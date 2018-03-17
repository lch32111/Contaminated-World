#include <time.h>

#include "Core.h"
#include "GameItem.h"

GameItem::GameItem()
{

}

GameItem::GameItem(CIMG* item_image, ItemType type)
{
	this->Item = item_image;
	this->eItemtype = type;
	this->Width = Item->getRect().w;
	this->Height = Item->getRect().h;
	this->XPos = this->YPos = 0;
	cursorCollider = DEFAULT_MOVE_COLLIDER;
	rItemCollider[DEFAULT_MOVE_COLLIDER].x = 0;
	rItemCollider[DEFAULT_MOVE_COLLIDER].y = 0;
	rItemCollider[DEFAULT_MOVE_COLLIDER].w = Width;
	rItemCollider[DEFAULT_MOVE_COLLIDER].h = Height;

	this->YAcc = 0;
	this->iSpawnTicks = this->SpawnYmove = this->SpawnMoveTime = 0;
	this->isDrawOnScreen = this->isSpawn = false;
	this->canSpawnYmove = true;
	this->Parabola_a = this->Parabola_b = this->Parabola_c = 0;
}

GameItem::~GameItem()
{

}

void GameItem::ParabolaParameter()
{
	srand((unsigned int)time(NULL));

	unsigned int left_right = rand() % 2; // 0 -> left, 1 right

	int a = rand() % 3;
	if (a == 0) 
		a = -1;
	else 
		a *= -1;

	int b = rand() % 3;
	if (left_right == 0)
		b *= -1;

	int c = -1 * a * b * b;

	Parabola_a = a;
	Parabola_b = b;
	Parabola_c = c;
}

void GameItem::moveItem()
{
	if (Parabola_b > 0)
		UpdateXPos(1);  // to the right
	else
		UpdateXPos(-1); // to the left
}

void GameItem::ItemPhysics()
{
	if(canSpawnYmove)
	{
		float y1, y2;
		
		// y = a(x-b)^2 + c
		y2 = (float)Parabola_a * (SpawnMoveTime - Parabola_b) * (SpawnMoveTime - Parabola_b) + Parabola_c;

		if (SpawnMoveTime > 1)
			if(Parabola_b > 0)
				y1 = (float)Parabola_a * (SpawnMoveTime - 1 - Parabola_b) * (SpawnMoveTime - 1 - Parabola_b) + Parabola_c;
			else
				y1 = (float)Parabola_a * (SpawnMoveTime + 1 - Parabola_b) * (SpawnMoveTime + 1 - Parabola_b) + Parabola_c;
		else
			y1 = 0; 
		
		SpawnYmove = (int)(y2 - y1) * -1;

		if (SpawnYmove > 0)
			YAcc = 7;
		else
			YAcc = 3;

		canSpawnYmove = false;
	}

	if (SpawnYmove > 0)
		--SpawnYmove;
	else if(SpawnYmove < 0)
		++SpawnYmove;

	if (SpawnYmove == 0)
		canSpawnYmove = true;

	// x는 1만큼씩 이동하고, 그 이동의 증가량만큼 y좌표 변경
	if (SpawnYmove > 0)
	{
		// 하강
		YAcc += 0.986 * 0.016;
		UpdateYPos((int)YAcc);
	}
	else
	{
		// 상승
		YAcc -= 0.986 * 0.016;
		UpdateYPos((int)-YAcc);
	}
}

void GameItem::UpdateXPos(int speed)
{
	XPos += speed;
	rItemCollider[cursorCollider].x += speed;

	if ((rItemCollider[cursorCollider].x < 0))
	{
		XPos = 0 - (rItemCollider[cursorCollider].x - XPos);
		rItemCollider[cursorCollider].x = 0;
	}
	else if ((rItemCollider[cursorCollider].x + rItemCollider[cursorCollider].w > SInfo::LEVEL_WIDTH))
	{
		XPos = XPos - (rItemCollider[cursorCollider].x + rItemCollider[cursorCollider].w - SInfo::LEVEL_WIDTH);
		rItemCollider[cursorCollider].x = SInfo::LEVEL_WIDTH - rItemCollider[cursorCollider].w;
	}

	int col;
	if (SCore::getMap()->XCollisionMapObject(&col, &rItemCollider[cursorCollider]))
	{
		int Xpenetration = SCore::getMap()->getXPenetrationDistance(&col, &rItemCollider[cursorCollider]);
		rItemCollider[cursorCollider].x -= Xpenetration;
		XPos -= Xpenetration;
	}
}

