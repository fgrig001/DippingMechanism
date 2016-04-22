#pragma once
#include <Arduino.h>
#include "SMObject.h"

class Button : public SMObject{
	public:
		Button(int pin);
		bool getStatus();
		void SM();
	private:
		bool buttonVal;
		int buttonPin;
		enum states {ONE,ZERO,DB1,DB2} state;
};

Button::Button(int pin):
	buttonVal(1),
	buttonPin(pin),
	state(DB1)
{
	pinMode(pin,INPUT);
	digitalWrite(pin,HIGH);
	period = 5;
}

bool Button::getStatus(){
	return buttonVal;
}

void Button::SM(){
	bool b = digitalRead(buttonPin);
	switch(state){ // transitions
		case ONE:
			state = (b==1) ? ONE : DB1;
			break;
		case DB1:
			state = (b==1) ? ONE : ZERO;
			break;
		case ZERO:
			state = (b==1) ? DB2 : ZERO;
			break;
		case DB2:
			state = (b==1) ? ONE : ZERO;
			break;
		default:
			state = DB1;
	}
	switch(state){ // actions
		case ONE:
			buttonVal = 1;
			break;
		case DB1:
			buttonVal = 1;
			break;
		case ZERO:
			buttonVal = 0;
			break;
		case DB2:
			buttonVal = 0;
			break;
		default:
			break;
	}
}
