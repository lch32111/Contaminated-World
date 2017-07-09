#include "MenuManager.h"
#include "Core.h"

MenuManager::MenuManager()
{
	currentGameState = eGame;

	this->oPauseMenu = new PauseMenu();
}

MenuManager::~MenuManager()
{

}

void MenuManager::Draw(SDL_Renderer* rR)
{
	switch (currentGameState)
	{
	case eMainMenu:
		;
		break;
	case eGame:
		SCore::getMap()->Draw(rR);
		break;
	case ePause:
		SCore::getMap()->DrawMenu(rR); //--
		oPauseMenu->Draw(rR);
		break;
	default:
		break;
	}
}

int MenuManager::getStateID() { return currentGameState; }
void MenuManager::setStateID(gameState ID) { currentGameState = ID; }
