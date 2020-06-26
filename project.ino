#include "MQ2.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);
int Analog_Input = A0;
int smoke;
MQ2 mq2(Analog_Input);
void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  mq2.begin();
  lcd.init();
}
void loop(){
  float* values= mq2.read(true); 
  smoke = mq2.readSmoke();
  lcd.setCursor(0,0);
  lcd.print("SMOKE:");
  lcd.print(smoke);
  lcd.setCursor(0,1);
  lcd.print(" %");
  delay(1000);
}
00.