/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

#include <LiquidCrystal.h>
#include "Button.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Button minusButton(6), plusButton(7), runButton(8), killButton(9);

//  Global Variables
int speedVal;

void setup() {
  // initialize variables
  speedVal = 0;
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Rate: 00 mm/s");
  lcd.setCursor(0, 1);
  lcd.print(" -  +   run kill");
}

void loop() {
  plusButton.SM();
  minusButton.SM();
  runButton.SM();
  killButton.SM();
  if(minusButton.getStatus() == 0){
      lcd.setCursor(6,0);
      lcd.print(--speedVal,DEC);
  }
  if(plusButton.getStatus() == 0){
      lcd.setCursor(6,0);
      lcd.print(++speedVal,DEC);
  }
  if(runButton.getStatus() == 0){
      //lcd.setCursor(0, 0);
      //lcd.print("Rate: 11 mm/s");
  }
  if(killButton.getStatus() == 0){
      //lcd.setCursor(0, 0);
      //lcd.print("Rate: 00 mm/s");
  }
  delay(20);
}


