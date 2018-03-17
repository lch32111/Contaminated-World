#include "AssetManager.h"

Player AssetManager::player;
CIMG AssetManager::CharacterIMG[61];
CIMG AssetManager::CharacterWeaponIMG[2];

int AssetManager::MapObject_number = 0;
MapObject AssetManager::MapObject_info[20];
MapLevel AssetManager::Demo_MapLevel;
MapLevel AssetManager::Demo_MapLevel2;
RMedicine AssetManager::Medicine;
CIMG AssetManager::MedicineIMG;

// Demo_Map start
M_Munzi AssetManager::Demo_Map_Munzi[3];
M_Munzi AssetManager::Demo_Map2_Munzi[5];
M_Orc AssetManager::Demo_Map2_Orc[5];

M_Munzi AssetManager::Demo_Map3_Munzi[7];
M_Orc AssetManager::Demo_Map3_Orc[7];

M_Munzi AssetManager::Demo_Map4_Munzi[18];

M_Munzi AssetManager::Demo_Map5_Munzi[12];
M_Orc AssetManager::Demo_Map5_Orc[12];

// Demo_Map over

CIMG AssetManager::Monster_MunziIMG[30];
CIMG AssetManager::Monster_OrcIMG[17];
CIMG AssetManager::Monster_BloodIMG;

CIMG AssetManager::GameItemIMG;

GameItem AssetManager::gameitem[number_gameitem];

CIMG AssetManager::FBonusItemIMG[8];
BonusItem AssetManager::fbonusitem[8];

CIMG AssetManager::BonusItemIMG[4];
BonusItem AssetManager::bonusitem[4];

Bitmap_Text AssetManager::BText;

AssetManager::AssetManager() {}

