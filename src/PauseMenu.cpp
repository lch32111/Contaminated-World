#include "PauseMenu.h"
#include "StaticInfo.h"
#include "Core.h"

PauseMenu::PauseMenu()
{
	rPause.x = rPause.y = 0;
	rPause.w = SInfo::GAME_WIDTH;
	rPause.h = SInfo::GAME_HEIGHT;

	// PauseMenu의 메뉴는 2개 (이어하기 / 게임종료)
	numOfMenu = 2;
}


void PauseMenu::Draw(SDL_Renderer* rR)
{
	SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(rR, 4, 4, 4, 205);
	SDL_RenderFillRect(rR, &rPause);

	switch (activeMenuOption)
	{
		case 0:
			SCore::getMap()->DrawMenu(rR);
			break;
		case 1:
			SCore::getMap()->DrawMenu_over(rR);
			break;
	}

	
}

void PauseMenu::enter()
{
	switch(activeMenuOption)
	{
		// 이어하기
		case 0:
			SInfo::getMM()->setStateID(SInfo::getMM()->eGame);
			break;
		// 게임 종료
		case 1:
			SCore::bQuitGame = true;
			break;
	}
}


void PauseMenu::escape()
{
	SInfo::getMM()->setStateID(SInfo::getMM()->eGame);
}


void PauseMenu::activeOption(int key)
{
	Menu::activeOption(key);

}