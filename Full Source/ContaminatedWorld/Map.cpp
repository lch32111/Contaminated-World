#include "Map.h"
#include "StaticInfo.h"
#include "AssetManager.h"
#include "Core.h"

#include <time.h>

template<typename T> inline const T abs(T const& x) { return (x < 0) ? -x : x; }

Map::Map()
{
	
}

Map::Map(const char* anything)
{
	cBackground = SCore::getAssetManager()->getMapBackgroundIMG();

	this->currentLevelID = 0;
	this->Camera = { 0, 0, SInfo::SCREEN_WIDTH, SInfo::SCREEN_HEIGHT };
	this->Tile_Width = this->Tile_Height = 70;
	this->iMapTime = 0;
	this->iMapTime2 = 0;
	this->player_number_material = 0;
	this->player_kill_monster = 0;
	this->player_hitted_number = 0;
	this->number_monster = 0;
	this->iFrametime = SDL_GetTicks();
	this->iFrametime2 = SDL_GetTicks();
	this->bStageStart = false;
	this->bStageEnd = false;
	this->bStageFail = false;
	this->bGameSuccess = false;
	for (int i = 0; i < 30; i++)
		this->SpawnMonstertime[i] = { true };
	// Bonus Item
	this->canGetSpawnTime = true;
	this->SpawnTime[4] = { 0, };
	this->BonusOrder[4] = { 0, };
	this->bBonusOrder0 = this->bBonusOrder1 = this->bBonusOrder2 = this->bBonusOrder3 = true;
	srand((unsigned int)time(NULL));
	
	LoadTestData();
	LoadLVL();
}

Map::~Map()
{

}

 
void Map::LoadTestData()
{
	for (int i = 0; i < AssetManager::MapObject_number; ++i)
		Map_Object.push_back(&AssetManager::MapObject_info[i]);

	Character = &AssetManager::player;
	number_item = AssetManager::number_gameitem;
	testItem = AssetManager::gameitem;
	Text = &AssetManager::BText;
	medicine = &AssetManager::Medicine;

	for (int i = 0; i < 8; i++)
		this->fbonusItem[i] = &AssetManager::fbonusitem[i];
	for (int i = 0; i < 4; i++)
		this->bonusItem[i] = &AssetManager::bonusitem[i];
}

void Map::LoadLVL()
{
	switch (currentLevelID)
	{
	case 0:
		Demo_Map2();
		break;
	case 1:
		Demo_Map3();
		break;
	case 2:
		Demo_Map4();
		break;
	case 3:
		Demo_Map5();
		break;
	default:
		break;
	}
}

void Map::Demo_Map()
{
}

void Map::Demo_Map2()
{
	cBackground = SCore::getAssetManager()->getMapBackgroundIMG();

	// Map Setting
	vM_Munzi.clear();
	vM_Orc.clear();
	SInfo::LEVEL_WIDTH = 3500;
	SInfo::LEVEL_HEIGHT = 700;
	Object_Place.push_back(&AssetManager::Demo_MapLevel2);

	vM_Munzi.push_back(&AssetManager::Demo_Map2_Munzi[0]);
	vM_Orc.push_back(&AssetManager::Demo_Map2_Orc[0]);

	for (int i = 0; i < 30; i++)
		this->SpawnMonstertime[i] = { true };

	// Variable Setting
	number_monster = 10;
	player_kill_monster = 0;
	player_hitted_number = 0;
	iMapTime = 0;
	iMapTime2 = 60;
	medicine->setPosition(24 * 70, 2 * 70 - 5);
	bStageStart = true;
	bStageEnd = false;
	bStageFail = false;
	UpdateCamera(); // Stage 시작 전 Camera 조정

	// 캐릭터 공격력 업그레이드(몬스터 데미지 증가)
	SInfo::getMM()->getUpgradeUI()->upgradeATK(0, 0);
	SInfo::getMM()->getUpgradeUI()->upgradeATK(1, 0);
}

void Map::Demo_Map3()
{
	cBackground = SCore::getAssetManager()->getMapBackgroundIMG();

	// Map Setting
	vM_Munzi.clear();
	vM_Orc.clear();

	SInfo::LEVEL_WIDTH = 3500;
	SInfo::LEVEL_HEIGHT = 700;
	Object_Place.push_back(&AssetManager::Demo_MapLevel2);

	vM_Orc.push_back(&AssetManager::Demo_Map3_Orc[0]);
	vM_Orc.push_back(&AssetManager::Demo_Map3_Orc[1]);
	vM_Munzi.push_back(&AssetManager::Demo_Map3_Munzi[0]);
	vM_Munzi.push_back(&AssetManager::Demo_Map3_Munzi[1]);

	for (int i = 0; i < 30; i++)
		this->SpawnMonstertime[i] = { true };

	// Variable Setting
	number_monster = 14;
	player_kill_monster = 0;
	player_hitted_number = 0;
	iMapTime = 0;
	iMapTime2 = 60;
	medicine->setPosition(24 * 70, 2 * 70 - 5);
	bStageStart = true;
	bStageEnd = false;
	bStageFail = false;
	UpdateCamera(); // Stage 시작 전 Camera 조정

	// 캐릭터 공격력 업그레이드(몬스터 데미지 증가)
	SInfo::getMM()->getUpgradeUI()->upgradeATK(0, 0);
	SInfo::getMM()->getUpgradeUI()->upgradeATK(0, 1);
	SInfo::getMM()->getUpgradeUI()->upgradeATK(1, 0);
	SInfo::getMM()->getUpgradeUI()->upgradeATK(1, 1);
}

void Map::Demo_Map4()
{
	cBackground = &SCore::getAssetManager()->getMapBackgroundIMG()[1];

	// Map Setting
	vM_Munzi.clear();
	vM_Orc.clear();
	SInfo::LEVEL_WIDTH = 3500;
	SInfo::LEVEL_HEIGHT = 700;
	Object_Place.push_back(&AssetManager::Demo_MapLevel2);

	vM_Munzi.push_back(&AssetManager::Demo_Map4_Munzi[0]);
	vM_Munzi.push_back(&AssetManager::Demo_Map4_Munzi[1]);
	vM_Munzi.push_back(&AssetManager::Demo_Map4_Munzi[2]);
	vM_Munzi.push_back(&AssetManager::Demo_Map4_Munzi[3]);

	for (int i = 0; i < 30; i++)
		this->SpawnMonstertime[i] = { true };

	// Variable Setting
	number_monster = 18;
	player_kill_monster = 0;
	player_hitted_number = 0;
	iMapTime = 0;
	iMapTime2 = 60;
	medicine->setPosition(24 * 70, 2 * 70 - 5);
	bStageStart = true;
	bStageEnd = false;
	bStageFail = false;
	UpdateCamera(); // Stage 시작 전 Camera 조정

	// 캐릭터 공격력 업그레이드(몬스터 데미지 증가)
	for (int i = 0; i<4; i++)
		SInfo::getMM()->getUpgradeUI()->upgradeATK(0, i);
}

