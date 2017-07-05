#pragma once

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "PauseMenu.h"

class MenuManager
{
private:

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

	void Draw(SDL_Renderer* rR);



	/*----get & set------*/
	int getStateID();
	void setStateID(gameState ID);

};


#endif