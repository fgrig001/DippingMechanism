#pragma once
#include <Arduino.h>
#include "Button.h"

class Menu{
	public:
		Menu();
		void SM();
		void run();
	private:
		int speedVal;
		Button * minusButton, plusButton, runButton, killButton;
};

Menu::Menu(){
	// Alocate button objects
	minusButton = new Button(6);
	plussButton = new Button(7);
	runButton = new Button(8);
	killButton = new Button(9);
}


