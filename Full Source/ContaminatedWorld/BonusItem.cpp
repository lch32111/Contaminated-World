#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "Core.h"
#include "BonusItem.h"
//#include "Player.h"

BonusItem::BonusItem() { }

// Èæ¹é fBonusItem Layout
BonusItem::BonusItem(CIMG* item_image, GemType type, int x, int y)
{
	this->fBonusItem = item_image;
	this->eGemType = type;
	this->fXPos = x;
	this->fYPos = y;

	// bonus item variable
	this->cBonusItem = item_image;
	this->eGemType = type;
	this->XPos = 0;
	this->YPos = 0;
	switch (type)
	{
	case GemType::GEM_BLUE:
		cursorCollider = GEM_BLUE_COLLIDER;
		rBonusItemCollider[GEM_BLUE_COLLIDER] = { 0, 0, 0, 0 };
		break;
	case GemType::GEM_GREEN:
		cursorCollider = GEM_GREEN_COLLIDER;
		rBonusItemCollider[GEM_GREEN_COLLIDER] = { 0, 0, 0, 0 };
		break;
	case GemType::GEM_PURPLE:
		cursorCollider = GEM_PURPLE_COLLIDER;
		rBonusItemCollider[GEM_PURPLE_COLLIDER] = { 0, 0, 0, 0 };
		break;
	case GemType::GEM_RED:
		cursorCollider = GEM_RED_COLLIDER;
		rBonusItemCollider[GEM_RED_COLLIDER] = { 0, 0, 0, 0 };
		break;
	}

	this->YAcc = 0;
	this->iSpawnTicks = this->SpawnYmove = this->SpawnMoveTime = 0;
	this->isDrawn = this->isSpawn = false;
	this->isAcquired = false;
	this->isGround = false;
	this->canDrawAcquired = false;
	this->iTimeLasting = SDL_GetTicks();
}

// È­¸é¿¡¼­ ¶³¾îÁö°í ½ÀµæÇÒ cBonusItem
BonusItem::BonusItem(CIMG* item_image, GemType type)
{
	srand((unsigned int)time(NULL));
	this->cBonusItem = item_image;
	this->eGemType = type;
	this->XPos = 0;
	this->YPos = 0;

	switch (type)
	{
	case GemType::GEM_BLUE:
		cursorCollider = GEM_BLUE_COLLIDER;
		rBonusItemCollider[GEM_BLUE_COLLIDER] = { 7, 4, 17, 21 };
		break;
	case GemType::GEM_GREEN:
		cursorCollider = GEM_GREEN_COLLIDER;
		rBonusItemCollider[GEM_GREEN_COLLIDER] = { 6, 6, 19, 20 };
		break;
	case GemType::GEM_PURPLE:
		cursorCollider = GEM_PURPLE_COLLIDER;
		rBonusItemCollider[GEM_PURPLE_COLLIDER] = { 6, 6, 19, 19 };
		break;
	case GemType::GEM_RED:
		cursorCollider = GEM_RED_COLLIDER;
		rBonusItemCollider[GEM_RED_COLLIDER] = { 7, 6, 17, 21 };
		break;
	}

	this->YAcc = 0;
	this->iSpawnTicks = this->SpawnYmove = this->SpawnMoveTime = 0;
	this->isDrawn = this->isSpawn = false;
	this->isAcquired = false;
	this->isGround = false;
	this->canDrawAcquired = false;
	this->iTimeLasting = SDL_GetTicks();

	// fbonus item variable
	this->fBonusItem = item_image;
	this->eGemType = type;
	this->fXPos = 0;
	this->fYPos = 0;
}

BonusItem::~BonusItem() { }

void BonusItem::BonusItemPhysics()
{
	UpdateYPos(3);
}