AssetManager::AssetManager(SDL_Renderer* rR)
{
	int IMGIndex = 0;
	CharacterIMG[IMGIndex].setIMG("character/character", rR); ++IMGIndex; // Default 0
	CharacterIMG[IMGIndex].setIMG("character/run1", rR); ++IMGIndex;      // Run 1
	CharacterIMG[IMGIndex].setIMG("character/run2", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run3", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run4", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run5", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run6", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run7", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run8", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run9", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run10", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run11", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run12", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/run13", rR); ++IMGIndex;     // Run 13
	CharacterIMG[IMGIndex].setIMG("character/jump1", rR); ++IMGIndex;     // Jump 14
	CharacterIMG[IMGIndex].setIMG("character/jump2", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/jump3", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/jump4", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/jump5", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/jump6", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/jump7", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/jump8", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/jump9", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/jump10", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/jump11", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/jump12", rR); ++IMGIndex;    // Jump 25
	CharacterIMG[IMGIndex].setIMG("character/fall1", rR); ++IMGIndex;     // Fall 26
	CharacterIMG[IMGIndex].setIMG("character/fall2", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/fall3", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/fall4", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/fall5", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/fall6", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/fall7", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/fall8", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/fall9", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/fall10", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/fall11", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/fall12", rR); ++IMGIndex;    // Fall 37
	CharacterIMG[IMGIndex].setIMG("character/hit1", rR); ++IMGIndex;      // Hit 38
	CharacterIMG[IMGIndex].setIMG("character/hit2", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/hit3", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/hit4", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/hit5", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/hit6", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/hit7", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/hit8", rR); ++IMGIndex;      // Hit 45 Collision point
	CharacterIMG[IMGIndex].setIMG("character/hit9", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/hit10", rR); ++IMGIndex;     // Hit 47
	CharacterIMG[IMGIndex].setIMG("character/hitted", rR); ++IMGIndex;    // Hitted 48
	CharacterIMG[IMGIndex].setIMG("character/die1", rR); ++IMGIndex;      // Die 49
	CharacterIMG[IMGIndex].setIMG("character/die2", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/die3", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/die4", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/die5", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/die6", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/die7", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/die8", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/die9", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/die10", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/die11", rR); ++IMGIndex;
	CharacterIMG[IMGIndex].setIMG("character/die12", rR);

	IMGIndex = 0;
	CharacterWeaponIMG[IMGIndex].setIMG("test/spear1", rR); ++IMGIndex;
	CharacterWeaponIMG[IMGIndex].setIMG("test/spear2", rR);
	player = Player(CharacterIMG, CharacterWeaponIMG, 24 * 70, 100);

	// Map Object Loading Start
	{
		IMGIndex = 0;
		int l_error = MapObject_Parser.OpenFile("FirstTestMapObject.cwmo");
		if (l_error < 0) printf("Cannot open cwmo file\n");
		bool l_success = false;
		MapObject_number = 0;
		l_success = MapObject_Parser.get_Numb_MabObject_Fromcwmo(&MapObject_number);
		if (!l_success) printf("Cannot read Numberof Mab object data\n");

		int index = 0; char address[50]; int type = 0;
		int Slopey1 = 0, Slopey2 = 0;
		for (int i = 0; i < MapObject_number; ++i)
		{
			l_success = MapObject_Parser.get_OneMapObject_Info_Fromcwmo(&index, address, &type);
			if (!l_success) printf("Cannot read Mab object information data\n");
			MapObjectIMG[i].setIMG(address, rR);

			if (type == 2) // Slope
			{
				l_success = MapObject_Parser.get_SlopeInfo_Fromcwmo(&Slopey1, &Slopey2);
				if (!l_success) printf("Cannot read slope information\n");
				
				MapObject_info[i] = MapObject(&MapObjectIMG[i], index, type, Slopey1, Slopey2);
			}
			else
				MapObject_info[i] = MapObject(&MapObjectIMG[i], index, type);
		}
		MapObject_Parser.~FileParser();
	}
	// Map Object Loading End

	// Demo Map Level Loading Start
	{
		int l_error = MapObject_Parser.OpenFile("FirstTest.cwm");
		if (l_error < 0) printf("Cannot open cwm file\n");

		int row{ 0 }, col{ 0 };
		std::vector<std::vector<int>> vec;
		bool l_success = false;
		l_success = MapObject_Parser.getRowFromcwm(&row);
		if (!l_success) printf("Cannot retrieve row data\n");

		l_success = MapObject_Parser.getColFromcwm(&col);
		if (!l_success) printf("Cannot retrieve col data\n");

		l_success = MapObject_Parser.getVecFromcwm(vec, row, col);
		if (!l_success) printf("Cannot retrieve vector data\n");
		Demo_MapLevel = MapLevel(vec, row, col);
		MapObject_Parser.~FileParser();
	}
	// Demo Map Level Loading End

	// Demo Map Level2 Loading Start
	{
		int l_error = MapObject_Parser.OpenFile("SecondTest.cwm");
		if (l_error < 0) printf("Cannot open cwm file\n");

		int row{ 0 }, col{ 0 };
		std::vector<std::vector<int>> vec;

		bool l_success = false;
		l_success = MapObject_Parser.getRowFromcwm(&row);
		if (!l_success) printf("Cannot retrieve row data\n");
	
		l_success = MapObject_Parser.getColFromcwm(&col);
		if (!l_success) printf("Cannot retrieve col data\n");

		l_success = MapObject_Parser.getVecFromcwm(vec, row, col);
		if (!l_success) printf("Cannot retrieve vector data\n");

		Demo_MapLevel2 = MapLevel(vec, row, col);
		MapObject_Parser.~FileParser();
	}
	// Demo Map Level2 Loading End

	// Rank Table File Loading Start
	{
		readRankTable();
	}
	// Rank Table File Loading End


	IMGIndex = 0;
	MedicineIMG.setIMG("test/medicine", rR);
	Medicine = RMedicine(&MedicineIMG, 500, 200);

	IMGIndex = 0;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster1", rR); ++IMGIndex;                 // Idle 0
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster2", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster3", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster4", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster5", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster6", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster7", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster8", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster9", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster10", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster11", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster12", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster13", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster14", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/monster15", rR); ++IMGIndex;                // Idle 14
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster1", rR); ++IMGIndex;  // Attack 15
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster2", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster3", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster4", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster5", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster6", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster7", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster8", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster9", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster10", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster11", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster12", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster13", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster14", rR); ++IMGIndex;
	Monster_MunziIMG[IMGIndex].setIMG("monster/munzi/attack_monster/monster15", rR);			  // Attack 29
	
	IMGIndex = 0;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run0", rR); ++IMGIndex;    // Run 0
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run1", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run2", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run3", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run4", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run5", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run6", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run7", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run8", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run9", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/run10", rR); ++IMGIndex;   // Run 10
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/attack0", rR); ++IMGIndex; // Attack 11
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/attack1", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/attack2", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/attack3", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/attack4", rR); ++IMGIndex;
	Monster_OrcIMG[IMGIndex].setIMG("monster/orc/attack5", rR);				// Attack 16

	IMGIndex = 0;
	Monster_BloodIMG.setIMG("monster/orc/blood", rR);

	// Map Monster Setting Start
	IMGIndex = 0;
	// MAP 2
	Demo_Map2_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 1 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 49 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 3 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 3 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 48 * 70, 2 * 70, IMGIndex); ++IMGIndex;

	IMGIndex = 0;
	Demo_Map2_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 49 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 1 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 1 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 45 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 47 * 70, 2 * 70, IMGIndex); ++IMGIndex;

	// MAP 3
	IMGIndex = 0;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 49 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 3 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 49 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 5 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 49 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 5 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 49 * 65, 2 * 70, IMGIndex); ++IMGIndex;

	IMGIndex = 0;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 1 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 3 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 47 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 3 * 60, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 5 * 60, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 49 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 1 * 70, 2 * 70, IMGIndex); ++IMGIndex;

	// MAP 4
	IMGIndex = 0;
	int m_number = 9; // Total Monster Number is 18 -> 18/2 = 9
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map4_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, ((IMGIndex)+1) * 60, 2 * 70, IMGIndex);
	IMGIndex = 0;
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map4_Munzi[IMGIndex + m_number] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, (55 - (IMGIndex)) * 60, 2 * 70, IMGIndex + m_number);

	// MAP 5
	m_number = 6; // Total Monster Number is 12 -> 12/2 = 6

				  // MUNZI : LEFTSIDE
	IMGIndex = 0;
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map5_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, ((IMGIndex)+1) * 50, 2 * 70, IMGIndex);
	//  MUNZI : RIGHTSIDE
	IMGIndex = 0;
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map5_Munzi[IMGIndex + m_number] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, (55 - (IMGIndex)) * 60, 2 * 70, IMGIndex + m_number);

	m_number = 6; // Total Monster Number is 12 -> 12/2 = 6

				  // ORC : LEFTSIDE
	IMGIndex = 0;
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map5_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, ((IMGIndex)+1) * 50, 2 * 70, IMGIndex);
	// ORC : RIGHTSIDE
	IMGIndex = 0;
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map5_Orc[IMGIndex + m_number] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, (55 - (IMGIndex)) * 60, 2 * 70, IMGIndex + m_number);

	// Map Monster Setting End

	IMGIndex = 0;
	GameItemIMG.setIMG("test/test", rR);
	for(int i = 0; i < number_gameitem; ++i)
		gameitem[i] = GameItem(&GameItemIMG, ItemType::ITEM_RADIOACTIVE_MATERIAL);

	// Bonus Item, Èæ¹é
	IMGIndex = 0;
	FBonusItemIMG[IMGIndex].setIMG("BonusItem/fBlue", rR); ++IMGIndex; // BLUE : 0
	FBonusItemIMG[IMGIndex].setIMG("BonusItem/fGreen", rR); ++IMGIndex; // GREEN : 1
	FBonusItemIMG[IMGIndex].setIMG("BonusItem/fPurple", rR); ++IMGIndex; // PURPLE : 2
	FBonusItemIMG[IMGIndex].setIMG("BonusItem/fRed", rR); ++IMGIndex; // RED : 3

	FBonusItemIMG[IMGIndex].setIMG("BonusItem/cBlue", rR); ++IMGIndex; // cBLUE : 4
	FBonusItemIMG[IMGIndex].setIMG("BonusItem/cGreen", rR); ++IMGIndex; // cGREEN : 5
	FBonusItemIMG[IMGIndex].setIMG("BonusItem/cPurple", rR); ++IMGIndex; // cPURPLE : 6
	FBonusItemIMG[IMGIndex].setIMG("BonusItem/cRed", rR); ++IMGIndex; // cRED : 7

	fbonusitem[0] = BonusItem(&FBonusItemIMG[0], GemType::GEM_BLUE, 500 - 32 * 2, 27);
	fbonusitem[1] = BonusItem(&FBonusItemIMG[1], GemType::GEM_GREEN, 500 - 32 * 1, 26);
	fbonusitem[2] = BonusItem(&FBonusItemIMG[2], GemType::GEM_PURPLE, 500 - 32 * 0, 26);
	fbonusitem[3] = BonusItem(&FBonusItemIMG[3], GemType::GEM_RED, 500 + 32 * 1, 26);

	fbonusitem[4] = BonusItem(&FBonusItemIMG[4], GemType::GEM_BLUE, 500 - 32 * 2, 27);
	fbonusitem[5] = BonusItem(&FBonusItemIMG[5], GemType::GEM_GREEN, 500 - 32 * 1, 26);
	fbonusitem[6] = BonusItem(&FBonusItemIMG[6], GemType::GEM_PURPLE, 500 - 32 * 0, 26);
	fbonusitem[7] = BonusItem(&FBonusItemIMG[7], GemType::GEM_RED, 500 + 32 * 1, 26);

	// Bonus Item, Spawn
	IMGIndex = 0;
	BonusItemIMG[IMGIndex].setIMG("BonusItem/cBlue", rR); ++IMGIndex; // BLUE : 0
	BonusItemIMG[IMGIndex].setIMG("BonusItem/cGreen", rR); ++IMGIndex; // GREEN : 1
	BonusItemIMG[IMGIndex].setIMG("BonusItem/cPurple", rR); ++IMGIndex; // PURPLE : 2
	BonusItemIMG[IMGIndex].setIMG("BonusItem/cRed", rR); ++IMGIndex; // RED : 3

	bonusitem[0] = BonusItem(&BonusItemIMG[0], GemType::GEM_BLUE);
	bonusitem[1] = BonusItem(&BonusItemIMG[1], GemType::GEM_GREEN);
	bonusitem[2] = BonusItem(&BonusItemIMG[2], GemType::GEM_PURPLE);
	bonusitem[3] = BonusItem(&BonusItemIMG[3], GemType::GEM_RED);
	// Bonus Item Setting is over

	IMGIndex = 0;
	TitleIMG.setIMG("title", rR);

	IMGIndex = 0; 
	MainMenuBackgroundIMG.setIMG("mainMenu", rR);

	IMGIndex = 0;
	MainMenuBoxIMG[IMGIndex].setIMG("start_icon", rR); ++IMGIndex;      // Index 0
	MainMenuBoxIMG[IMGIndex].setIMG("start_icon_over", rR); ++IMGIndex;
	MainMenuBoxIMG[IMGIndex].setIMG("option", rR); ++IMGIndex;
	MainMenuBoxIMG[IMGIndex].setIMG("option_over", rR); ++IMGIndex;
	MainMenuBoxIMG[IMGIndex].setIMG("ranking", rR); ++IMGIndex;
	MainMenuBoxIMG[IMGIndex].setIMG("ranking_over", rR); ++IMGIndex;
	MainMenuBoxIMG[IMGIndex].setIMG("quit_icon", rR); ++IMGIndex;
	MainMenuBoxIMG[IMGIndex].setIMG("quit_icon_over", rR);				// Index 7

	IMGIndex = 0;
	PauseMenuIMG[IMGIndex].setIMG("quit_icon", rR); ++IMGIndex;         // Index 0
	PauseMenuIMG[IMGIndex].setIMG("quit_icon_over", rR); ++IMGIndex;
	PauseMenuIMG[IMGIndex].setIMG("option", rR); ++IMGIndex;
	PauseMenuIMG[IMGIndex].setIMG("option_over", rR); ++IMGIndex;
	PauseMenuIMG[IMGIndex].setIMG("back_to_main", rR); ++IMGIndex;
	PauseMenuIMG[IMGIndex].setIMG("back_to_main_over", rR); ++IMGIndex;
	PauseMenuIMG[IMGIndex].setIMG("continue_icon", rR); ++IMGIndex;
	PauseMenuIMG[IMGIndex].setIMG("continue_icon_over", rR);			// Index 7

	
	IMGIndex = 0;
	UpgradeIMG[IMGIndex].setIMG("UI/bgUI", rR);						// Index 0 - clear UI start
	UpgradeIMG[IMGIndex].setWH(370, 197); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/again", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/again_over", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/next", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/next_over", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/upgrade", rR);
	UpgradeIMG[IMGIndex].setWH(54, 58); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/upgrade_over", rR);
	UpgradeIMG[IMGIndex].setWH(54, 58); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/main", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/main_over", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/text1", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/text2", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/text3", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/text4", rR); ++IMGIndex;       // Index 12 - clear UI end

	UpgradeIMG[IMGIndex].setIMG("UI/bgUI", rR);					 // Index 13 - upgrade UI start
	UpgradeIMG[IMGIndex].setWH(370, 230); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/character", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/character_over", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/vac", rR);
	UpgradeIMG[IMGIndex].setWH(54, 58); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/vac_over", rR);
	UpgradeIMG[IMGIndex].setWH(54, 58); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/HP", rR);
	UpgradeIMG[IMGIndex].setWH(54, 58); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/DF", rR);
	UpgradeIMG[IMGIndex].setWH(54, 58); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/ATK", rR);
	UpgradeIMG[IMGIndex].setWH(54, 58); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/plus", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/plus_over", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/plus", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/plus_over", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/quit", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/quit_over", rR);++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/text5", rR); ++IMGIndex;
	UpgradeIMG[IMGIndex].setIMG("UI/text6", rR); ++IMGIndex;		// Index 28 - upgrade UI end

	UpgradeIMG[IMGIndex].setIMG("UI/hwan", rR);				// index 29 - common UI
	UpgradeIMG[IMGIndex].setWH(75, 25); 

	IMGIndex = 0;
	EndingMenuIMG[IMGIndex].setIMG("endingMenu/gamesuccess", rR); ++IMGIndex;
	EndingMenuIMG[IMGIndex].setIMG("endingMenu/gameover", rR); ++IMGIndex;
	EndingMenuIMG[IMGIndex].setIMG("endingMenu/saving", rR); ++IMGIndex;
	EndingMenuIMG[IMGIndex].setIMG("endingMenu/saving_over", rR);

	IMGIndex = 0;
	RankingMenuIMG.setIMG("rankingmenu", rR);

	IMGIndex = 0;
	MapBackgroundIMG[IMGIndex].setIMG("backsky2", rR); ++IMGIndex;
	MapBackgroundIMG[IMGIndex].setIMG("backsky", rR);

	IMGIndex = 0;
	FontIMG.setIMG("fonts/basicfont", rR, 245, 247, 242); // Colorkey RGB 245 247 242 
	BText = Bitmap_Text(&FontIMG);
}

