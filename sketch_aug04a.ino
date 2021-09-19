
#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define LOADCELL_DOUT_PIN  5
#define LOADCELL_SCK_PIN  6

HX711 scale;

int resval=0;
int respin = A0;
int buzzer = 8;
 
float weight;
float calibration_factor = -200; // for me this vlaue works just perfect 7050
 
void setup() 
{
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare(); //Reset the scale to 0
  //Get a baseline reading
  lcd.init();
  lcd.backlight();
  pinMode(buzzer,OUTPUT);
  lcd.setCursor(6,0);
  lcd.print("DIY");
  lcd.setCursor(1,1);
  lcd.print("Weighing Scale");
  delay(3000);
  lcd.clear();
}
 
void loop() 
 
{
  resval = analogRead(respin);
  // Print 'Hello World!' on the first line of the LCD:
  lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
  lcd.print("water level!"); // Print the string "Hello World!"
  lcd.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  //Read data from analog pin and store it to resval variable
   
  if (resval<=300){ 
    lcd.println("Empty ");
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
    delay(1000);} else if (resval>400 && resval<=500){ lcd.println("Low "); } else if (resval>500 && resval<=530){ lcd.println("Medium "); } else if (resval>330){ 
    lcd.println("High "); 
  }
  delay(3000); 
  lcd.clear();
  delay(1000);

  
 
  weight = scale.get_units(); 
 
  lcd.setCursor(0, 0);
  lcd.print("Measured Weight");
  lcd.setCursor(0, 1);
  lcd.print(weight);
  lcd.print(" G ");
  delay(4000);
  lcd.clear();
  
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println("G");
  Serial.println();
  
 }
