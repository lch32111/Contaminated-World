#pragma once

#ifndef MENU_H
#define MENU_H

#include "header.h"

class Menu
{
public :

	Menu();
	~Menu();

	int activeMenuOption;
	int numOfMenu;
	int menuXpos;
	int menuYpos;

	bool is_in_button(int x, int y, SDL_Rect button);

	void activeOption(int key);
	void resetActiveOption();
};




#endif 
