#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "CIMG.h"

enum class ItemType
{
	ITEM_RADIOACTIVE_MATERIAL,
	ITEM_COUNT
};

class GameItem
{
private:
	CIMG* Item;
	ItemType eItemtype;
	float XPos, YPos;
	float YAcc;
	int Width, Height;

	enum Item_Collider
	{
		DEFAULT_MOVE_COLLIDER,
		ITEM_COLLIDER_COUNT
	};
	Item_Collider cursorCollider;
	SDL_Rect rItemCollider[Item_Collider::ITEM_COLLIDER_COUNT];

	int SpawnMoveTime;
	int SpawnYmove;
	int iSpawnTicks;
	bool isSpawn;
	bool canSpawnYmove;
	bool isDrawOnScreen;
	int Parabola_a, Parabola_b, Parabola_c; // for Parabola movement

	void ParabolaParameter();
	void UpdateXPos(int speed);
	void UpdateYPos(int speed);
	void moveItem();
	void ItemPhysics();
public:
	GameItem();
	GameItem(CIMG* item_image, ItemType type);
	~GameItem();

	void Spawn(float x, float y, int width, int height);
	void Acquire();
	
	void Update();
	void Draw(SDL_Renderer* rR, SDL_Rect* Camera);

	SDL_Rect getRect();
	bool getisSpawn();
	bool getisDrawn();
};

#endif