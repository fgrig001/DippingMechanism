#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "SMObject.h"
#include "Button.h"
#include "Motor.h"

class Menu : public SMObject{
	public:
		Menu();
		void InitButtons(Button *b1,Button *b2,Button *b3,Button *b4);
		void InitLCD(int pin1,int pin2,int pin3,int pin4,int pin5,int pin6);
		void InitMotor(int dir_pin,int step_pin);
		void SM();
	private:
		LiquidCrystal *LCD;
		Button *Button1;
		Button *Button2;
		Button *Button3;
		Button *Button4;
		Motor *Stepper;
		enum states {MAIN_BEF,INC_MB,DEC_MB,MAIN_AFT,INC_MA,DEC_MA,RUN,
					 RET,PRE_MB,PRE_AB,PRE_MA,PRE_AA,ADJ_BEF,INC_AB,
					 DEC_AB,ADJ_AFT,INC_AA,DEC_AA} state;
		int speedVal;
		int numSteps;
};

Menu::Menu() : speedVal(0),numSteps(400) {}

void Menu::InitButtons(Button *b1,Button *b2,Button *b3,Button *b4){
	Button1 = b1;
	Button2 = b2;
	Button3 = b3;
	Button4 = b4;
}

void Menu::InitLCD(int pin1,int pin2,int pin3,int pin4,int pin5,int pin6){
	LCD = new LiquidCrystal(pin1,pin2,pin3,pin4,pin5,pin6);
  	LCD->begin(16, 2);
}

void Menu::InitMotor(int dir_pin,int step_pin){
	Stepper = new Motor(dir_pin,step_pin);
}

void Menu::SM(){
	bool b1 = !Button1->getStatus();
	bool b2 = !Button2->getStatus();
	bool b3 = !Button3->getStatus();
	bool b4 = !Button4->getStatus();

	switch(state){ // transitions
		case MAIN_BEF:
			if(b2){
				state = INC_MB;
				speedVal++;
			}else if(b1){
				state = DEC_MB;
				speedVal--;
			}else if(b3){
  				LCD->setCursor(0, 1);
  				LCD->print(" running...     ");
				state = RUN;
			}else if(b4){
				state = PRE_AB;
			}else{
				state = MAIN_BEF;
			}
			break;
		case INC_MB:
			state = b2 ? INC_MB : MAIN_BEF;
			break;
		case DEC_MB:
			state = b1 ? DEC_MB : MAIN_BEF;
			break;
		case MAIN_AFT:
			if(b2){
				state = INC_MA;
				speedVal++;
			}else if(b1){
				state = DEC_MA;
				speedVal--;
			}else if(b3){
  				LCD->setCursor(0, 1);
  				LCD->print(" running...     ");
				state = RET;
			}else if(b4){
				state = PRE_AA;
			}else{
				state = MAIN_AFT;
			}
			break;
		case INC_MA:
			state = b2 ? INC_MA : MAIN_AFT;
			break;
		case DEC_MA:
			state = b1 ? DEC_MA : MAIN_AFT;
			break;
		case RUN:
			state = MAIN_AFT;
			break;
		case RET:
			state = MAIN_BEF;
			break;
		case PRE_MB:
			state = b4 ? PRE_MB : MAIN_BEF;
			break;
		case PRE_AB:
			state = b4 ? PRE_AB : ADJ_BEF;
			break;
		case PRE_MA:
			state = b4 ? PRE_MA : MAIN_AFT;
			break;
		case PRE_AA:
			state = b4 ? PRE_AA : ADJ_AFT;
			break;
		case ADJ_BEF:
			if(b1){
				state = DEC_AB;	
			}else if(b2){
				state = INC_AB;	
			}else if(b4){
				state = PRE_MB;	
			}else{
				state = ADJ_BEF;
			}
			break;
		case INC_AB:
			state = b2 ? INC_AB : ADJ_BEF;
			break;
		case DEC_AB:
			state = b1 ? DEC_AB : ADJ_BEF;
			break;
		case ADJ_AFT:
			if(b1){
				state = DEC_AA;	
			}else if(b2){
				state = INC_AA;	
			}else if(b4){
				state = PRE_MA;	
			}else{
				state = ADJ_AFT;
			}
			break;
		case INC_AA:
			state = b2 ? INC_AA : ADJ_AFT;
			break;
		case DEC_AA:
			state = b1 ? DEC_AA : ADJ_AFT;
			break;
		default:
			break;
	}
	switch(state){ // actions
		case MAIN_BEF:
  			LCD->setCursor(0, 0);
  			LCD->print("Rate: 00 mm/s");
			(speedVal<10) ? LCD->setCursor(7,0) : LCD->setCursor(6,0);
      		LCD->print(speedVal,DEC);
  			LCD->setCursor(0, 1);
  			LCD->print(" -  +   run adj");
			break;
		case INC_MB:
			break;
		case DEC_MB:
			break;
		case MAIN_AFT:
  			LCD->setCursor(0, 0);
  			LCD->print("Rate: 00 mm/s");
			(speedVal<10) ? LCD->setCursor(7,0) : LCD->setCursor(6,0);
      		LCD->print(speedVal,DEC);
  			LCD->setCursor(0, 1);
  			LCD->print(" -  +   ret adj");
			break;
		case INC_MA:
			break;
		case DEC_MA:
			break;
		case RUN:
			Stepper->run(1,speedVal,numSteps);
			break;
		case RET:
			Stepper->run(0,speedVal,numSteps);
			break;
		case PRE_MB:
			break;
		case PRE_AB:
			break;
		case PRE_MA:
			break;
		case PRE_AA:
			break;
		case ADJ_BEF:
  			LCD->setCursor(0, 0);
  			LCD->print("Adj Start Pos");
  			LCD->setCursor(0, 1);
  			LCD->print(" -  +       exit");
			break;
		case INC_AB:
			Stepper->run(1,speedVal,10);
			break;
		case DEC_AB:
			Stepper->run(0,speedVal,10);
			break;
		case ADJ_AFT:
  			LCD->setCursor(0, 0);
  			LCD->print("Adj End Pos");
  			LCD->setCursor(0, 1);
  			LCD->print(" -  +       exit");
			break;
		case INC_AA:
			Stepper->run(1,speedVal,10);
			numSteps += 10;
			break;
		case DEC_AA:
			Stepper->run(0,speedVal,10);
			numSteps -= 10;
			break;
		default:
			break;
	}
}