void Map::Demo_Map5()
{
	cBackground = &SCore::getAssetManager()->getMapBackgroundIMG()[1];

	// Map Setting
	vM_Munzi.clear();
	vM_Orc.clear();
	SInfo::LEVEL_WIDTH = 3500;
	SInfo::LEVEL_HEIGHT = 700;
	Object_Place.push_back(&AssetManager::Demo_MapLevel2);

	vM_Munzi.push_back(&AssetManager::Demo_Map5_Munzi[0]);
	vM_Munzi.push_back(&AssetManager::Demo_Map5_Munzi[1]);
	vM_Orc.push_back(&AssetManager::Demo_Map5_Orc[0]);
	vM_Orc.push_back(&AssetManager::Demo_Map5_Orc[1]);

	for (int i = 0; i < 30; i++)
		this->SpawnMonstertime[i] = { true };

	// Variable Setting
	number_monster = 24;
	player_kill_monster = 0;
	player_hitted_number = 0;
	iMapTime = 0;
	iMapTime2 = 60;
	medicine->setPosition(24 * 70, 2 * 70 - 5);
	bStageStart = true;
	bStageEnd = false;
	bStageFail = false;
	UpdateCamera(); // Stage 시작 전 Camera 조정

	// 캐릭터 공격력 업그레이드(몬스터 데미지 증가)
	SInfo::getMM()->getUpgradeUI()->upgradeATK(0, 0);
	SInfo::getMM()->getUpgradeUI()->upgradeATK(0, 1);
	SInfo::getMM()->getUpgradeUI()->upgradeATK(1, 0);
	SInfo::getMM()->getUpgradeUI()->upgradeATK(1, 1);
}

void Map::SpawnMonster()
{
	if (bStageStart == false && bStageEnd == false)
	{
		switch (currentLevelID)
		{
		case 0: // MAP 2
			for (int i = 0; i < 4; i++)
			{
				if (iMapTime2 == 60 - 6 * (1 + i) && SpawnMonstertime[i])
				{
					vM_Munzi.push_back(&AssetManager::Demo_Map2_Munzi[i + 1]);
					SInfo::getMM()->getUpgradeUI()->upgradeATK(0, vM_Munzi.size()-1);

					vM_Orc.push_back(&AssetManager::Demo_Map2_Orc[i + 1]);
					SInfo::getMM()->getUpgradeUI()->upgradeATK(1, vM_Orc.size()-1);
					SpawnMonstertime[i] = false;
				}
			}
			break;
		case 1: // MAP 3
			for (int i = 0; i < 5; i++)
			{
				if (iMapTime2 == 60 - 5 * (1 + i) && SpawnMonstertime[i])
				{
					vM_Munzi.push_back(&AssetManager::Demo_Map3_Munzi[i + 2]);
					SInfo::getMM()->getUpgradeUI()->upgradeATK(0, vM_Munzi.size() - 1);

					vM_Orc.push_back(&AssetManager::Demo_Map3_Orc[i + 2]);
					SInfo::getMM()->getUpgradeUI()->upgradeATK(1, vM_Orc.size() - 1);
					SpawnMonstertime[i] = false;
				}
			}
			break;
		case 2: // MAP 4
			for (int i = 0; i < 7; i++)
			{
				if (iMapTime2 == 60 - 4 * (1 + i) && SpawnMonstertime[2 * (i + 2)])
				{
					vM_Munzi.push_back(&AssetManager::Demo_Map4_Munzi[2 * (i + 2)]);
					SInfo::getMM()->getUpgradeUI()->upgradeATK(0, vM_Munzi.size() - 1);
					SpawnMonstertime[2 * (i + 2)] = false;
				}
				else if (iMapTime2 == 60 - 5 * (1 + i) && SpawnMonstertime[(2 * (i + 2)) + 1])
				{
					vM_Munzi.push_back(&AssetManager::Demo_Map4_Munzi[(2 * (i + 2)) + 1]);
					SInfo::getMM()->getUpgradeUI()->upgradeATK(0, vM_Munzi.size() - 1);
					SpawnMonstertime[(2 * (i + 2)) + 1] = false;
				}
			}
			break;
		case 3: // MAP 5, iMapTime2 = 60
			for (int i = 0; i < 5; i++)
			{
				if (iMapTime2 == 62 - 7 * (1 + i) && SpawnMonstertime[2 * (i + 1) + 1])
				{
					vM_Munzi.push_back(&AssetManager::Demo_Map5_Munzi[2 * (i + 1) + 1]);
					SInfo::getMM()->getUpgradeUI()->upgradeATK(0, vM_Munzi.size() - 1);
					vM_Orc.push_back(&AssetManager::Demo_Map5_Orc[2 * (i + 1) + 1]);
					SInfo::getMM()->getUpgradeUI()->upgradeATK(1, vM_Orc.size() - 1);
					SpawnMonstertime[2 * (i + 1) + 1] = false;
				}
				else if (iMapTime2 == 53 - 6 * (1 + i) && SpawnMonstertime[2 * (i + 1)])
				{
					vM_Munzi.push_back(&AssetManager::Demo_Map5_Munzi[2 * (i + 1)]);
					SInfo::getMM()->getUpgradeUI()->upgradeATK(0, vM_Munzi.size() - 1);
					vM_Orc.push_back(&AssetManager::Demo_Map5_Orc[2 * (i + 1)]);
					SInfo::getMM()->getUpgradeUI()->upgradeATK(1, vM_Orc.size() - 1);
					SpawnMonstertime[2 * (i + 1)] = false;
				}
			}
			break;
		}
	}
}

void Map::Draw(SDL_Renderer* rR)
{
	DrawMap(rR);
	medicine->Draw(rR, &Camera);
	DrawCharacter(rR);
	DrawMonster(rR);
	DrawItem(rR);
	DrawGameLayout(rR);
	DrawBonusItem(rR);
}

