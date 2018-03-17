#pragma once

#ifndef MAP_H
#define MAP_H

#include "CIMG.h"
#include "PIMG.h"
#include "Player.h"
#include "Monster_Munzi.h"
#include "Monster_Orc.h"
#include "MapObject.h"
#include "MapLevel.h"
#include "GameItem.h"
#include "BitmapText.h"
#include "RMedicine.h"
#include "BonusItem.h"
#include <vector>

class Map
{
private:
	bool bStageStart;
	bool bStageEnd;
	bool bStageFail;
	bool bGameSuccess;

	CIMG* cBackground;

	Player* Character;
	int player_number_material;
	int player_kill_monster;
	int player_hitted_number;

	RMedicine* medicine;
	std::vector<M_Munzi*> vM_Munzi;
	std::vector<M_Orc*> vM_Orc;
	int number_monster;

	int number_item;
	int number_spawnitem;
	GameItem* testItem;
	Bitmap_Text* Text;

	// BonusItem
	BonusItem* bonusItem[4];
	bool canGetSpawnTime;
	int SpawnTime[4];
	int BonusOrder[4];
	BonusItem* fbonusItem[8];

	// Map Objeet
	std::vector<MapObject*> Map_Object;
	std::vector<MapLevel*> Object_Place;
	int currentLevelID;
	int Tile_Width;
	int Tile_Height;

	unsigned int iFrametime;
	unsigned int iFrametime2;
	int iMapTime;	// count용 시간
	int iMapTime2;	// 남은시간

	SDL_Rect Camera;

	void LoadTestData();

	void Demo_Map();
	void Demo_Map2();
	void Demo_Map3();
	void Demo_Map4();
	void Demo_Map5();
	
	void UpdatePlayer();
	void UpdateMonster();
	void UpdateMedicine();
	void UpdateItem();
	void UpdateCamera();
	void UpdateBonusItem();

	void DrawMap(SDL_Renderer* rR);
	void DrawCharacter(SDL_Renderer* rR);
	void DrawMonster(SDL_Renderer* rR);
	void DrawItem(SDL_Renderer* rR);
	void DrawGameLayout(SDL_Renderer* rR);
	void DrawBonusItem(SDL_Renderer* rR);
	void SpawnItem();
	void SpawnMonster();

public:
	Map();
	Map(const char* anything);
	~Map();

	void Draw(SDL_Renderer* rR);
	void DrawBonusItemUI(SDL_Renderer* rR);

	void LoadLVL();
	// Updated Collision Functions Start

	// Monster SpawnTime
	bool SpawnMonstertime[30];

	// Character <-> Monster
	bool CollisionCharacter(const SDL_Rect* Target);
	bool AttackCollisionCharacter(const SDL_Rect* Target);
	bool CollisionMonster(const SDL_Rect* Target);
	bool AttackCollisionMonster(const SDL_Rect* Target);

	// Monster <-> Medicine
	bool CollisionBodyMonster(const SDL_Rect* Target); // 몸으로 공격하는 몬스터(ex. 먼지)와 Medicine Collision Detect
	bool AttackCollisionMedicine(const SDL_Rect* Target);

	bool XCollisionMapObject(int* object_col, const SDL_Rect* Target);
	int getXPenetrationDistance(const int* object_col, const SDL_Rect* Target);
	
	int getBottomCollidedPlatformType(const SDL_Rect* Target);
	bool YCollisionMapObject(int* object_row, const int* speed, const SDL_Rect* Target);
	bool YTopCollisionMapObject(int* object_row, const SDL_Rect* Target);
	bool YBottomCollisionMapObject(int* object_row, const SDL_Rect* Target);
	int getYPenetrationDistance(const int* object_row, const SDL_Rect* Target);
	
	int isSlopeTile(int* object_row, int* object_col, const SDL_Rect* Target);
	float getSlopePosition(const int* object_row, const int* object_col, const SDL_Rect* Target);
	// Updated Collision Functions End

	// BonusItem Variables
	bool bBonusOrder0, bBonusOrder1, bBonusOrder2, bBonusOrder3;

	void Update();
	void reset();
	void resetBonusItem();

	void UpdateScore();
	void set_iMapTime2(int time); // iMapTime2(남은시간) 감소
	bool getbStageEnd();

	// Upgrade UI 경고문구
	void DrawMedicineFullHPText(SDL_Renderer* rR);
	void DrawCharacterFullHPText(SDL_Renderer* rR);

	/* ----- get & set ----- */
	Player* getPlayer();
	RMedicine* getMedicine();
	std::vector<M_Munzi*> getVecMunzi();
	std::vector<M_Orc*> getVecOrc();
	Bitmap_Text* getText();
	int getCurrentLevel();
	void setCurrentLevel(int lv);
};
#endif