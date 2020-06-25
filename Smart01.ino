#include <Wire.h>
#include "LiquidCrystal_I2C.h"                                                  

int sensorPin = A0;                                                             
int RELAY1 = 2;                                                                 
int LedRED = 12;
int LEDgreen = 11;
int smokeA0 = 0;
int sensorThres = 400;
LiquidCrystal_I2C lcd(0x27, 16, 2) ;                                            
  void setup() 
{                                                                               
    Serial.begin(9600);                                                        
    Serial.println("Starting");
    lcd.init();                                                                 
    lcd.backlight();                                                            
    Serial.begin(9600);                                                        
    pinMode(RELAY1, OUTPUT);                                                    
    pinMode(LedRED, OUTPUT);
    pinMode(LEDgreen, OUTPUT);
    pinMode(smokeA0, INPUT);
}

  void loop()                                                                     
{
    Serial.println("RUNNING !");
    int sensorValue;                                                            
    sensorValue = analogRead(sensorPin);                                        
    sensorValue = map(sensorValue, 0, 1023, 100, 0); 
    Serial.print("Soil moisture: ");                                            
    Serial.print(sensorValue);
    Serial.println(" %");
    int analogSensor = analogRead(smokeA0);
    Serial.print("Pin A0: ");
    Serial.println(analogSensor); 

    if (analogSensor > sensorThres)  
    {
    digitalWrite(LedRED, HIGH);
    digitalWrite(LEDgreen, LOW);
    }

    else  
    {
    digitalWrite(LedRED, LOW);
    digitalWrite(LEDgreen, HIGH);
    }
     delay(100);

    
    if(sensorValue <=40 )                                                      
    { 
        digitalWrite(RELAY1, HIGH);                                             
        lcd.setCursor(0, 0);                                                   
        lcd.print(" Pumb  on  ");                                               
        Serial.print(" Pumb  on  ");
        lcd.setCursor(0, 1);                                                     
        lcd.print("Moisture < 40");                                             
        Serial.println("Moisture < 40");
    }
    else       //ถ้าไม่ตรงเงื่อนไข
    {   
        digitalWrite(RELAY1, LOW);  
        lcd.setCursor(0, 0);                                                    
        lcd.print(" Pumb off  ");                                               
        Serial.print(" Pumb off  ");
        lcd.setCursor(0, 1);                                                    
        lcd.print("Moisture > 40");  
        Serial.println("Moisture > 40");
    }

    delay(5000); 
}