void GameItem::UpdateYPos(int speed)
{
	YPos += speed;
	rItemCollider[cursorCollider].y += speed;

	if ((rItemCollider[cursorCollider].y < 0))
	{
		YPos = 0 - (rItemCollider[cursorCollider].y - YPos);
		rItemCollider[cursorCollider].y = 0;
	}
	else if ((rItemCollider[cursorCollider].y + rItemCollider[cursorCollider].h > SInfo::LEVEL_WIDTH))
	{
		YPos = YPos - (rItemCollider[cursorCollider].y + rItemCollider[cursorCollider].h - SInfo::LEVEL_WIDTH);
		rItemCollider[cursorCollider].y = SInfo::LEVEL_WIDTH - rItemCollider[cursorCollider].h;
	}


	int row, col;  // the variables for fast Y axis Collision and Slope Collision
	if (SCore::getMap()->YCollisionMapObject(&row, &speed, &rItemCollider[cursorCollider]))
	{
		int YPenetration = SCore::getMap()->getYPenetrationDistance(&row, &rItemCollider[cursorCollider]);
		rItemCollider[cursorCollider].y -= YPenetration;
		YPos -= YPenetration;

		if (row * 70 > rItemCollider[cursorCollider].y)
			isSpawn = false;
	}

	// Check if the item is in the slope tile
	if (SCore::getMap()->isSlopeTile(&row, &col, &rItemCollider[cursorCollider]) >= 0)
	{
		// the variable for checking if the item is above the real slope while in the slope tile.
		float slope_position = SCore::getMap()->getSlopePosition(&row, &col, &rItemCollider[cursorCollider]);

		// if the item is under the real slope, allocate the slope position into YPos
		if (rItemCollider[cursorCollider].y >= slope_position)
		{
			YPos = slope_position - (rItemCollider[cursorCollider].y - YPos);
			rItemCollider[cursorCollider].y = (int)slope_position;
			isSpawn = false;
		}
	}
}

// parameter : 아이템을 가지는 몬스터의 좌표 및 크기
void GameItem::Spawn(float x, float y, int width, int height)
{
	XPos = x + width / 2;
	YPos = y + height / 2;
	rItemCollider[cursorCollider].x = (int)XPos;
	rItemCollider[cursorCollider].y = (int)YPos;


	this->isDrawOnScreen = this->isSpawn = true;
	ParabolaParameter();
	SInfo::getMusic()->PlayChunk(SInfo::getMusic()->ccoindrop);
}

void GameItem::Acquire()
{
	this->isSpawn = false;
	this->isDrawOnScreen = false;
	SInfo::getMusic()->PlayChunk(SInfo::getMusic()->ccoinacquire);
}

void GameItem::Update()
{
	if (isSpawn)
	{
		if (canSpawnYmove)
		{
			if (Parabola_b > 0)
				++SpawnMoveTime;
			else
				--SpawnMoveTime;
		}

		moveItem();
		ItemPhysics();
	}
}

void GameItem::Draw(SDL_Renderer* rR, SDL_Rect* Camera)
{
	if(isDrawOnScreen)
		Item->Draw(rR, (int)this->XPos - Camera->x, (int)this->YPos - Camera->y, false);

	/* Debug start
	SDL_SetRenderDrawColor(rR, 255, 0, 0, 0xFF);
	SDL_Rect colliR{ rItemCollider[cursorCollider].x - Camera->x, rItemCollider[cursorCollider].y - Camera->y, Width, Height };
	SDL_RenderDrawRect(rR, &colliR);
	*/
}

SDL_Rect GameItem::getRect() { return this->rItemCollider[DEFAULT_MOVE_COLLIDER]; }
bool GameItem::getisSpawn() { return this->isSpawn; }
bool GameItem::getisDrawn() { return this->isDrawOnScreen; }