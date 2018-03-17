#pragma once


#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Menu.h"
#include "CIMG.h"

class PauseMenu : public Menu
{
private:

	SDL_Rect rPause;
	CIMG* cContinueIcon;
	CIMG* cContinueIcon_over;
	CIMG* cGotoMain;
	CIMG* cGotoMain_over;
	CIMG* cOption;
	CIMG* cOption_over;
	CIMG* cQuitIcon;
	CIMG* cQuitIcon_over;

	int menuXpos;
	int menuYpos;

public:
	PauseMenu();
	void Update();
	void Draw(SDL_Renderer* rR);

	void DrawPauseMenu(SDL_Renderer* rR);
	void DrawPauseMenu_over1(SDL_Renderer* rR);
	void DrawPauseMenu_over2(SDL_Renderer* rR);
	void DrawPauseMenu_over3(SDL_Renderer* rR);
	void DrawPauseMenu_over4(SDL_Renderer* rR);

	void enter();
	void escape();
	void click(int x, int y);

	void checkMouseInput(int x, int y);
	void resetGotoMain();

};

#endif