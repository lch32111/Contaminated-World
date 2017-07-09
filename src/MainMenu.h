#pragma once

#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"

class MainMenu : public Menu
{
private:



public:

	MainMenu();

	void Update();
	void Draw();

	void enter();
	void activeOption(int key);
};

#endif 