void Map::DrawMap(SDL_Renderer* rR)
{
	cBackground->Draw(rR, 0, 0, false);

	int left_tile = (Camera.x - Tile_Width) / Tile_Width;
	int right_tile = (Camera.x + Tile_Width + Camera.w) / Tile_Width;
	int top_tile = (Camera.y - Tile_Height) / Tile_Height;
	int bottom_tile = (Camera.y + Tile_Height + Camera.h) / Tile_Height;

	if (left_tile < 0) left_tile = 0;
	if (right_tile >= Object_Place[currentLevelID]->getMapCol()) right_tile = Object_Place[currentLevelID]->getMapCol() - 1;
	if (top_tile < 0) top_tile = 0;
	if (bottom_tile >= Object_Place[currentLevelID]->getMapRow()) bottom_tile = Object_Place[currentLevelID]->getMapRow() - 1;


	for (unsigned int i = top_tile; i <= bottom_tile; ++i)
		for (unsigned int j = left_tile; j <= right_tile; ++j)
			Map_Object[Object_Place[currentLevelID]->getMapdata(i, j)]->Draw(rR, j * Tile_Width - Camera.x, i * Tile_Height - Camera.y);
}

void Map::DrawCharacter(SDL_Renderer* rR)
{
	Character->Draw(rR, &Camera);
}

void Map::DrawMonster(SDL_Renderer* rR)
{
	for (unsigned int i = 0; i < vM_Munzi.size(); ++i)
		vM_Munzi[i]->Draw(rR, &Camera);

	for (unsigned int i = 0; i < vM_Orc.size(); ++i)
		vM_Orc[i]->Draw(rR, &Camera);
}

void Map::DrawItem(SDL_Renderer* rR)
{
	for(int i = 0; i < number_item; ++i)
		if(testItem[i].getisDrawn())
			testItem[i].Draw(rR, &Camera);
}

void Map::DrawGameLayout(SDL_Renderer* rR)
{
	// 게임중
	if(bStageStart == false && bStageEnd == false)
	{
		Text->Draw(rR, "Stage " + std::to_string(getCurrentLevel() + 1), 10, 10);
		Text->DrawXCenter(rR, std::to_string(iMapTime2), 10);	// 남은 시간
		Text->DrawXCenter(rR, "Medicine HP : " + std::to_string(medicine->getHP()) , SInfo::SCREEN_HEIGHT - Text->getTextHeight("Medicine HP : "));
		Text->Draw(rR, "Score : " + std::to_string(Character->getScore()), SInfo::SCREEN_WIDTH - Text->getTextWidth("Score : " + std::to_string(Character->getScore())) - 10, 10);
		
		//BonusItem
		DrawBonusItemUI(rR);
	}
	// Stage 시작 상태
	else if(bStageStart == true)
	{
		Text->DrawXCenter(rR, "Start In " + std::to_string(5 - iMapTime) + " Second" , Text->getTextHeight("a"));
		Text->DrawXCenter(rR, "Stage " + std::to_string(getCurrentLevel() + 1) + " Start!", Text->getTextHeight("a\n"));
	}
	// Stage 끝 상태
	else if (bStageEnd == true)
	{
		Text->DrawXCenter(rR, "Stage " + std::to_string(getCurrentLevel() + 1) + " End!", 3*(Text->getTextHeight("t")));
		Text->DrawXCenter(rR, std::to_string(iMapTime2), 10);
		if (bStageFail == true)
			Text->DrawXCenter(rR, "Failed to defense the medicine!", Text->getTextHeight("t\n"));
		Text->DrawXCenter(rR, "Medicine HP : " + std::to_string(medicine->getHP()), SInfo::SCREEN_HEIGHT - Text->getTextHeight("Medicine HP : "));
		Text->Draw(rR, "Score : " + std::to_string(Character->getScore()), SInfo::SCREEN_WIDTH - Text->getTextWidth("Score : " + std::to_string(Character->getScore())) - 10, 10);
		
		//BonusItem
		DrawBonusItemUI(rR);

		DrawMedicineFullHPText(rR);
		DrawCharacterFullHPText(rR);
	}
}

// 화면 상단에 띄워지는 보너스아이템 UI
void Map::DrawBonusItemUI(SDL_Renderer* rR)
{
	for (int i = 0; i < 4; i++)
		fbonusItem[i]->Drawf(rR);
	for (int i = 0; i<4; i++)
		if (bonusItem[i]->get_canDrawAcquired())
			fbonusItem[i + 4]->Drawf(rR);
}

void Map::DrawBonusItem(SDL_Renderer* rR)
{
	// 전체 Draw
	for (int i = 0; i < 4; i++)
		if (bonusItem[i]->getisDrawn())
		{
			bonusItem[i]->Draw(rR, &Camera);
			if (SDL_GetTicks() - bonusItem[i]->iTimeLasting > 4000)
				bonusItem[i]->set_isDrawn(false);
		}
}

void Map::SpawnItem()
{
	// 게임중에만 아이템이 생성되고 떨어지도록 설정
	if (bStageStart == false && bStageEnd == false)
	{
		// 4개의 랜덤 시간대 배열 생성
		if (canGetSpawnTime) 
		{
			for (int i = 1; i <= 4; i++) 
			{
				SpawnTime[i - 1] = ((rand() % ((iMapTime2 / 6) - 2))) + ((iMapTime2 / 6) * (4 - i + 1));
			}
			// 1~4 랜덤 숫자 배열 생성
			bool bCheckExistOfNum[4] = { false, };
			for (int j = 0; j < 4; ) 
			{
				int temp = rand() % 4;
				if (bCheckExistOfNum[temp] == false)
				{
					bCheckExistOfNum[temp] = true;
					BonusOrder[j] = temp;
					++j;
				}
			}
			this->canGetSpawnTime = false;
		}

		int x = Character->getXPos();
		int w = Character->getWidth();

		// 색깔 별 Spawn ( 랜덤 시간대에 맞춰서 )
		if (iMapTime2 == SpawnTime[0]) {
			if (bBonusOrder0) {
				bonusItem[BonusOrder[0]]->SpawnPos(x, w);
				bBonusOrder0 = false;
			}
		}
		else if (iMapTime2 == SpawnTime[1]) {
			if (bBonusOrder1) {
				bonusItem[BonusOrder[1]]->SpawnPos(x, w);
				bBonusOrder1 = false;
			}
		}
		else if (iMapTime2 == SpawnTime[2]) {
			if (bBonusOrder2) {
				bonusItem[BonusOrder[2]]->SpawnPos(x, w);
				bBonusOrder2 = false;
			}
		}
		else if (iMapTime2 == SpawnTime[3]) {
			if (bBonusOrder3) {
				bonusItem[BonusOrder[3]]->SpawnPos(x, w);
				bBonusOrder3 = false;
			}
		}
	}
}

void Map::DrawMedicineFullHPText(SDL_Renderer* rR)
{
	if(SInfo::getMM()->getUpgradeUI()->getbCanDrawMedicineFullHPText())
		Text->DrawXCenter(rR, "Medicine HP is already FULL", 6 * (Text->getTextHeight("t")));
}

