#include<LiquidCrystal.h>  //Header file for LCD Module

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //lcd connected pins

const int sensor = A0; // The LM35 is attached to A0
const float maxV = 5.0; // The reference voldage is 5V

bool showF = true;
int t;
int onTemp = 25;        // Turn the heater on at a low temp
int offTemp = 26;       // Turn the heater off at a high temp

class TempSense {
  private:
    const int lm35Scale = 100.0; // 100 degree Celcius per Volt.
    int sensor = A0;
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
};

class Warmer {
  private:
    bool onStatus = false;
  public:
    Warmer() {
    }
    void turnOn() {
      this->onStatus = true;
    }
    void turnOff() {
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
      lcd.setCursor(0,0);
      lcd.print("Temp:");
      if (this->showF) {
      lcd.print((int)this->temp->getFahrenheit());
      lcd.print((char)223);
      lcd.print(" F");
    } else {
      lcd.print((int)this->temp->getCelsius());
      lcd.print((char)223);
      lcd.print(" C");
    }
  
    lcd.setCursor(0,1);
    if (this->warmer->isOn()) {
      lcd.print("Heater: On   ");
    } else {
      lcd.print("Heater: Off  ");
    }
  }   
};


TempSense temp(sensor, 5.0);
Warmer warmer;
Display disp(&temp, &warmer);

void setup() {}
  
void loop() 
{
  if(temp.getCelsius() > onTemp) 
  {
    warmer.turnOff();
  }
  else if (temp.getCelsius() < offTemp)
  {
    warmer.turnOn();
  }

  disp.show();
  delay(1000);
}
