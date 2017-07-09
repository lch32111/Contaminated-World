#pragma once


#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "header.h"
#include "Menu.h"

class PauseMenu : public Menu
{
private:

	SDL_Rect rPause;
	
public:

	PauseMenu();
	void Draw(SDL_Renderer* rR);

	void enter();
	void escape();
	void activeOption(int key);

	
};

#endif