void Map::DrawCharacterFullHPText(SDL_Renderer* rR)
{
	if (SInfo::getMM()->getUpgradeUI()->getbCanDrawCharacterFullHPText())
		Text->DrawXCenter(rR, "Character HP is already FULL", 6 * (Text->getTextHeight("t")));
}

void Map::Update()
{
	// 게임 중
	if(bStageStart == false && bStageEnd == false)
	{
		if (player_kill_monster == number_monster)
		{
			if (bStageEnd == false)
			{
				bStageEnd = true;
				SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cstageend);
				UpdateMedicine();
			}
		}
		else if (medicine->getisAvailable() == false || iMapTime2 <= 0)
		{
			if (bStageEnd == false)
			{
				bStageEnd = true;
				bStageFail = true;
				SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cstageend);
				vM_Munzi.clear();
				vM_Orc.clear();
				UpdateMonster();
				UpdateMedicine();
			}
		}

		SpawnMonster();
		UpdatePlayer();			// Memory High!! -> 연산을 가능하면 계속 줄이기
		UpdateMonster();		// Memory High!! -> 연산을 가능하면 계속 줄이기
		UpdateMedicine();
		UpdateItem();
		UpdateCamera();
		UpdateBonusItem();

		if (SDL_GetTicks() - iFrametime >= 1000)
		{
			--iMapTime2;
			iFrametime = SDL_GetTicks();
		}

		
	}
	// Stage 시작 상태
	else if(bStageStart == true)
	{
		// stage start music을 한 번만 실행하고 시간을 설정을위해 bstageEnd 변수를 이용함.
		if (bStageEnd == false)
		{
			iFrametime = SDL_GetTicks();
			SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cstagestart);
			bStageEnd = true;
		}
		
		// 5초 뒤 시작인걸 보여주기 위해 시간 초 증가
		if (SDL_GetTicks() - iFrametime >= 1000)
		{
			++iMapTime;
			iFrametime = SDL_GetTicks();
		}

		// 5초 뒤 stagestart/end flag를 false로
		if (iMapTime == 5)
		{
			SInfo::getMusic()->changeMusic();
			SInfo::getMusic()->PlayMusic();
			iMapTime = 0;
			bStageStart = false;
			bStageEnd = false;
		}
	}
	// Stage 끝 상태
	else if (bStageEnd == true)
	{
		UpdatePlayer();
		UpdateItem();
		UpdateCamera();
		UpdateBonusItem();
		SInfo::getMusic()->setMusicStopped(false);
		SInfo::getMusic()->StopMusic();

		// 1초씩 증가
		if (SDL_GetTicks() - iFrametime >= 1000)
		{
			++iMapTime;
			iFrametime = SDL_GetTicks();
		}

		//3초 후 upgrade 상태로 변경
		if( iMapTime == 3)
		{
			// 눌러져 있는 키를 모두 풀어주기 위한 코드
			SInfo::getMM()->getUpgradeUI()->set_bResetKeypressed(true);
			iMapTime = 0;

			if (bStageFail)
			{
				SInfo::getMM()->setStateID(SInfo::getMM()->eEnding);
				SInfo::getMM()->getEndingMenu()->setGameSuccess(false, 0);
				SInfo::getMusic()->PlayMusic(SInfo::getMusic()->mDead);
			}
			else
			{
				// Game Success(All Stage Clear) -> Rank Table
				if (currentLevelID == 3)
				{
					SInfo::getMM()->setStateID(SInfo::getMM()->eEnding);
					SInfo::getMM()->getEndingMenu()->setGameSuccess(true, SInfo::getMM()->getUpgradeUI()->getTotalCoin());
					SInfo::getMusic()->PlayMusic(SInfo::getMusic()->mDead); //## Clear 노래로 바꿔주면 좋을듯
				}
				else // StageEnd -> UpgradUI -> Stage Change
				{
					SInfo::getMM()->setStateID(SInfo::getMM()->eUpgradeUI);
					// 업그레이드 상태가 되면(클리어창이 뜨면) gem UI를 클리어창으로 이동시킨다
					for (int i = 0; i < 8; i++)
						fbonusItem[i]->setfXYpos(0, SInfo::SCREEN_HEIGHT / 2 - 60);
				}
			}
		}
	}
}

void Map::UpdatePlayer()
{
	Character->Update();
	player_hitted_number = Character->getHittedNumber();
}

void Map::UpdateMonster()
{
	for (std::vector<M_Munzi*>::iterator it = vM_Munzi.begin(); it != vM_Munzi.end();)
	{
		(*it)->Update();
		if ((*it)->getbDie())
		{
			// GameItem Spawn Start
			int random_spawn = rand() % 10;
			if (random_spawn / 10.f > 0.3f)
			{
				int random_itemnumb = rand() % 3;
				if (random_itemnumb == 0) random_itemnumb = 1;

				for (int i = 0; i < random_itemnumb; ++i)
				{
					testItem[number_spawnitem].Spawn((*it)->getXPos(), (*it)->getYPos(), (*it)->getWidth(), (*it)->getHeight());
					if (number_spawnitem < number_item - 1)
						++number_spawnitem;
					else
						break;
				}
			}
			// GameItem Spawn End

			++player_kill_monster;

			it = vM_Munzi.erase(it);
		}
		else
			++it;
	}

	for (std::vector<M_Orc*>::iterator it = vM_Orc.begin(); it != vM_Orc.end();)
	{
		(*it)->Update();
		if ((*it)->getbDie())
		{
			// GameItem Spawn Start
			int random_spawn = rand() % 10;
			if (random_spawn / 10.f > 0.3f)
			{
				int random_itemnumb = rand() % 3;
				if (random_itemnumb == 0) random_itemnumb = 1;

				for (int i = 0; i < random_itemnumb; ++i)
				{
					testItem[number_spawnitem].Spawn((*it)->getXPos(), (*it)->getYPos(), (*it)->getWidth(), (*it)->getHeight());
					if (number_spawnitem < number_item - 1)
						++number_spawnitem;
					else
						break;
				}
			}
			// GameItem Spawn End

			++player_kill_monster;

			it = vM_Orc.erase(it);
		}
		else
			++it;
	}
}

void Map::UpdateMedicine()
{
	medicine->Update();
}

void Map::UpdateItem()
{
	for(int i = 0; i < number_item; ++i)
		if (testItem[i].getisSpawn())
			testItem[i].Update();

	for(int i = 0; i <= number_spawnitem; ++i)
		if (testItem[i].getisDrawn())
		{
			if (CollisionCharacter(&testItem[i].getRect()))
			{
				testItem[i].Acquire();
				++player_number_material;
				Character->addScore(100);
			}
		}
}

