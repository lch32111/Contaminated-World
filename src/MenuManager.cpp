#include "MenuManager.h"
#include "Core.h"

MenuManager::MenuManager()
{
	//currentGameState = eMainMenu;
	currentGameState = eGame;

	this->oPauseMenu = new PauseMenu();
	this->oMainMenu = new MainMenu();
}

MenuManager::~MenuManager()
{

}

void MenuManager::Update()
{
	switch (currentGameState)
	{
		case eMainMenu:
			break;
		case eGame:
			SCore::getMap()->Update();
			break;
		case ePause:
			break;
	}
}

void MenuManager::Draw(SDL_Renderer* rR)
{
	switch (currentGameState)
	{
		case eMainMenu:
			//oMainMenu->Draw(rR);
			break;
		case eGame:
			SCore::getMap()->Draw(rR);
			break;
		case ePause:
			SCore::getMap()->Draw(rR);
			oPauseMenu->Draw(rR);
			break;
		default:
			break;
	}
	
}

void MenuManager::enter()
{
	switch (currentGameState)
	{
		case eMainMenu:
			//oMainMenu->enter();
			break;

		case ePause:
			oPauseMenu->enter();
			break;
	}

}

void MenuManager::escape()
{
	switch (currentGameState)
	{
		case ePause:
			oPauseMenu->escape();
			break;

	}
}


void MenuManager::keyPressed(int key)
{
	switch (currentGameState)
	{
		case eMainMenu : 
			//oMainMenu->activeOption(key);
			break;
		case ePause :
			oPauseMenu->activeOption(key);
			break;
	}
}


int MenuManager::getStateID() { return currentGameState; }
void MenuManager::setStateID(gameState ID) { currentGameState = ID; }
