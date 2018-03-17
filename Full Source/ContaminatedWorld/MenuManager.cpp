#include "MenuManager.h"
#include "Core.h"

MenuManager::MenuManager()
{
	currentGameState = eTitle;
	cMainMenuBackground = SCore::getAssetManager()->getMainmenuBackgroundIMG();
}

MenuManager::~MenuManager()
{

}

void MenuManager::Update()
{
	switch (currentGameState)
	{
	case eTitle:
		oTitle.Update();
		break;
	case eMainMenu:
		oMainMenu.Update();
		break;
	case eGame:
		SCore::getMap()->Update();
		break;
	case ePause:
		oPauseMenu.Update();
		break;
	case eRanking:
		oRankingMenu.Update();
		break;
	case eUpgradeUI:
		oUpgradeUI.Update();
		break;
	case eEnding:
		oEndingMenu.Update();
		break;
	}
}

void MenuManager::Draw(SDL_Renderer* rR)
{
	switch (currentGameState)
	{
	case eTitle:
		oTitle.Draw(rR);
		break;
	case eMainMenu:
		cMainMenuBackground->Draw(rR, 0, 0, false);
		oMainMenu.Draw(rR);
		break;
	case eGame:
		SCore::getMap()->Draw(rR);
		break;
	case ePause:
		SCore::getMap()->Draw(rR);
		oPauseMenu.Draw(rR);
		break;
	case eOption:
		cMainMenuBackground->Draw(rR, 0, 0, false);
		oOptionMenu.Draw(rR);
		break;
	case eRanking:
		oRankingMenu.Draw(rR);
		break;
	case eUpgradeUI:
		SCore::getMap()->Draw(rR);
		oUpgradeUI.Draw(rR);
		break;
	case eEnding:
		oEndingMenu.Draw(rR);
		break;
	}

}

void MenuManager::enter()
{
	switch (currentGameState)
	{
	case eTitle:
		oTitle.enter();
		break;
	case eMainMenu:
		oMainMenu.enter();
		break;
	case ePause:
		oPauseMenu.enter();
		break;
	case eEnding:
		oEndingMenu.enter();
		break;
	default:
		break;
	}
}

void MenuManager::escape()
{
	switch (currentGameState)
	{
	case ePause:
		oPauseMenu.escape();
		break;
	case eOption:
		oOptionMenu.escape();
		break;
	case eRanking:
		oRankingMenu.escape();
		break;
	case eUpgradeUI:
		oUpgradeUI.escape();
		break;
	}
}


void MenuManager::keyPressed(int key)
{
	switch (currentGameState)
	{
	case eMainMenu:
		oMainMenu.activeOption(key);
		break;
	case ePause:
		oPauseMenu.activeOption(key);
		break;
	case eOption:
		oOptionMenu.activeVolumeControl(key);
		break;
	case eRanking:
		oRankingMenu.activeOption(key);
		break;
	case eEnding:
		oEndingMenu.activeOption(key);
	default:
		break;
	}
}

void MenuManager::checkMouseInput(int x, int y)
{
	switch (SInfo::getMM()->getStateID())
	{
	case eMainMenu:
		oMainMenu.checkMouseInput(x, y);
		break;
	case ePause:
		oPauseMenu.checkMouseInput(x, y);
		break;
	case eOption:
		oOptionMenu.checkMouseInput(x, y);
		break;
	case eRanking:
		oRankingMenu.checkMouseInput(x, y);
		break;
	case eUpgradeUI:
		oUpgradeUI.checkMouseInput(x, y);
		break;
	case eEnding:
		oEndingMenu.checkMouseInput(x, y);
		break;
	}
}

void MenuManager::click(int x, int y)
{
	switch (SInfo::getMM()->getStateID())
	{
	case eMainMenu:
		oMainMenu.click(x, y);
		break;
	case ePause:
		oPauseMenu.click(x, y);
		break;
	case eOption:
		oOptionMenu.click(x, y);
		break;
	case eRanking:
		oRankingMenu.click(x, y);
		break;
	case eUpgradeUI:
		oUpgradeUI.click(x, y);
		break;
	case eEnding:
		oEndingMenu.click(x, y);
	default:
		break;
	}
}

void MenuManager::passTextInput(char* InputText)
{
	oEndingMenu.appendUserText(InputText);
}

void MenuManager::eraseText()
{
	oEndingMenu.popupUserText();
}

int MenuManager::getStateID() { return currentGameState; }
void MenuManager::setStateID(gameState ID) { currentGameState = ID; }
MainMenu* MenuManager::getMainMenu() { return &oMainMenu; }
OptionMenu* MenuManager::getOptionMenu() { return &oOptionMenu; }
RankingMenu* MenuManager::getRankingMenu() { return &oRankingMenu; }
Upgrade* MenuManager::getUpgradeUI() { return &oUpgradeUI; }
EndingMenu* MenuManager::getEndingMenu() { return &oEndingMenu; }