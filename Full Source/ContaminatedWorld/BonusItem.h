#ifndef BONUSITEM_H
#define BONUSITEM_H

#include "CIMG.h"
#include "Player.h"

enum class GemType
{
	GEM_BLUE,
	GEM_GREEN,
	GEM_PURPLE,
	GEM_RED,
	GEM_COUNT
};

class BonusItem
{
private:
	CIMG* fBonusItem;
	CIMG* cBonusItem;

	//Player* pBonusItem;
	GemType eGemType;
	int XPos, YPos;
	int fXPos, fYPos;
	float YAcc;

	enum Gem_Collider
	{
		GEM_BLUE_COLLIDER,
		GEM_GREEN_COLLIDER,
		GEM_PURPLE_COLLIDER,
		GEM_RED_COLLIDER,
		GEM_COLLIDER_COUNT
	};
	Gem_Collider cursorCollider;
	SDL_Rect rBonusItemCollider[Gem_Collider::GEM_COLLIDER_COUNT];

	int SpawnMoveTime;
	int SpawnYmove;
	int iSpawnTicks;

	bool isSpawn;

	bool isDrawn;
	bool isAcquired;
	bool canDrawAcquired;

	void UpdateYPos(int speed);
	void BonusItemPhysics();

	bool isGround;
public:
	BonusItem();
	BonusItem(CIMG* bonusitem_image, GemType type, int x, int y);
	BonusItem(CIMG* bonusitem_image, GemType type);
	~BonusItem();

	unsigned int iTimeLasting; // 보너스 아이템 지속시간

	void SpawnItem();
	void SpawnPos(int x, int w);

	void Acquire();

	void Update();
	void Draw(SDL_Renderer* rR, SDL_Rect* Camera);
	void Drawf(SDL_Renderer* rR);

	/*----- get & set -----*/
	SDL_Rect getColliderRect(GemType gemtype);
	GemType getGemType(int i);
	bool getisSpawn();
	bool getisDrawn();
	bool getisAcquired();
	bool get_canDrawAcquired();
	void set_isDrawn(bool b);
	void setfXYpos(int x, int y);
};

#endif

