
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
#include "SMObject.h"
#include "Menu.h"

SMObject* SMObjects[10];
int numSMObjects = 5;

Button Button1(6); 
Button Button2(7); 
Button Button3(8); 
Button Button4(9);
Menu DipperMenu;


void setup() {
	DipperMenu.InitButtons(&Button1,&Button2,&Button3,&Button4);
	DipperMenu.InitLCD(12,11,5,4,3,2);
	DipperMenu.InitMotor(0,1);

	SMObjects[0] = &Button1;
	SMObjects[1] = &Button2;
	SMObjects[2] = &Button3;
	SMObjects[3] = &Button4;
	SMObjects[4] = &DipperMenu;
}

void loop() {
	for(int i=0;i<numSMObjects;++i){
		SMObjects[i]->SM();
	}
  	delay(20);
}