void Map::UpdateCamera()
{
	Camera.x = Character->getXPos() + (Character->getWidth() - SInfo::SCREEN_WIDTH) / 2;
	Camera.y = Character->getYPos() + (Character->getHeight() - SInfo::SCREEN_HEIGHT) / 2;
	if (Camera.x < 0)
		Camera.x = 0;
	if (Camera.y < 0)
		Camera.y = 0;
	if (Camera.x > SInfo::LEVEL_WIDTH - Camera.w)
		Camera.x = SInfo::LEVEL_WIDTH - Camera.w;
	if (Camera.y > SInfo::LEVEL_HEIGHT - Camera.h)
		Camera.y = SInfo::LEVEL_HEIGHT - Camera.h;
}

void Map::UpdateBonusItem()
{
	SpawnItem();

	for (int i = 0; i < 4; i++)
	{
		if (bonusItem[i]->getisSpawn())
			bonusItem[i]->Update();
	}
	for (int i = 0; i < 4; i++)
		if (bonusItem[i]->getisDrawn())
		{
			if (CollisionCharacter(&bonusItem[i]->getColliderRect(bonusItem[i]->getGemType(i))))
			{
				bonusItem[i]->Acquire();
				Character->addScore(1000);
			}
		}
}

void Map::UpdateScore()
{
	Character->calcSCore(iMapTime2);
}

void Map::reset()
{
	player_number_material = 0;
	player_kill_monster = 0;
	player_hitted_number = 0;
	SInfo::getMM()->getUpgradeUI()->resetiUpdradeAttack();
	vM_Munzi.clear();
	vM_Orc.clear();
	Object_Place.clear();
	
	AssetManager::AssetReset();
	Character = &AssetManager::player;
	testItem = AssetManager::gameitem;
	medicine = &AssetManager::Medicine;

	Character->resetScore();
	resetBonusItem();

	LoadLVL();
}

void Map::resetBonusItem()
{
	canGetSpawnTime = true;
	for (int i = 0; i < 4; i++)
	{
		SpawnTime[i] = 0;
		BonusOrder[i] = 0;
	}
	bBonusOrder0 = bBonusOrder1 = bBonusOrder2 = bBonusOrder3 = true;

	for (int i = 0; i < 8; i++)
		this->fbonusItem[i] = &AssetManager::fbonusitem[i];
	for (int i = 0; i < 4; i++)
		this->bonusItem[i] = &AssetManager::bonusitem[i];
}


bool Map::CollisionCharacter(const SDL_Rect* Target)
{
	int Collision_index = 0;
	int minAx = Character->getXPos();
	int maxAx = minAx +Character->getWidth();
	int minAy = Character->getYPos();
	int maxAy = minAy + Character->getHeight();
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	if (maxAx < minBx || minAx > maxBx)
		++Collision_index;
	if (maxAy < minBy || minAy > maxBy)
		++Collision_index;

	if (Collision_index == 0)
	{
		return true;
	}

	return false;
}

bool Map::AttackCollisionCharacter(const SDL_Rect* Target)
{
	int Collision_index = 0;
	int minAx = Character->getXPos();
	int maxAx = minAx + Character->getWidth();
	int minAy = Character->getYPos();
	int maxAy = minAy + Character->getHeight();
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	if (maxAx < minBx || minAx > maxBx)
		++Collision_index;
	if (maxAy < minBy || minAy > maxBy)
		++Collision_index;

	if (Collision_index == 0)
	{
		Character->HPdown();
		return true;
	}

	return false;
}

bool Map::CollisionMonster(const SDL_Rect* Target)
{
	int Collision_index = 0;
	int minAx, minAy, maxAx, maxAy;
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	for (unsigned int i = 0; i < vM_Munzi.size(); ++i)
	{
		if(!vM_Munzi[i]->getbDie())
		{
			minAx = vM_Munzi[i]->getXPos();
			maxAx = minAx + vM_Munzi[i]->getWidth();
			minAy = vM_Munzi[i]->getYPos();
			maxAy = minAy + vM_Munzi[i]->getHeight();

			if (maxAx < minBx || minAx > maxBx)
				++Collision_index;
			if (maxAy < minBy || minAy > maxBy)
				++Collision_index;

			if (Collision_index == 0)
			{
				return true;
			}

			Collision_index = 0;
		}
	}

	for (unsigned int i = 0; i < vM_Orc.size(); ++i)
	{
		if (!vM_Orc[i]->getbDie())
		{
			minAx = vM_Orc[i]->getXPos();
			maxAx = minAx + vM_Orc[i]->getWidth();
			minAy = vM_Orc[i]->getYPos();
			maxAy = minAy + vM_Orc[i]->getHeight();

			if (maxAx < minBx || minAx > maxBx)
				++Collision_index;
			if (maxAy < minBy || minAy > maxBy)
				++Collision_index;

			if (Collision_index == 0)
				return true;

			Collision_index = 0;
		}
	}

	return false;
}

bool Map::AttackCollisionMonster(const SDL_Rect* Target)
{
	bool attack = false;
	int Collision_index = 0;
	int minAx, minAy, maxAx, maxAy;
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	for (unsigned int i = 0; i < vM_Munzi.size(); ++i)
	{
		if(!vM_Munzi[i]->getbDie())
		{
			minAx = vM_Munzi[i]->getXPos();
			maxAx = minAx + vM_Munzi[i]->getWidth();
			minAy = vM_Munzi[i]->getYPos();
			maxAy = minAy + vM_Munzi[i]->getHeight();

			if (maxAx < minBx || minAx > maxBx)
				++Collision_index;
			if (maxAy < minBy || minAy > maxBy)
				++Collision_index;

			if (Collision_index == 0)
			{
				vM_Munzi[i]->set_HittedMonsterState();	// Hitted
				attack = true;
			}

			Collision_index = 0;
		}
	}

	for (unsigned int i = 0; i < vM_Orc.size(); ++i)
	{
		if (!vM_Orc[i]->getbDie())
		{
			minAx = vM_Orc[i]->getXPos();
			maxAx = minAx + vM_Orc[i]->getWidth();
			minAy = vM_Orc[i]->getYPos();
			maxAy = minAy + vM_Orc[i]->getHeight();

			if (maxAx < minBx || minAx > maxBx)
				++Collision_index;
			if (maxAy < minBy || minAy > maxBy)
				++Collision_index;

			if (Collision_index == 0)
			{
				vM_Orc[i]->set_HittedMonsterState();	// Hitted
				attack = true;
			}

			Collision_index = 0;
		}
	}

	return attack;
}

