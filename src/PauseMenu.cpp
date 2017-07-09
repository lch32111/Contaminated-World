#include "PauseMenu.h"
#include "StaticInfo.h"

PauseMenu::PauseMenu()
{
	rPause.x = rPause.y = 0;
	rPause.w = SInfo::GAME_WIDTH;
	rPause.h = SInfo::GAME_HEIGHT;
}


void PauseMenu::Draw(SDL_Renderer* rR)
{
	SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(rR, 4, 4, 4, 235);
	SDL_RenderFillRect(rR, &rPause);
	SDL_SetRenderDrawColor(rR, 255, 255, 255, 255); // Å×µÎ¸®

}