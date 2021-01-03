#include<LiquidCrystal.h>  //Header file for LCD Module
#include<EEPROM.h>         // Store the settings in EEprom
#include<RunningAverage.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //lcd connected pins

const byte sensor = A0;      // The LM35 is attached to A0
const byte controller = 13; // The controller output is D13
const float maxV = 5.0;     // The reference voldage is 5V
const int cycleWait = 1000;       // loop every second

bool showF = true;
bool menuMode = false;

int onTemp = 2;        // Turn the heater on at a low temp
int offTemp = 5;       // Turn the heater off at a high temp

const byte eepromSet = 0xA1;

byte settings[4];

class TempSense {
  private:
    const int lm35Scale = 100.0; // 100 degree Celcius per Volt.
    byte sensor = A0;
    float maxV;
  public:
    TempSense(byte sensor, float maxV) {
      this->sensor = sensor;
      this->maxV = maxV;
      init();
    }
    void init() {
      pinMode(sensor,INPUT);
    }
    float getVolts() {
      return maxV * (float) analogRead(sensor) / 1023.0;
    }
    float getCelsius() {
      return lm35Scale * this->getVolts();
    }
    float getFahrenheit() {
      return 1.8 * this->getCelsius() + 32.0;
    }
};

class Warmer {
  private:
    bool onStatus = false;
    byte controller = 13;

  public:
    Warmer(int controller) {
      this->controller = controller;
      init();
    }

    void init() {
      pinMode(this->controller, OUTPUT);
    }
    void turnOn() {
      digitalWrite(this->controller, HIGH);
      this->onStatus = true;
    }
    void turnOff() {
      digitalWrite(this->controller, LOW);
      this->onStatus = false;
    }
    bool isOn() {
      return this->onStatus;
    }
};

class Display {
  private:
    TempSense *temp;
    Warmer *warmer;
    char deg = 223;
    bool showF = true;
    bool menuMode = false;
    int optIdx = 0;
    int maxOpts = 4;
    int valIdx = 0;
    const byte button1 = 6;
    const byte button2 = 7;
    const char *opts[4] = {"Hi Temp", "Low Temp", "Avg. Time", "Hold Time"};
    const int hiTemp[3] = {40, 48, 80};
    const int lowTemp[3] = {33, 35, 74};
    const int avgTime[3] = {60, 300, 600};
    const int holdTime[3] = {4, 8, 24};
    long int buttonTimer;
    const long int buttonTimeout = 5000;  // 5 second timeout;
    
    byte hiTempValIdx;
    byte lowTempValIdx;
    byte avgTimeValIdx;
    byte holdTimeValIdx;

  public:
    Display(TempSense *temp, Warmer *warmer) {
      this->temp = temp;
      this->warmer = warmer;
      init();
    }
    
    void init() {

       byte stored;
       int address;
       lcd.begin(16,2);

       this->hiTempValIdx = 0;
       this->lowTempValIdx = 0;
       this->avgTimeValIdx = 0;
       this->holdTimeValIdx = 0;
       
       // read in and initialize the stored settings if they are stored

       EEPROM.get(4 * sizeof(byte), stored);
       
       if (stored == eepromSet) {
           for (int i = 0; i < 4; i++) {
               address = i * sizeof(byte);
               EEPROM.get(address, settings[i]);
           }
       }
       this->hiTempValIdx = settings[0];
       this->lowTempValIdx = settings[1];
       this->avgTimeValIdx = settings[2];
       this->holdTimeValIdx = settings[3];

  
    }

    void setButtons() {
      pinMode(this->button1, INPUT_PULLUP);
      pinMode(this->button2, INPUT_PULLUP);
    }
    
    void flipMenuMode() {
       if (!this->menuMode) {
         this->menuMode = true;
         this->optIdx = 0;
       } else if (this->optIdx < this->maxOpts - 1) {
         ++(this->optIdx);
       } else {
        this->optIdx = 0;
       }
       this->buttonTimer = millis(); // update the timer on each event
    }

    void cycleValues() {
       if (this->menuMode) {
        switch(this->optIdx) {
          case 0:
            this->hiTempValIdx = ++(this->hiTempValIdx) % 3;
            break;
          case 1:
            this->lowTempValIdx = ++(this->lowTempValIdx) % 3;
            break;
          case 2:
            this->avgTimeValIdx = ++(this->avgTimeValIdx) % 3;
            break;
          case 3:
            this->holdTimeValIdx = ++(this->holdTimeValIdx) % 3;
            break;
        }
       }
       this->buttonTimer = millis(); // update the timer on each event
    }

    float f2c(float f) {
      return (f - 32) / 1.8;
    }

    void checkTimeout() {
      int address;
      
      if ( (millis() - this->buttonTimer) > buttonTimeout) {
        this->menuMode = false;
        offTemp = f2c(hiTemp[this->hiTempValIdx]);
        onTemp = f2c(lowTemp[this->lowTempValIdx]);
        settings[0] = this->hiTempValIdx;
        settings[1] = this->lowTempValIdx;
        settings[2] = this->avgTimeValIdx;
        settings[3] = this->holdTimeValIdx;
    }
        
        for (int i = 0; i < 4; i++) {
           address = i * sizeof(byte);
           EEPROM.update(address, settings[i]);
        }
        address = 4 * sizeof(byte);
        EEPROM.update(address, eepromSet);
               
    }
    
    void show() {
      if (this-> menuMode) {
        lcd.clear();
        lcd.setCursor(0,0);
//        lcd.print("Timer:");
//        lcd.print(millis() - this->buttonTimer);
        lcd.print("Option:");
        lcd.print(opts[optIdx]);
        lcd.setCursor(0,1);
        lcd.print("Value:");
        char buf [7];
        char buf2 [10];
        switch(this->optIdx) {
          case 0:
            sprintf(buf, " %2d%c F", (int)hiTemp[this->hiTempValIdx], deg);
            lcd.print(buf);
            break;
          case 1:
            sprintf(buf, " %2d%c F", (int)lowTemp[this->lowTempValIdx], deg);
            lcd.print(buf);
            break;
          case 2:
            sprintf(buf2, " %3d sec.", (int)avgTime[this->avgTimeValIdx]);
            lcd.print(buf2);
            break;
          case 3:
            sprintf(buf2, " %3d hrs.", (int)holdTime[this->holdTimeValIdx]);
            lcd.print(buf2);
            break;
       }
        
      } else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Temp:");
        char buf [12];
        sprintf(buf, " %2d%c F     ", (int)this->temp->getFahrenheit(), deg);
        lcd.print(buf);
        lcd.setCursor(0,1);
        if (this->warmer->isOn()) {
          lcd.print("Heater: On   ");
        } else {
          lcd.print("Heater: Off  ");
        }
        
      }
  }

};


TempSense temp(sensor, 5.0);
Warmer warmer(controller);
Display disp(&temp, &warmer);

bool toggle;
const byte button1 = 6;
const byte button2 = 7;

void setup() {
  warmer.init();
  disp.setButtons();
}

void loop() 
{
  if(temp.getCelsius() < onTemp) 
  {
    warmer.turnOn();
  } else if (temp.getCelsius() > offTemp)
  {
    warmer.turnOff();
  }

  if (! digitalRead(button1) ) {
    disp.flipMenuMode();    
  }
  if (! digitalRead(button2) ) {
    disp.cycleValues();    
  }

  disp.checkTimeout();
  disp.show();
  delay(cycleWait);
}
