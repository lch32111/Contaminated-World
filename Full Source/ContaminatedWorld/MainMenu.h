#pragma once

#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"
#include "CIMG.h"

class MainMenu : public Menu
{
private:
	CIMG* cStartIcon;
	CIMG* cStartIcon_over;
	CIMG* cOption;
	CIMG* cOption_over;
	CIMG* cRanking;
	CIMG* cRanking_over;
	CIMG* cQuitIcon;
	CIMG* cQuitIcon_over;

public:
	MainMenu();

	void Update();
	void Draw(SDL_Renderer* rR);

	void DrawMainMenu(SDL_Renderer* rR);
	void DrawMainMenu_over1(SDL_Renderer* rR);
	void DrawMainMenu_over2(SDL_Renderer* rR);
	void DrawMainMenu_over3(SDL_Renderer* rR);
	void DrawMainMenu_over4(SDL_Renderer* rR);


	void enter();
	void click(int x, int y);



	void startGame();
	void restart();
	void quitGame();

	void checkMouseInput(int x, int y);
};

#endif 
