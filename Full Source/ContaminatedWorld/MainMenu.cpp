#include "MainMenu.h"
#include "StaticInfo.h"
#include "Core.h"

MainMenu::MainMenu()
{
	cStartIcon = SCore::getAssetManager()->getMainmenuBoxIMG();
	cStartIcon_over = &cStartIcon[1];
	cOption = &cStartIcon[2];
	cOption_over = &cStartIcon[3];
	cRanking = &cStartIcon[4];
	cRanking_over = &cStartIcon[5];
	cQuitIcon = &cStartIcon[6];
	cQuitIcon_over = &cStartIcon[7];

	this->numOfMenu = 4;
	this->menuXpos = (SInfo::SCREEN_WIDTH - cStartIcon->getRect().w) / 2;
	this->menuYpos = (SInfo::SCREEN_HEIGHT / 5 * 2) + SInfo::SCREEN_HEIGHT / 16;
}


void MainMenu::Update()
{
	SInfo::getMusic()->changeMusic();
	SInfo::getMusic()->PlayMusic();
}

void MainMenu::Draw(SDL_Renderer* rR)
{
	switch (activeMenuOption)
	{
	case 0:
		// 게임시작 아이콘 활성화
		DrawMainMenu_over1(rR);
		break;
	case 1:
		// 옵션 아이콘 활성화
		DrawMainMenu_over2(rR);
		break;
	case 2:
		// 랭킹 아이콘 활성화
		DrawMainMenu_over3(rR);
		break;
	case 3:
		// 게임종료 아이콘 활성화
		DrawMainMenu_over4(rR);
		break;
	default:
		DrawMainMenu(rR);
		break;
	}
}

void MainMenu::DrawMainMenu(SDL_Renderer* rR)
{
	cStartIcon->Draw(rR, menuXpos, menuYpos, false);
	cOption->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8, false);
	cRanking->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8 * 2, false);
	cQuitIcon->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8 * 3, false);
}
void MainMenu::DrawMainMenu_over1(SDL_Renderer* rR)
{
	cStartIcon_over->Draw(rR, menuXpos, menuYpos, false);
	cOption->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8, false);
	cRanking->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8 * 2, false);
	cQuitIcon->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8 * 3, false);
}

void MainMenu::DrawMainMenu_over2(SDL_Renderer* rR)
{
	cStartIcon->Draw(rR, menuXpos, menuYpos, false);
	cOption_over->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8, false);
	cRanking->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8 * 2, false);
	cQuitIcon->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8 * 3, false);
}

void MainMenu::DrawMainMenu_over3(SDL_Renderer* rR)
{
	cStartIcon->Draw(rR, menuXpos, menuYpos, false);
	cOption->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8, false);
	cRanking_over->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8 * 2, false);
	cQuitIcon->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8 * 3, false);
}

void MainMenu::DrawMainMenu_over4(SDL_Renderer* rR)
{
	cStartIcon->Draw(rR, menuXpos, menuYpos, false);
	cOption->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8, false);
	cRanking->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8 * 2, false);
	cQuitIcon_over->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 8 * 3, false);
}


void MainMenu::enter()
{
	switch (activeMenuOption)
	{
	case 0:
		startGame();
		break;
	case 1:
		SInfo::getMM()->setStateID(SInfo::getMM()->eOption);
		break;
	case 2:
		SInfo::getMM()->getRankingMenu()->postProcessing();
		SInfo::getMM()->setStateID(SInfo::getMM()->eRanking);
		break;
	case 3:
		quitGame();
		break;
	}
}

void MainMenu::click(int x, int y)
{
	switch (activeMenuOption)
	{
	case 0:
		if (is_in_button(x, y, cStartIcon->getRect()))
			startGame();
		break;
	case 1:
		if (is_in_button(x, y, cOption->getRect()))
			SInfo::getMM()->setStateID(SInfo::getMM()->eOption);
		break;
	case 2:
		if (is_in_button(x, y, cRanking->getRect()))
		{
			SInfo::getMM()->getRankingMenu()->postProcessing();
			SInfo::getMM()->setStateID(SInfo::getMM()->eRanking);
		}
		break;
	case 3:
		if (is_in_button(x, y, cQuitIcon->getRect()))
			quitGame();
		break;
	}
}

void MainMenu::startGame()
{
	SInfo::getMM()->setStateID(SInfo::getMM()->eGame);
	SInfo::getMusic()->PlayMusic(SInfo::getMusic()->mGame);
}

void MainMenu::restart()
{
	startGame();
}

void MainMenu::quitGame()
{
	SCore::bQuitGame = true;
}

void MainMenu::checkMouseInput(int x, int y)
{
	if (is_in_button(x, y, cStartIcon->getRect()))
		activeMenuOption = 0;
	else if (is_in_button(x, y, cOption->getRect()))
		activeMenuOption = 1;
	else if (is_in_button(x, y, cRanking->getRect()))
		activeMenuOption = 2;
	else if (is_in_button(x, y, cQuitIcon->getRect()))
		activeMenuOption = 3;
	else
		activeMenuOption = -1;

}