AssetManager::~AssetManager()
{

}

void AssetManager::AssetReset()
{
	player = Player(CharacterIMG, CharacterWeaponIMG, 24 * 70, 100);

	// Map Monster Setting Start
	int IMGIndex = 0;
	// MAP 2
	Demo_Map2_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 1 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 49 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 3 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 3 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 48 * 70, 2 * 70, IMGIndex); ++IMGIndex;

	IMGIndex = 0;
	Demo_Map2_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 49 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 1 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 1 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 45 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map2_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 47 * 70, 2 * 70, IMGIndex); ++IMGIndex;

	// MAP 3
	IMGIndex = 0;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 49 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 3 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 49 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 5 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 49 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 5 * 65, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, 49 * 65, 2 * 70, IMGIndex); ++IMGIndex;

	IMGIndex = 0;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 1 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 3 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 47 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 3 * 60, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 5 * 60, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 49 * 70, 2 * 70, IMGIndex); ++IMGIndex;
	Demo_Map3_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, 1 * 70, 2 * 70, IMGIndex); ++IMGIndex;

	// MAP 4
	IMGIndex = 0;
	int m_number = 9; // Total Monster Number is 18 -> 18/2 = 9
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map4_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, ((IMGIndex)+1) * 60, 2 * 70, IMGIndex);
	IMGIndex = 0;
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map4_Munzi[IMGIndex + m_number] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, (55 - (IMGIndex)) * 60, 2 * 70, IMGIndex + m_number);

	// MAP 5
	m_number = 6; // Total Monster Number is 12 -> 12/2 = 6

				  // MUNZI : LEFTSIDE
	IMGIndex = 0;
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map5_Munzi[IMGIndex] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, ((IMGIndex)+1) * 50, 2 * 70, IMGIndex);
	//  MUNZI : RIGHTSIDE
	IMGIndex = 0;
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map5_Munzi[IMGIndex + m_number] = M_Munzi(Monster_MunziIMG, &Monster_BloodIMG, (55 - (IMGIndex)) * 60, 2 * 70, IMGIndex + m_number);

	m_number = 6; // Total Monster Number is 12 -> 12/2 = 6

				  // ORC : LEFTSIDE
	IMGIndex = 0;
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map5_Orc[IMGIndex] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, ((IMGIndex)+1) * 50, 2 * 70, IMGIndex);
	// ORC : RIGHTSIDE
	IMGIndex = 0;
	for (IMGIndex; IMGIndex < m_number; IMGIndex++)
		Demo_Map5_Orc[IMGIndex + m_number] = M_Orc(Monster_OrcIMG, &Monster_BloodIMG, (55 - (IMGIndex)) * 60, 2 * 70, IMGIndex + m_number);

	// Map Monster Setting End ++IMGIndex;


	Medicine = RMedicine(&MedicineIMG, 500, 200);

	fbonusitem[0] = BonusItem(&FBonusItemIMG[0], GemType::GEM_BLUE, 500 - 32 * 2, 27);
	fbonusitem[1] = BonusItem(&FBonusItemIMG[1], GemType::GEM_GREEN, 500 - 32 * 1, 26);
	fbonusitem[2] = BonusItem(&FBonusItemIMG[2], GemType::GEM_PURPLE, 500 - 32 * 0, 26);
	fbonusitem[3] = BonusItem(&FBonusItemIMG[3], GemType::GEM_RED, 500 + 32 * 1, 26);
	fbonusitem[4] = BonusItem(&FBonusItemIMG[4], GemType::GEM_BLUE, 500 - 32 * 2, 27);
	fbonusitem[5] = BonusItem(&FBonusItemIMG[5], GemType::GEM_GREEN, 500 - 32 * 1, 26);
	fbonusitem[6] = BonusItem(&FBonusItemIMG[6], GemType::GEM_PURPLE, 500 - 32 * 0, 26);
	fbonusitem[7] = BonusItem(&FBonusItemIMG[7], GemType::GEM_RED, 500 + 32 * 1, 26);

	bonusitem[0] = BonusItem(&BonusItemIMG[0], GemType::GEM_BLUE);
	bonusitem[1] = BonusItem(&BonusItemIMG[1], GemType::GEM_GREEN);
	bonusitem[2] = BonusItem(&BonusItemIMG[2], GemType::GEM_PURPLE);
	bonusitem[3] = BonusItem(&BonusItemIMG[3], GemType::GEM_RED);

	for (int i = 0; i < number_gameitem; ++i)
		gameitem[i] = GameItem(&GameItemIMG, ItemType::ITEM_RADIOACTIVE_MATERIAL);
}

