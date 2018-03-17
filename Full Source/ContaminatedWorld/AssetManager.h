#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include "CIMG.h"
#include "PIMG.h"
#include "MapObject.h"
#include "MapLevel.h"
#include "FileParser.h"
#include "BitmapText.h"
#include "RMedicine.h"
#include "GameItem.h"
#include "Player.h"
#include "Monster_Munzi.h"
#include "Monster_Orc.h"
#include "Upgrade.h"
#include "BonusItem.h"

// Rank Information
typedef struct RankInfo
{
	int rankTable_size;
	std::vector<std::string> vRank_Number;
	std::vector<std::string> vRank_Name;
	std::vector<std::string> vRank_Score;
	std::vector<std::string> vRank_Thought;
} RankInfo;

class AssetManager
{
private:
	static CIMG CharacterIMG[61];
	static CIMG CharacterWeaponIMG[2];

	FileParser MapObject_Parser;
	CIMG MapObjectIMG[20];

	static CIMG MedicineIMG;

	static CIMG Monster_MunziIMG[30];
	static CIMG Monster_OrcIMG[17];
	static CIMG Monster_BloodIMG;

	static CIMG GameItemIMG;

	static CIMG BonusItemIMG[4];
	static CIMG FBonusItemIMG[8]; // Èæ¹é º¸³Ê½º ·¹ÀÌ¾Æ¿ô

	CIMG TitleIMG;
	CIMG MainMenuBackgroundIMG;
	CIMG MainMenuBoxIMG[8];
	CIMG PauseMenuIMG[8];
	CIMG UpgradeIMG[30];
	CIMG EndingMenuIMG[4];
	CIMG RankingMenuIMG;
	CIMG MapBackgroundIMG[2];

	PIMG FontIMG;

	RankInfo RankTable;
	void readRankTable();
public:
	AssetManager();
	AssetManager(SDL_Renderer* rR);
	~AssetManager();

	static Player player;
	static int MapObject_number;
	static MapObject MapObject_info[20];
	static MapLevel Demo_MapLevel;
	static MapLevel Demo_MapLevel2;
	static RMedicine Medicine;

	static M_Munzi Demo_Map_Munzi[3];

	// Map 2 : 10
	static M_Munzi Demo_Map2_Munzi[5];
	static M_Orc Demo_Map2_Orc[5];

	// Map 3 : 14
	static M_Munzi Demo_Map3_Munzi[7];
	static M_Orc Demo_Map3_Orc[7];

	// MAP 4 : 18
	static M_Munzi Demo_Map4_Munzi[18];

	// MAP 5 : 22
	static M_Munzi Demo_Map5_Munzi[12];
	static M_Orc Demo_Map5_Orc[12];

	static const int number_gameitem = 500;
	static GameItem gameitem[number_gameitem];
	
	static BonusItem bonusitem[4];
	static BonusItem fbonusitem[8];

	static Bitmap_Text BText;
	
	static void AssetReset();
	static void BonusItemReset();

	CIMG* getTitleIMG();
	CIMG* getMainmenuBackgroundIMG();
	CIMG* getMainmenuBoxIMG();
	CIMG* getPauseMenuIMG();
	CIMG* getUpgradeIMG();
	CIMG* getEndingMenuIMG();
	CIMG* getRankingMenuIMG();
	CIMG* getMapBackgroundIMG();

	RankInfo* getRankInfo();
	RankInfo* getLatestRankInfo();
};


#endif