bool Map::CollisionBodyMonster(const SDL_Rect* Target)
{
	int Collision_index = 0;
	int minAx, minAy, maxAx, maxAy;
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	for (unsigned int i = 0; i < vM_Munzi.size(); ++i)
	{
		if (!vM_Munzi[i]->getbDie())
		{
			minAx = vM_Munzi[i]->getXPos();
			maxAx = minAx + vM_Munzi[i]->getWidth();
			minAy = vM_Munzi[i]->getYPos();
			maxAy = minAy + vM_Munzi[i]->getHeight();

			if (maxAx < minBx || minAx > maxBx)
				++Collision_index;
			if (maxAy < minBy || minAy > maxBy)
				++Collision_index;

			if (Collision_index == 0)
			{
				return true;
			}

			Collision_index = 0;
		}
	}

	return false;
}

bool Map::AttackCollisionMedicine(const SDL_Rect* Target)
{
	int Collision_index = 0;
	int minAx = medicine->getRect().x;
	int maxAx = minAx + medicine->getRect().w;
	int minAy = medicine->getRect().y;
	int maxAy = minAy + medicine->getRect().h;
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	if (maxAx < minBx || minAx > maxBx)
		++Collision_index;
	if (maxAy < minBy || minAy > maxBy)
		++Collision_index;

	if (Collision_index == 0)
	{
		medicine->setHitted();
		return true;
	}

	return false;
}

int Map::getBottomCollidedPlatformType(const SDL_Rect* Target)
{
	int left_tile = Target->x / Tile_Width;
	int right_tile = Target->x + Target->w / Tile_Width;
	int bottom_tile = (Target->y + Target->h) / Tile_Height;
	if (left_tile < 0) left_tile = 0;
	if (right_tile >= Object_Place[currentLevelID]->getMapCol()) right_tile = Object_Place[currentLevelID]->getMapCol() - 1;
	if (bottom_tile >= Object_Place[currentLevelID]->getMapRow()) bottom_tile = Object_Place[currentLevelID]->getMapRow() - 1;
	
	int Collision_index = 0;
	int minAx, minAy, maxAx, maxAy;
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	for (unsigned int i = left_tile; i <= right_tile; ++i)
	{
		int objectType = Map_Object[Object_Place[currentLevelID]->getMapdata(bottom_tile, i)]->getObjectType();
		if (objectType != 0) // If tile is solid or slope
		{
			minAx = i * Tile_Width;
			maxAx = minAx + Tile_Width;
			minAy = bottom_tile * Tile_Height;
			maxAy = minAy + Tile_Height;

			if (maxAx < minBx || minAx > maxBx)
				++Collision_index;
			if (maxAy < minBy || minAy > maxBy)
				++Collision_index;

			if (Collision_index == 0)
				return objectType;
		}
	}

	return 0; // background or not collided with object.
}

// for the collision detection with X Position.
bool Map::XCollisionMapObject(int* object_col, const SDL_Rect* Target)
{
	int left_tile = Target->x / Tile_Width;
	int right_tile = (Target->x + Target->w) / Tile_Width;
	int top_tile = Target->y / Tile_Height;
	int bottom_tile = (Target->y + Target->h) / Tile_Height;

	if (left_tile < 0) left_tile = 0;
	if (right_tile >= Object_Place[currentLevelID]->getMapCol()) right_tile = Object_Place[currentLevelID]->getMapCol() - 1;
	if (top_tile < 0) top_tile = 0;
	if (bottom_tile >= Object_Place[currentLevelID]->getMapRow()) bottom_tile = Object_Place[currentLevelID]->getMapRow() - 1;

	int Collision_index = 0;
	int minAx, minAy, maxAx, maxAy;
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	for (unsigned int i = top_tile; i <= bottom_tile; ++i)
	{
		for (unsigned int j = left_tile; j <= right_tile; j += right_tile - left_tile)
		{
			int objectType = Map_Object[Object_Place[currentLevelID]->getMapdata(i, j)]->getObjectType();
			if (objectType == 1) // Solid
			{
				minAx = j * Tile_Width;
				maxAx = minAx + Tile_Width;
				minAy = i * Tile_Height;
				maxAy = minAy + Tile_Height;

				if (maxAx < minBx || minAx > maxBx)
					++Collision_index;
				if (maxAy < minBy || minAy > maxBy)
					++Collision_index;

				if (Collision_index == 0)
				{
					*object_col = j;
					return true;
				}
			}
			else if (objectType == 2) // slope tile
			{
				// the reason why this code is here is that
				// When the character is next to the slope tile in the air
				// The collision point is not in the slope tile. So The character just pass through the tile.
				// In order to prevent that problem, This code is here.
				int row, col;
				int SlopeState = isSlopeTile(&row, &col, Target);
				if (SlopeState >= 0)
					return false;
				else
				{
					*object_col = j;
					return true;
				}
			}

			// 타겟의 크기가 작아 left_tile과 right_tile이 같은 경우 계속 공회전하므로
			if (left_tile == right_tile)
				j = right_tile + 1;
		}
	}

	return false;
}

