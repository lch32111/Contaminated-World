#include "Map.h"
#include "StaticInfo.h"

//--
Map::Map()
{
	
}

Map::Map(SDL_Renderer* rR)
{
	Character = new Player(rR, SInfo::GAME_WIDTH / 1.5, SInfo::GAME_HEIGHT / 2);
	Monster.push_back(new CIMG("monster", rR));
	Monster.push_back(new CIMG("monster", rR));
	LoadTestData(rR);
}

void Map::LoadTestData(SDL_Renderer* rR)
{
	Background.setIMG("background", rR);
	Menu.setIMG("quit_icon", rR);
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
	Monster[0]->Draw(rR, SInfo::GAME_WIDTH / 6, SInfo::GAME_HEIGHT / 1.5, false);
	Monster[1]->Draw(rR, SInfo::GAME_WIDTH / 1.8, SInfo::GAME_HEIGHT / 1.5, false);
}

void Map::DrawMenu(SDL_Renderer* rR)
{
	Menu.Draw(rR, SInfo::MenuXpos, SInfo::MenuYpos, false);
}

bool Map::CollisionMonster()
{
	int Collision = 0;

	for (int i = 0; i < Monster.size(); ++i)
	{
		int x = Monster[i]->getRect().x;
		int y = Monster[i]->getRect().y;
		int w = Monster[i]->getRect().w;
		int h = Monster[i]->getRect().h;

		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		leftA = x;
		rightA = x + w;
		topA = y;
		bottomA = y + h;

		leftB = Character->getXPos();
		rightB = Character->getXPos() + Character->getWidth();
		topB = Character->getYPos();
		bottomB = Character->getYPos() + Character->getHeight();

		if (bottomA <= topB)
			++Collision;
		if (topA >= bottomB)
			++Collision;
		if (rightA <= leftB)
			++Collision;
		if (leftA >= rightB)
			++Collision;

		if (Collision == 0)
		{
			printf("Ãæµ¹\n");
			return true;
		}

		Collision = 0;
	}

	return false;
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