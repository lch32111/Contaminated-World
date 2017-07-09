#include "Map.h"
#include "StaticInfo.h"

//--
Map::Map()
{

}

Map::Map(SDL_Renderer* rR)
{
	Character = new Player(rR, SInfo::GAME_WIDTH / 2, SInfo::GAME_HEIGHT / 2);
	LoadTestData(rR);
}

void Map::LoadTestData(SDL_Renderer* rR)
{
	Background.setIMG("background", rR);
	Monster.setIMG("monster", rR);
	QuitIcon.setIMG("quit_icon", rR);
	QuitIcon_over.setIMG("quit_icon_over", rR);
	ContinueIcon.setIMG("continue_icon", rR);
	ContinueIcon_over.setIMG("continue_icon_over", rR);
}

void Map::Draw(SDL_Renderer* rR)
{
	DrawBackground(rR);
	DrawCharacter(rR);
	DrawMonster(rR);
}

void Map::DrawBackground(SDL_Renderer* rR)
{
	Background.Draw(rR, 0, 0, false);
}

void Map::DrawCharacter(SDL_Renderer* rR)
{
	Character->Draw(rR, Character->getXPos(), Character->getYPos(), Character->getRotate());
}

void Map::DrawMonster(SDL_Renderer* rR)
{
	Monster.Draw(rR, SInfo::GAME_WIDTH / 4, SInfo::GAME_HEIGHT / 3, false);
}

//--
void Map::DrawMenu(SDL_Renderer* rR)
{
	ContinueIcon_over.Draw(rR, SInfo::ContinueMenuXpos, SInfo::ContinueMenuYpos, false);
	QuitIcon.Draw(rR, SInfo::QuitMenuXpos, SInfo::QuitMenuYpos, false);
}


void Map::DrawMenu_over(SDL_Renderer* rR)
{
	ContinueIcon.Draw(rR, SInfo::ContinueMenuXpos, SInfo::ContinueMenuYpos, false);
	QuitIcon_over.Draw(rR, SInfo::QuitMenuXpos, SInfo::QuitMenuYpos, false);
}


void Map::Update()
{
	UpdatePlayer();
}

void Map::UpdatePlayer()
{
	Character->Update();
}

Player* Map::getPlayer() { return Character; }