// for the collision detection with Y Position
bool Map::YCollisionMapObject(int* object_row, const int* speed, const SDL_Rect* Target)
{
	int left_tile = Target->x / Tile_Width;
	int right_tile = (Target->x + Target->w) / Tile_Width;

	if (left_tile < 0) left_tile = 0;
	if (right_tile >= Object_Place[currentLevelID]->getMapCol()) right_tile = Object_Place[currentLevelID]->getMapCol() - 1;

	int top_tile, bottom_tile;

	int Collision_index = 0;
	int minAx, minAy, maxAx, maxAy;
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	// speed > 0 means falling
	if (*speed > 0)
	{
		bottom_tile = (Target->y + Target->h) / Tile_Height;
		if (bottom_tile >= Object_Place[currentLevelID]->getMapRow()) bottom_tile = Object_Place[currentLevelID]->getMapRow() - 1;

		for (unsigned int i = left_tile; i <= right_tile; ++i)
		{
			int objectType = Map_Object[Object_Place[currentLevelID]->getMapdata(bottom_tile, i)]->getObjectType();
			if (objectType == 1) // Solid
			{
				minAx = i * Tile_Width;
				maxAx = minAx + Tile_Width;
				minAy = bottom_tile * Tile_Height;
				maxAy = minAy + Tile_Height;

				if (maxAx < minBx || minAx > maxBx)
					++Collision_index;
				if (maxAy < minBy || minAy > maxBy)
					++Collision_index;

				if (Collision_index == 0)
				{
					*object_row = bottom_tile;
					return true;
				}
			}
			else if (objectType == 2) // Slope
			{
				int row, col;
				int slopeState = isSlopeTile(&row, &col, Target);
				
				if(slopeState <= -1) // 타겟의 하단 양쪽이 Slope에 있지 않거나, 정상적인 Slope 타는게 아닐 때
				{
					minAx = i * Tile_Width;
					maxAx = minAx + Tile_Width;
					minAy = bottom_tile * Tile_Height;
					maxAy = minAy + Tile_Height;

					if (maxAx < minBx || minAx > maxBx)
						++Collision_index;
					if (maxAy < minBy || minAy > maxBy)
						++Collision_index;
					
					if (Collision_index == 0)
					{
						*object_row = bottom_tile;
						return true;
					}
				}
				else if(slopeState >= 0) // 타겟의 하단 양쪽 둘 중 하나가 Slope에 있을 때
				{
					if (i > left_tile && i < right_tile)
					{
						minAx = i * Tile_Width;
						maxAx = minAx + Tile_Width;
						minAy = bottom_tile * Tile_Height;
						maxAy = minAy + Tile_Height;

						if (maxAx < minBx || minAx > maxBx)
							++Collision_index;
						if (maxAy < minBy || minAy > maxBy)
							++Collision_index;

						if (Collision_index == 0)
						{
							*object_row = bottom_tile;
							return true;
						}
					}
				}
			}
		}
	}
	else
	{
		top_tile = (Target->y / Tile_Height);
		if (top_tile < 0) top_tile = 0;
		for (unsigned int i = left_tile; i <= right_tile; ++i)
		{
			// The reason to check Map Object type, not bCollision, is that
			// When the character is under the slope tile, the charater just go up through the tile.
			// In order to prevent the problem, This code checks the Object Type.
			if (Map_Object[Object_Place[currentLevelID]->getMapdata(top_tile, i)]->getObjectType() != 0) // Solid or Slope Tile
			{
				minAx = i * Tile_Width;
				maxAx = minAx + Tile_Width;
				minAy = top_tile * Tile_Height;
				maxAy = minAy + Tile_Height;

				if (maxAx < minBx || minAx > maxBx)
					++Collision_index;
				if (maxAy < minBy || minAy > maxBy)
					++Collision_index;

				if (Collision_index == 0)
				{
					*object_row = top_tile;
					return true;
				}
			}
		}
	}

	return false;
}

// Caution!!! : Use this function when the Target go up
bool Map::YTopCollisionMapObject(int* object_row, const SDL_Rect* Target)
{
	int left_tile = Target->x / Tile_Width;
	int right_tile = (Target->x + Target->w) / Tile_Width;
	int top_tile = (Target->y / Tile_Height);

	if (left_tile < 0) left_tile = 0;
	if (right_tile >= Object_Place[currentLevelID]->getMapCol()) right_tile = Object_Place[currentLevelID]->getMapCol() - 1;
	if (top_tile < 0) top_tile = 0;

	int Collision_index = 0;
	int minAx, minAy, maxAx, maxAy;
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	for (unsigned int i = left_tile; i <= right_tile; ++i)
	{
		// The reason to check Map Object type, not bCollision, is that
		// When the character is under the slope tile, the charater just go up through the tile.
		// In order to prevent the problem, This code checks the Object Type.
		if (Map_Object[Object_Place[currentLevelID]->getMapdata(top_tile, i)]->getObjectType() != 0) // Solid or Slope Tile
		{
			minAx = i * Tile_Width;
			maxAx = minAx + Tile_Width;
			minAy = top_tile * Tile_Height;
			maxAy = minAy + Tile_Height;

			if (maxAx < minBx || minAx > maxBx)
				++Collision_index;
			if (maxAy < minBy || minAy > maxBy)
				++Collision_index;

			if (Collision_index == 0)
			{
				*object_row = top_tile;
				return true;
			}
		}
	}

	return false;
}

// Caution!!! : Use this function when the Target go down
bool Map::YBottomCollisionMapObject(int* object_row, const SDL_Rect* Target)
{
	int left_tile = Target->x / Tile_Width;
	int right_tile = (Target->x + Target->w) / Tile_Width;
	int bottom_tile = (Target->y + Target->h) / Tile_Height;

	if (left_tile < 0) left_tile = 0;
	if (right_tile >= Object_Place[currentLevelID]->getMapCol()) right_tile = Object_Place[currentLevelID]->getMapCol() - 1;
	if (bottom_tile >= Object_Place[currentLevelID]->getMapRow()) bottom_tile = Object_Place[currentLevelID]->getMapRow() - 1;
	
	int Collision_index = 0;
	int minAx, minAy, maxAx, maxAy;
	int minBx = Target->x;
	int maxBx = minBx + Target->w;
	int minBy = Target->y;
	int maxBy = minBy + Target->h;

	for (unsigned int i = left_tile; i <= right_tile; ++i)
	{
		if (Map_Object[Object_Place[currentLevelID]->getMapdata(bottom_tile, i)]->getCollision())
		{
			minAx = i * Tile_Width;
			maxAx = minAx + Tile_Width;
			minAy = bottom_tile * Tile_Height;
			maxAy = minAy + Tile_Height;

			if (maxAx < minBx || minAx > maxBx)
				++Collision_index;
			if (maxAy < minBy || minAy > maxBy)
				++Collision_index;

			if (Collision_index == 0)
			{
				*object_row = bottom_tile;
				return true;
			}
		}
	}

	return false;
}

int Map::getXPenetrationDistance(const int* object_col, const SDL_Rect* Target)
{
	// left = false, right = true
	bool Collide_left_right = false;

	// Object left, Target Right
	if ((*object_col * Tile_Width <= Target->x) && ((*object_col + 1) * Tile_Width >= Target->x))
		Collide_left_right = false;
	// Obejct Right, Target Left
	else if ((*object_col * Tile_Width <= Target->x + Target->w) && ((*object_col + 1) * Tile_Width >= Target->x + Target->w))
		Collide_left_right = true;
	// Object와 Target이 딱 겹치는 부분 이 때는 0을 return하여 X좌표를 수정하지 않도록
	else
		return 0;

	// 오른쪽과 충돌이므로, 양수를 반환하여 XPos가 줄어들도록
	if (Collide_left_right)
		return ((Target->x + Target->w - *object_col * Tile_Width) + 1);
	// 왼쪽과 충돌하므로, 음수를 반환하여 XPos가 늘어나도록
	else
		return -1 * (((*object_col + 1) * Tile_Width - Target->x) + 1);
}

