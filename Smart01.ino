#include <Wire.h>
#include "LiquidCrystal_I2C.h"                                                  //อ้างอิงและดึงคำสั่งจาก library

int sensorPin = A0;                                                             //กำหนดตัวแปร sensorPin = A0
int RELAY1 = 2;                                                                 //กำหนดตัวแปร RELAY = 2
int LedRED = 12;
int LEDgreen = 11;
int smokeA0 = 0;
int sensorThres = 400;
LiquidCrystal_I2C lcd(0x27, 16, 2) ;                                            // ฟังชั่นของ lcd  ชนิดมี16หลัก2แถว

  void setup() 
{                                                                               //เริ่มต้นการทำงานการตั้งค่า
    Serial.begin(9600);                                                        
    Serial.println("Starting");
    lcd.init();                                                                 //เริ่มต้นการทำงานของ lcd
    lcd.backlight();                                                            // แบคไลท์ทำงาน ไฟติด
    Serial.begin(9600);                                                         //ความเร็วในการส่งข้อมูลแบบอนุกรม9600เซ็กกั้น
    pinMode(RELAY1, OUTPUT);                                                    // กำหนดให้ relay เป็น output
    pinMode(LedRED, OUTPUT);
    pinMode(LEDgreen, OUTPUT);
    pinMode(smokeA0, INPUT);
}

  void loop()                                                                     //การทำงานวนซ้ำๆไป
{
    Serial.println("RUNNING !");
    int sensorValue;                                                            //ประกาศตัวแปร sensor value
    sensorValue = analogRead(sensorPin);                                        // อา่นค่าตัวแปรของ sersorPin เก็บไว้ที่ sensor value
    sensorValue = map(sensorValue, 0, 1023, 100, 0); 
    Serial.print("Soil moisture: ");                                            //ความชื้นในดิน
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

    
    if(sensorValue <=40 )                                                       //ถ้า sensor value วัดได้น้อยกว่าหรือเท่า40 ให้ทำงานต่อไปในปีกกา
    { 
        digitalWrite(RELAY1, HIGH);                                             // ส่งข้อมูลไปยังขาdigitalให้RELAYทำงานเป็น high เป็น1
        lcd.setCursor(0, 0);                                                    // เคอเซอร์ตัวอังษร หลัก 0 แถวที่ 0
        lcd.print(" Pumb  on  ");                                               // เเสดงข้อความบน lcd
        Serial.print(" Pumb  on  ");
        lcd.setCursor(0, 1);                                                    // เคอเซอร์ตัวอังษร หลัก 0 แถวที่ 1 
        lcd.print("Moisture < 40");                                             //เเสดงข้อความบนจอ lcd moisture น้อยกว่า 40
        Serial.println("Moisture < 40");
    }
    else       //ถ้าไม่ตรงเงื่อนไข
    {   
        digitalWrite(RELAY1, LOW);  
        lcd.setCursor(0, 0);                                                    // เคอเซอร์ตัวอังษร หลัก 0 แถวที่ 0
        lcd.print(" Pumb off  ");                                               // เเสดงข้อความบน lcd
        Serial.print(" Pumb off  ");
        lcd.setCursor(0, 1);                                                    // เคอเซอร์ตัวอังษร หลัก 0 แถวที่ 1
        lcd.print("Moisture > 40");  
        Serial.println("Moisture > 40");
    }

    delay(5000); 
}