void BonusItem::UpdateYPos(int speed)
{
	YPos += speed;
	rBonusItemCollider[cursorCollider].y += speed;

	if ((rBonusItemCollider[cursorCollider].y < 0))
	{
		YPos = 0 - (rBonusItemCollider[cursorCollider].y - YPos);
		rBonusItemCollider[cursorCollider].y = 0;
	}
	else if ((rBonusItemCollider[cursorCollider].y + rBonusItemCollider[cursorCollider].h > SInfo::LEVEL_WIDTH))
	{
		YPos = YPos - (rBonusItemCollider[cursorCollider].y + rBonusItemCollider[cursorCollider].h - SInfo::LEVEL_WIDTH);
		rBonusItemCollider[cursorCollider].y = SInfo::LEVEL_WIDTH - rBonusItemCollider[cursorCollider].h;
	}


	int row, col;  // the variables for fast Y axis Collision and Slope Collision
	if (SCore::getMap()->YCollisionMapObject(&row, &speed, &rBonusItemCollider[cursorCollider]))
	{
		int YPenetration = SCore::getMap()->getYPenetrationDistance(&row, &rBonusItemCollider[cursorCollider]);
		rBonusItemCollider[cursorCollider].y -= YPenetration;
		YPos -= YPenetration;

		if (row * 70 > rBonusItemCollider[cursorCollider].y)
			isSpawn = false;
	}

	// Check if the item is in the slope tile
	if (SCore::getMap()->isSlopeTile(&row, &col, &rBonusItemCollider[cursorCollider]) >= 0)
	{
		// the variable for checking if the item is above the real slope while in the slope tile.
		float slope_position = SCore::getMap()->getSlopePosition(&row, &col, &rBonusItemCollider[cursorCollider]);

		// if the item is under the real slope, allocate the slope position into YPos
		if (rBonusItemCollider[cursorCollider].y >= slope_position)
		{
			YPos = slope_position - (rBonusItemCollider[cursorCollider].y - YPos);
			rBonusItemCollider[cursorCollider].y = (int)slope_position;
			isSpawn = false;
		}
	}
}

void BonusItem::SpawnPos(int x, int w)
{
	// x is Player's Xpos, w is Player's Width
	if ((x + (w / 2)) <= 500)
		XPos = (rand() % 950) + 25;
	else if ((x + (w / 2)) >= 3000)
		XPos = (rand() % 950) + 2475;
	else
		XPos = (rand() % 950) + ((x + (w / 2)) - 475);
	YPos = (rand() % 150) + 50;

	rBonusItemCollider[cursorCollider].x = (int)XPos;
	rBonusItemCollider[cursorCollider].y = (int)YPos;

	this->isDrawn = this->isSpawn = true;
	this->iTimeLasting = SDL_GetTicks(); // bonus item time lasting
	SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cBonusSpawn); //GEM SPAWN SOUNDS
}

void BonusItem::Acquire()
{
	isAcquired = true;
	isDrawn = false;
	canDrawAcquired = true;
	isSpawn = false;
	SInfo::getMusic()->PlayChunk(SInfo::getMusic()->ccoinacquire);
}

void BonusItem::Update()
{
	if (getisSpawn())
	{
		BonusItemPhysics();
	}
}

void BonusItem::Draw(SDL_Renderer* rR, SDL_Rect* Camera)
{
	cBonusItem->Draw(rR, (int)this->XPos - Camera->x, (int)this->YPos - Camera->y, false);
}

void BonusItem::Drawf(SDL_Renderer* rR)
{
	fBonusItem->Draw(rR, fXPos, fYPos, false);
}

SDL_Rect BonusItem::getColliderRect(GemType gemtype) 
{
	switch (gemtype) 
	{
	case GemType::GEM_BLUE:
		return rBonusItemCollider[GEM_BLUE_COLLIDER]; break;
	case GemType::GEM_GREEN:
		return rBonusItemCollider[GEM_GREEN_COLLIDER]; break;
	case GemType::GEM_PURPLE:
		return rBonusItemCollider[GEM_PURPLE_COLLIDER]; break;
	case GemType::GEM_RED:
		return rBonusItemCollider[GEM_RED_COLLIDER]; break;
	}
}
GemType BonusItem::getGemType(int i)
{
	switch (i)
	{
	case 0:
		return GemType::GEM_BLUE;
		break;
	case 1:
		return GemType::GEM_GREEN;
		break;
	case 2:
		return GemType::GEM_PURPLE;
		break;
	case 3:
		return GemType::GEM_RED;
		break;
	}
}

bool BonusItem::getisSpawn() { return isSpawn; }
bool BonusItem::getisDrawn() { return isDrawn; }
bool BonusItem::getisAcquired() { return isAcquired; }
bool BonusItem::get_canDrawAcquired() { return canDrawAcquired; }
void BonusItem::set_isDrawn(bool b) { this->isDrawn = b; }
void BonusItem::setfXYpos(int x, int y) 
{
	this->fYPos = y; 
}

