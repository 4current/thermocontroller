#include<LiquidCrystal.h>  //Header file for LCD Module

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //lcd connected pins

const byte sensor = A0;      // The LM35 is attached to A0
const byte controller = 13; // The controller output is D13
const byte button1 = 8;      // Settings Menu
const float maxV = 5.0;     // The reference voldage is 5V
const int cycleWait = 500;       // loop every 500ms

bool showF = true;
bool menuMode = false;

int onTemp = 25;        // Turn the heater on at a low temp
int offTemp = 26;       // Turn the heater off at a high temp

class TempSense {
  private:
    const int lm35Scale = 100.0; // 100 degree Celcius per Volt.
    byte sensor = A0;
    float maxV = 5.0;
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
    float getOnTemp() {
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
    bool showF = true;
    bool menuMode = false;
    byte button1 = 8;
    
  public:
    Display(TempSense *temp, Warmer *warmer) {
      this->temp = temp;
      this->warmer = warmer;
      init();
    }
    
    void init() {
       lcd.begin(16,2);           
    }

    void show() {
      bool toggle = ! digitalRead(this->button1);

      // Toggle menuMode if button1 pressed
      if (toggle) {
        this->menuMode = ! this->menuMode;
      }

      if (this-> menuMode) {
        lcd.setCursor(0,0);
        lcd.print("Off Temp:");
        lcd.print(offTemp);
        lcd.setCursor(0,1);
        lcd.print("On Temp:");
        lcd.print(onTemp);
      } else {
        lcd.setCursor(0,0);
        lcd.print("Temp: ");
        if (this->showF) {
          lcd.print((int)this->temp->getFahrenheit());
          lcd.print((char)223);
          lcd.print("F     ");
        } else {
          lcd.print((int)this->temp->getCelsius());
          lcd.print((char)223);
          lcd.print("C     ");
        }
      
        lcd.setCursor(0,1);
        if (this->warmer->isOn()) {
          lcd.print("Heater: On   ");
        } else {
          lcd.print("Heater: Off  ");
        }
        
      }
  }

  void setButtons(byte button1) {
     pinMode(this->button1, INPUT_PULLUP);
  }
};


TempSense temp(sensor, 5.0);
Warmer warmer(controller);
Display disp(&temp, &warmer);

void setup() {
  warmer.init();
  disp.setButtons(button1);
}
  
void loop() 
{
  if(temp.getCelsius() < onTemp) 
  {
    warmer.turnOn();
  }
  else if (temp.getCelsius() > offTemp)
  {
    warmer.turnOff();
  }

  disp.show();
  delay(cycleWait);
}