void AssetManager::BonusItemReset()
{
	fbonusitem[0] = BonusItem(&FBonusItemIMG[0], GemType::GEM_BLUE, 500 - 32 * 2, 27);
	fbonusitem[1] = BonusItem(&FBonusItemIMG[1], GemType::GEM_GREEN, 500 - 32 * 1, 26);
	fbonusitem[2] = BonusItem(&FBonusItemIMG[2], GemType::GEM_PURPLE, 500 - 32 * 0, 26);
	fbonusitem[3] = BonusItem(&FBonusItemIMG[3], GemType::GEM_RED, 500 + 32 * 1, 26);
	fbonusitem[4] = BonusItem(&FBonusItemIMG[4], GemType::GEM_BLUE, 500 - 32 * 2, 27);
	fbonusitem[5] = BonusItem(&FBonusItemIMG[5], GemType::GEM_GREEN, 500 - 32 * 1, 26);
	fbonusitem[6] = BonusItem(&FBonusItemIMG[6], GemType::GEM_PURPLE, 500 - 32 * 0, 26);
	fbonusitem[7] = BonusItem(&FBonusItemIMG[7], GemType::GEM_RED, 500 + 32 * 1, 26);

	bonusitem[0] = BonusItem(&BonusItemIMG[0], GemType::GEM_BLUE);
	bonusitem[1] = BonusItem(&BonusItemIMG[1], GemType::GEM_GREEN);
	bonusitem[2] = BonusItem(&BonusItemIMG[2], GemType::GEM_PURPLE);
	bonusitem[3] = BonusItem(&BonusItemIMG[3], GemType::GEM_RED);
}

