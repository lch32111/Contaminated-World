#include "PauseMenu.h"
#include "StaticInfo.h"
#include "Core.h"

PauseMenu::PauseMenu()
{
	rPause.x = rPause.y = 0;
	rPause.w = SInfo::SCREEN_WIDTH;
	rPause.h = SInfo::SCREEN_HEIGHT;

	cQuitIcon = SCore::getAssetManager()->getPauseMenuIMG();
	cQuitIcon_over = &cQuitIcon[1];
	cOption = &cQuitIcon[2];
	cOption_over = &cQuitIcon[3];
	cGotoMain = &cQuitIcon[4];
	cGotoMain_over = &cQuitIcon[5];
	cContinueIcon = &cQuitIcon[6];
	cContinueIcon_over = &cQuitIcon[7];


	// Game Play Pause 상태일때 메뉴 (이어하기 / 메인으로 / 옵션 / 게임종료)
	numOfMenu = 4;
	this->menuXpos = SInfo::SCREEN_WIDTH / 2 - cContinueIcon->getRect().w / 2;
	this->menuYpos = SInfo::SCREEN_HEIGHT / 2;
}

void PauseMenu::Update()
{
	SInfo::getMusic()->changeMusic();
	SInfo::getMusic()->PlayMusic();
}

void PauseMenu::Draw(SDL_Renderer* rR)
{
	SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(rR, 4, 4, 4, 205);
	SDL_RenderFillRect(rR, &rPause);

	switch (activeMenuOption)
	{
	case 0:  // 이어하기 활성화
		DrawPauseMenu_over1(rR);
		break;
	case 1:	// 메인으로
		DrawPauseMenu_over2(rR);
		break;
	case 2:	// 옵션
		DrawPauseMenu_over3(rR);
		break;
	case 3:	// 게임종료
		DrawPauseMenu_over4(rR);
		break;
	default:
		DrawPauseMenu(rR);
		break;
	}
}

/*-- Game Play Pause ---*/

void PauseMenu::DrawPauseMenu(SDL_Renderer* rR)
{
	cContinueIcon->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 2 + SInfo::SCREEN_HEIGHT / 20, false);
	cGotoMain->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 3 + SInfo::SCREEN_HEIGHT / 20, false);
	cOption->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 4 + SInfo::SCREEN_HEIGHT / 20, false);
	cQuitIcon->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 5 + SInfo::SCREEN_HEIGHT / 20, false);
}

// 이어하기 메뉴 활성화
void PauseMenu::DrawPauseMenu_over1(SDL_Renderer* rR)
{
	cContinueIcon_over->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 2 + SInfo::SCREEN_HEIGHT / 20, false);
	cGotoMain->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 3 + SInfo::SCREEN_HEIGHT / 20, false);
	cOption->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 4 + SInfo::SCREEN_HEIGHT / 20, false);
	cQuitIcon->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 5 + SInfo::SCREEN_HEIGHT / 20, false);
}

// 메인으로 메뉴 활성화
void PauseMenu::DrawPauseMenu_over2(SDL_Renderer* rR)
{
	cContinueIcon->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 2 + SInfo::SCREEN_HEIGHT / 20, false);
	cGotoMain_over->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 3 + SInfo::SCREEN_HEIGHT / 20, false);
	cOption->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 4 + SInfo::SCREEN_HEIGHT / 20, false);
	cQuitIcon->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 5 + SInfo::SCREEN_HEIGHT / 20, false);
}

// 옵션 메뉴 활성화
void PauseMenu::DrawPauseMenu_over3(SDL_Renderer* rR)
{
	cContinueIcon->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 2 + SInfo::SCREEN_HEIGHT / 20, false);
	cGotoMain->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 3 + SInfo::SCREEN_HEIGHT / 20, false);
	cOption_over->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 4 + SInfo::SCREEN_HEIGHT / 20, false);
	cQuitIcon->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 5 + SInfo::SCREEN_HEIGHT / 20, false);
}

// 게임종료 메뉴 활성화
void PauseMenu::DrawPauseMenu_over4(SDL_Renderer* rR)
{
	cContinueIcon->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 2 + SInfo::SCREEN_HEIGHT / 20, false);
	cGotoMain->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 3 + SInfo::SCREEN_HEIGHT / 20, false);
	cOption->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 4 + SInfo::SCREEN_HEIGHT / 20, false);
	cQuitIcon_over->Draw(rR, menuXpos, SInfo::SCREEN_HEIGHT / 8 * 5 + SInfo::SCREEN_HEIGHT / 20, false);
}

void PauseMenu::enter()
{
	switch (activeMenuOption)
	{
	case 0: // 이어하기
		SInfo::getMM()->setStateID(SInfo::getMM()->eGame);
		break;
	case 1: // 메인으로
		resetGotoMain();
		break;
	case 2: // 옵션 
		SInfo::getMM()->setStateID(SInfo::getMM()->eOption);
		SInfo::getMM()->getOptionMenu()->set_escapeToMainMenu(false);
		break;
	case 3: // 게임 종료
		SInfo::getMM()->getMainMenu()->quitGame();
		break;
	}
}

void PauseMenu::escape()
{
	SInfo::getMM()->setStateID(SInfo::getMM()->eGame);
}

void PauseMenu::click(int x, int y)
{
	switch (activeMenuOption)
	{
		// 이어하기
	case 0:
		if (is_in_button(x, y, cContinueIcon_over->getRect()))
			SInfo::getMM()->setStateID(SInfo::getMM()->eGame);
		break;
		// 메인으로
	case 1:
		if (is_in_button(x, y, cGotoMain->getRect()))
			resetGotoMain();
		break;
		// 옵션 
	case 2:
		SInfo::getMM()->setStateID(SInfo::getMM()->eOption);
		SInfo::getMM()->getOptionMenu()->set_escapeToMainMenu(false);
		break;
		// 게임종료
	case 3:
		if (is_in_button(x, y, cQuitIcon->getRect()))
			SCore::bQuitGame = true;
		break;
	default:
		break;
	}
}


void PauseMenu::checkMouseInput(int x, int y)
{
	if (is_in_button(x, y, cContinueIcon->getRect()))
		activeMenuOption = 0;

	else if (is_in_button(x, y, cGotoMain->getRect()))
		activeMenuOption = 1;

	else if (is_in_button(x, y, cOption->getRect()))
		activeMenuOption = 2;

	else if (is_in_button(x, y, cQuitIcon->getRect()))
		activeMenuOption = 3;

	else
		activeMenuOption = -1;
}

void PauseMenu::resetGotoMain()
{
	SCore::getMap()->setCurrentLevel(0);
	SInfo::getMM()->getUpgradeUI()->setbCalcCoin(false);
	SCore::getMap()->reset();
	SInfo::getMM()->setStateID(SInfo::getMM()->eMainMenu);
	SInfo::getMusic()->PlayMusic(SInfo::getMusic()->mTitle);
}


