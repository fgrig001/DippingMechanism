#pragma once
#include <Arduino.h>

class Motor{
	public:
		Motor(int dir_pin, int step_pin);
		void run(int direction,int speed_val, int num_steps);
	private:
		int dirPin;
		int stepPin;
};

Motor::Motor(int dir_pin, int step_pin) :
	dirPin(dir_pin),
	stepPin(step_pin)
{
	pinMode(dirPin,OUTPUT);
	pinMode(stepPin,OUTPUT);
}

void Motor::run(int direction,int speed_val, int num_steps){
	int delayVal = 200/speed_val;
	digitalWrite(dirPin,direction);
	for(int i=0;i<num_steps;++i){
		digitalWrite(stepPin,HIGH);
		delay(delayVal);
		//delayMicroseconds(delay);
		digitalWrite(stepPin,LOW);
		delay(delayVal);
		//delayMicroseconds(delay);
	}
}