void AssetManager::readRankTable()
{
	// Initialization 
	RankTable.rankTable_size = 0;
	RankTable.vRank_Number.clear();
	RankTable.vRank_Name.clear();
	RankTable.vRank_Score.clear();
	RankTable.vRank_Thought.clear();

	int l_error = MapObject_Parser.OpenFile("TestRankTable.cwrt");
	if (l_error < 0) printf("Cannot open cwrt file\n");

	int RankTable_Number = 0;

	bool l_success = false;
	l_success = MapObject_Parser.get_Numb_RankTable_Fromcwrt(&RankTable_Number);
	if (!l_success) printf("Cannot retrieve rank number data\n");

	RankTable.rankTable_size = RankTable_Number;
	RankTable.vRank_Number.reserve(RankTable_Number);
	RankTable.vRank_Name.reserve(RankTable_Number);
	RankTable.vRank_Score.reserve(RankTable_Number);
	RankTable.vRank_Thought.reserve(RankTable_Number);

	int rNumber;
	std::string rName;
	int rScore;
	std::string rThought;

	for (int i = 0; i < RankTable_Number; ++i)
	{
		l_success = MapObject_Parser.get_Rank_Number_Fromcwrt(&rNumber);
		if (!l_success) printf("Cannot retrieve rank number data\n");

		l_success = MapObject_Parser.get_Rank_Name_Fromcwrt(&rName);
		if (!l_success) printf("Cannot retrieve rank Name data\n");

		l_success = MapObject_Parser.get_Rank_Score_Fromcwrt(&rScore);
		if (!l_success) printf("Cannot retrieve rank Score data\n");

		l_success = MapObject_Parser.get_Rank_Thought_Fromcwrt(&rThought);
		if (!l_success) printf("Cannot retrieve rank Thought data\n");

		RankTable.vRank_Number.push_back(std::to_string(rNumber));
		RankTable.vRank_Name.push_back(rName);
		RankTable.vRank_Score.push_back(std::to_string(rScore));
		RankTable.vRank_Thought.push_back(rThought);
	}

	MapObject_Parser.~FileParser();
}

RankInfo* AssetManager::getRankInfo() { return &RankTable; }
RankInfo* AssetManager::getLatestRankInfo()
{
	readRankTable();
	return &RankTable;
}

CIMG* AssetManager::getTitleIMG() { return &TitleIMG; }
CIMG* AssetManager::getMainmenuBackgroundIMG() { return &MainMenuBackgroundIMG; }
CIMG* AssetManager::getMainmenuBoxIMG() { return MainMenuBoxIMG; }
CIMG* AssetManager::getPauseMenuIMG() { return PauseMenuIMG; }
CIMG* AssetManager::getUpgradeIMG() { return UpgradeIMG; }
CIMG* AssetManager::getEndingMenuIMG() { return EndingMenuIMG; }
CIMG* AssetManager::getRankingMenuIMG() { return &RankingMenuIMG; }
CIMG* AssetManager::getMapBackgroundIMG() { return MapBackgroundIMG; }