int Map::getYPenetrationDistance(const int* object_row, const SDL_Rect* Target)
{
	// Top check = false, Bottom check = true
	bool Collide_Top_Bottom = false;

	// Object bottom, Target Up
	if (*object_row * Tile_Height <= Target->y + Target->h && (*object_row + 1) * Tile_Height >= Target->y + Target->h)
		Collide_Top_Bottom = true; // Bottom check
	// Object Up, Target bottom
	else if ((*object_row + 1) * Tile_Height >= Target->y && *object_row * Tile_Height <= Target->y)
		Collide_Top_Bottom = false; // Top check
	else
		return 0;

	// Bottom Penetration
	if (Collide_Top_Bottom)
		return ((Target->y + Target->h - *object_row * Tile_Height) + 1);
	// Top Penetration
	else
		return -1 * (((*object_row + 1) * Tile_Height - Target->y) + 1);
}

int Map::isSlopeTile(int* object_row, int* object_col, const SDL_Rect* Target)
{
	int row = (Target->y + Target->h) / Tile_Height;
	int left_col = Target->x / Tile_Width;
	int right_col = (Target->x + Target->w) / Tile_Width;

	if (row >= Object_Place[currentLevelID]->getMapRow()) row = Object_Place[currentLevelID]->getMapRow() - 1;
	if (left_col < 0) left_col = 0;
	if (right_col >= Object_Place[currentLevelID]->getMapCol()) right_col = Object_Place[currentLevelID]->getMapCol() - 1;

	std::pair<int, int> leftcol_slope_info = Map_Object[Object_Place[currentLevelID]->getMapdata(row, left_col)]->getSlopeInfo();
	std::pair<int, int> rightcol_slope_info = Map_Object[Object_Place[currentLevelID]->getMapdata(row, right_col)]->getSlopeInfo();
	int SlopeState = -1;
	// Slope State -2 : 하단 양쪽 둘 중 하나가, Slope에 있긴하지만, Slope를 정상적으로 오르거나 내려가는 상태가 아님
	// Slope State -1 : 하단 양쪽 둘 다 Slope에 있지않음
	// Slope State 0 : North east Slope, right_col로 좌표구하기
	// Slope State 1 : North west Slope, left_col로 좌표구하기
	// Slope State 2 : Target의 left_col, right_col 두 개가 slope 안에 있기 때문에, NE slope인지 NW slope인지 가려내야함
	                 // Target의 너비가 충분히 작아 left_col과 right_col이 동시에 한 slope에 있을 때

	if (Map_Object[Object_Place[currentLevelID]->getMapdata(row, right_col)]->getObjectType() == 2)
	{
		if (rightcol_slope_info.first > rightcol_slope_info.second)
			SlopeState = 0;
		else
			SlopeState = -2;
	}
		

	if (Map_Object[Object_Place[currentLevelID]->getMapdata(row, left_col)]->getObjectType() == 2)
	{
		if (leftcol_slope_info.first < leftcol_slope_info.second)
			SlopeState = 1;
		else
			SlopeState = -2;
	}

	if (Map_Object[Object_Place[currentLevelID]->getMapdata(row, right_col)]->getObjectType() == 2
		&& Map_Object[Object_Place[currentLevelID]->getMapdata(row, left_col)]->getObjectType() == 2)
	{
		if (leftcol_slope_info.first < leftcol_slope_info.second && rightcol_slope_info.first > rightcol_slope_info.second)
			SlopeState = 2;
		else
			SlopeState = -2;

		// Target의 크기가 작아 left_col과 right_col이 동시에 들어있을때
		if (left_col == right_col)
			SlopeState = 2;
	}

	if (SlopeState == 0)
	{
		*object_row = row;
		*object_col = right_col;
		
	}
	else if (SlopeState == 1)
	{
		*object_row = row;
		*object_col = left_col;
	}
	else if (SlopeState == 2)
	{
		// 캐릭터의 양쪽이 서로다른 slope column에 걸쳐있을 때
		if (left_col != right_col)
		{
			float left = getSlopePosition(&row, &left_col, Target);
			float right = getSlopePosition(&row, &right_col, Target);
			// 둘 중 캐릭터를 더 높은 위치에 있게하는 곳에 있게 한다. (y값이 더 작은)
			if (left > right) // y축 기준
			{
				*object_row = row;
				*object_col = right_col;
			}
			else
			{
				*object_row = row;
				*object_col = left_col;
			}
		}
		// 캐릭터의 양쪽이 한 column안에 있을 때
		else
		{
			// slope 정보는 비어있는 pixel의 개수이므로,
			// second가 크다는 것은 first가 꽉차 있다는 것이므로
			// NW Slope이다.
			if (rightcol_slope_info.first < rightcol_slope_info.second)
			{
				*object_row = row;
				*object_col = left_col;
			}
			else
			{
				*object_row = row;
				*object_col = right_col;
			}
		}
	}

	return SlopeState;
}

float Map::getSlopePosition(const int* object_row, const int* object_col, const SDL_Rect* Target)
{
	std::pair<int, int> temp = Map_Object[Object_Place[currentLevelID]->getMapdata(*object_row, *object_col)]->getSlopeInfo();
	float floory, result;

	// North east Slope
	if (temp.first > temp.second)
	{
		float axis = (float)(temp.first - temp.second) / Tile_Width;
		int b = (Tile_Height - temp.first);
		int x = Target->x + Target->w - *object_col * Tile_Width;
		floory = x * axis + b;

		// With this, the character can go to next tile.
		if (abs(floory) / (float)Tile_Height > 0.97)
			floory += temp.first - abs(floory);

		// (the bottom position of the slope tile - Character Height - floory from slope(원래 쓰는 좌표계와 컴퓨터좌표계가 다르므로 -1)
		// the reason to subtract 1 from the result Yposition is that the character can move to the next tile with the position.
		result = (*object_row + 1) * Tile_Height - 1 - Target->h - floory;
		return result;
	}
	// North west Slope
	else if(temp.first < temp.second)
	{
		float axis = (float)(temp.first - temp.second) / Tile_Width;
		int b = (Tile_Height - temp.first);
		int x = Target->x - *object_col * Tile_Width;
		floory = x * axis + b;

		if (abs(floory) / (float)Tile_Height > 0.97)
			floory += temp.second - abs(floory);

		result = (*object_row + 1) * Tile_Height - 1 - Target->h - floory;
		return result;
	}

	return -1.f;
}

Player* Map::getPlayer() { return Character; }
RMedicine* Map::getMedicine() { return medicine; }
std::vector<M_Munzi*> Map::getVecMunzi() { return vM_Munzi; }
std::vector<M_Orc*> Map::getVecOrc() { return vM_Orc; }
Bitmap_Text* Map::getText() { return Text; }
void Map::set_iMapTime2(int time) { iMapTime2 = time; }
bool Map::getbStageEnd() { return bStageEnd; }
void Map::setCurrentLevel(int lev) { this->currentLevelID = lev; }
int Map::getCurrentLevel() { return this->currentLevelID; }