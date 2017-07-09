#pragma once

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "PauseMenu.h"
#include "MainMenu.h"

class MenuManager
{
private:

	MainMenu* oMainMenu;
	PauseMenu* oPauseMenu;

public:
	MenuManager();
	~MenuManager();

	enum gameState
	{
		eMainMenu,
		eGame,
		ePause
	};

	gameState currentGameState;

	void Update();
	void Draw(SDL_Renderer* rR);

	void enter();
	void escape();

	void keyPressed(int key);	


	/*----get & set------*/
	int getStateID();
	void setStateID(gameState ID);
	//PauseMenu* getPauseMenu();

};


#endif