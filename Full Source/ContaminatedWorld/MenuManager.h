#pragma once

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "Title.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "OptionMenu.h"
#include "RankingMenu.h"
#include "Upgrade.h"
#include "EndingMenu.h"


class MenuManager
{
private:
	Title oTitle;
	MainMenu oMainMenu;
	PauseMenu oPauseMenu;
	OptionMenu oOptionMenu;
	RankingMenu oRankingMenu;
	Upgrade oUpgradeUI;
	EndingMenu oEndingMenu;

	CIMG* cMainMenuBackground;
public:

	MenuManager();
	~MenuManager();

	enum gameState
	{
		eTitle,
		eMainMenu,
		eGame,
		ePause,
		eOption,
		eRanking,
		eUpgradeUI,
		eEnding,
	};

	gameState currentGameState;

	void Update();
	void Draw(SDL_Renderer* rR);

	void enter();
	void escape();

	void keyPressed(int key);
	void checkMouseInput(int x, int y);
	void click(int x, int y);

	void passTextInput(char* InputText);
	void eraseText();

	/*----get & set------*/
	int getStateID();
	void setStateID(gameState ID);

	MainMenu* getMainMenu();
	OptionMenu* getOptionMenu();
	RankingMenu* getRankingMenu();
	Upgrade* getUpgradeUI();
	EndingMenu* getEndingMenu();
};


#endif