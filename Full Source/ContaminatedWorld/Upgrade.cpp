#include "Upgrade.h"
#include "Core.h"
#include "BonusItem.h"

Upgrade::Upgrade() 
{
	// clear UI
	cBg_clear = SCore::getAssetManager()->getUpgradeIMG();
	cAgain = &cBg_clear[1];
	cAgain_over = &cBg_clear[2];
	cNext = &cBg_clear[3];
	cNext_over = &cBg_clear[4];
	cUpgrade = &cBg_clear[5];
	cUpgrade_over = &cBg_clear[6];
	cMain = &cBg_clear[7];
	cMain_over = &cBg_clear[8];
	cText_Again = &cBg_clear[9];
	cText_Next = &cBg_clear[10];
	cText_Upgrade = &cBg_clear[11];
	cText_Main = &cBg_clear[12];

	// upgrade UI 
	cBg_upgrade = &cBg_clear[13];
	cCharacterUI = &cBg_clear[14];
	cCharacterUI_over = &cBg_clear[15];
	cVaccineUI = &cBg_clear[16];
	cVaccineUI_over = &cBg_clear[17];
	cHP = &cBg_clear[18];
	cDF = &cBg_clear[19];
	cATK = &cBg_clear[20];
	cUpperPlus = &cBg_clear[21];
	cUpperPlus_over = &cBg_clear[22];
	cLowerPlus= &cBg_clear[23];
	cLowerPlus_over = &cBg_clear[24];
	cQuit = &cBg_clear[25];
	cQuit_over = &cBg_clear[26];
	cText_Character = &cBg_clear[27];
	cText_Vaccine = &cBg_clear[28];

	cCoin = &cBg_clear[29];
	
	total_AcquiredCoin = 0;
	coin = 0;

	activeMenuOption = -1;
	bUpgrade = false;
	bCheckCharacter = true;	
	bCalcCoin = false;
	bResetKeypressed = false;
	iUpgradeAttack = 0;
	ratio = 0.0;

	bMedicineFullHPText = false;
	bCanDrawMedicineFullHPText = false;
	iMedicineFullHPTextTime = 0;

	bCharacterFullHPText = false;
	bCanDrawCharacterFullHPText = false;
	iCharacterFullHPTextTime = 0;
}

Upgrade::~Upgrade()
{

}

void Upgrade::Update()
{
	SCore::getMap()->UpdateScore();
	if(SCore::getMap()->getPlayer()->getbCalcScore())	// 남은시간 점수로 환산 후 코인으로 변환
		calcCoin();
	UpdatMedicineFullHPText();
	UpdatCharacterFullHPText();
	/* bonus item UI reset하는 코드 추가 */
}

void Upgrade::UpdatMedicineFullHPText()
{
	if (bMedicineFullHPText)
	{
		bCanDrawMedicineFullHPText = true;
		if (SDL_GetTicks() - iMedicineFullHPTextTime > 1000)
		{
			bCanDrawMedicineFullHPText = false;
			bMedicineFullHPText = false;
		}
	}
}

void Upgrade::UpdatCharacterFullHPText()
{
	if (bCharacterFullHPText)
	{
		bCanDrawCharacterFullHPText = true;
		if (SDL_GetTicks() - iCharacterFullHPTextTime > 1000)
		{
			bCanDrawCharacterFullHPText = false;
			bCharacterFullHPText = false;
		}
	}
}

void Upgrade::Draw(SDL_Renderer *rR)
{
	// upgrade UI 
	if (bUpgrade)
	{
		cBg_upgrade->Draw(rR, SInfo::SCREEN_WIDTH / 2 - cBg_upgrade->getRect().w / 2, SInfo::SCREEN_HEIGHT / 2 - cBg_upgrade->getRect().h / 2, false);
		// 캐릭터 업그레이드
		if (bCheckCharacter)
		{
			cCharacterUI_over->Draw(rR, cBg_upgrade->getRect().x + 40, SInfo::SCREEN_HEIGHT / 2 - 60, false);
			cVaccineUI->Draw(rR, cBg_upgrade->getRect().x + 40, SInfo::SCREEN_HEIGHT / 2 + 25, false);
			cHP->Draw(rR, cBg_upgrade->getRect().x + 125, SInfo::SCREEN_HEIGHT / 2 - 50, false);
			cATK->Draw(rR, cBg_upgrade->getRect().x + 125, SInfo::SCREEN_HEIGHT / 2 + 15, false);
		}
		// 백신 업그레이드
		else
		{
			cCharacterUI->Draw(rR, cBg_upgrade->getRect().x + 40, SInfo::SCREEN_HEIGHT / 2 - 60, false);
			cVaccineUI_over->Draw(rR, cBg_upgrade->getRect().x + 40, SInfo::SCREEN_HEIGHT / 2 + 25, false);
			cHP->Draw(rR, cBg_upgrade->getRect().x + 125, SInfo::SCREEN_HEIGHT / 2 - 50, false);
			cDF->Draw(rR, cBg_upgrade->getRect().x + 125, SInfo::SCREEN_HEIGHT / 2 + 15, false);
		}

		switch (activeMenuOption)
		{
		case 0:		// hp+ UI 활성화
			DrawUpgradeUI_over1(rR);
			break;
		case 1:		// atk+ UI 활성화
			DrawUpgradeUI_over2(rR);
			break;
		case 2:		// quit UI 활성화
			DrawUpgradeUI_over3(rR);
			break;
		default:
			DrawUpgradeUI(rR);
			break;
		}
		cText_Character->Draw(rR, cCharacterUI_over->getRect().x + cCharacterUI_over->getRect().w/2 - cText_Character->getRect().w/2, cCharacterUI_over->getRect().y+ cCharacterUI_over->getRect().h, false);
		cText_Vaccine->Draw(rR, cVaccineUI->getRect().x + cVaccineUI->getRect().w / 2 - cText_Vaccine->getRect().w / 2, cVaccineUI->getRect().y + cVaccineUI->getRect().h, false);

		cCoin->Draw(rR, cBg_upgrade->getRect().x + cBg_upgrade->getRect().w - (20 + cCoin->getRect().w), cBg_upgrade->getRect().y + 50, false);
		SCore::getMap()->getText()->Draw(rR, std::to_string(coin), cCoin->getRect().x + 30, cCoin->getRect().y + 3);
	}
	// clear UI 
	else
	{
		cBg_clear->Draw(rR, SInfo::SCREEN_WIDTH / 2 - cBg_clear->getRect().w / 2, SInfo::SCREEN_HEIGHT / 2 - cBg_clear->getRect().h / 2, false);
		switch (activeMenuOption)
		{
			// 다시하기 
		case 0:
			DrawClearUI_over1(rR);
			break;
			// 다음 스테이지
		case 1:
			DrawClearUI_over2(rR);
			break;
			// 업그레이드 
		case 2:
			DrawClearUI_over3(rR);
			break;
			// 메인으로 
		case 3:
			DrawClearUI_over4(rR);
			break;
		default:
			DrawClearUI(rR);
			break;
		}

		cText_Again->Draw(rR, cAgain->getRect().x + cAgain->getRect().w/2 - cText_Again->getRect().w/2, cAgain->getRect().y + cAgain->getRect().h + 5, false);
		cText_Next->Draw(rR, cNext->getRect().x + cNext->getRect().w / 2 - cText_Next->getRect().w / 2, cText_Again->getRect().y, false);
		cText_Upgrade->Draw(rR, cUpgrade->getRect().x + cUpgrade->getRect().w / 2 - cText_Upgrade->getRect().w / 2, cText_Again->getRect().y, false);
		cText_Main->Draw(rR, cMain->getRect().x + cMain->getRect().w / 2 - cText_Main->getRect().w / 2, cText_Again->getRect().y, false);
	
		cCoin->Draw(rR, cBg_clear->getRect().x + cBg_clear->getRect().w - (20 + cCoin->getRect().w), cBg_clear->getRect().y + 40, false);
		SCore::getMap()->DrawBonusItemUI(rR);
		SCore::getMap()->getText()->Draw(rR, std::to_string(coin), cCoin->getRect().x + 30, cCoin->getRect().y + 3);
	}
}

/* ---- clear UI ---- */
// defalt
void Upgrade::DrawClearUI(SDL_Renderer* rR)
{
	cAgain->Draw(rR, cBg_clear->getRect().x + 30, cBg_clear->getRect().y + cBg_clear->getRect().h - 100, false);
	cNext->Draw(rR, cBg_clear->getRect().x + 2 * 30 + cUpgrade->getRect().w, cAgain->getRect().y, false);
	cUpgrade->Draw(rR, cBg_clear->getRect().x + 3 * 30 + 2 * cUpgrade->getRect().w, cAgain->getRect().y, false);
	cMain->Draw(rR, cBg_clear->getRect().x + 4 * 30 + 3 * cUpgrade->getRect().w, cAgain->getRect().y, false);
}

void Upgrade::DrawClearUI_over1(SDL_Renderer* rR)
{
	cAgain_over->Draw(rR, cBg_clear->getRect().x + 30, cBg_clear->getRect().y + cBg_clear->getRect().h - 100, false);
	cNext->Draw(rR, cBg_clear->getRect().x + 2 * 30 + cUpgrade->getRect().w, cAgain->getRect().y, false);
	cUpgrade->Draw(rR, cBg_clear->getRect().x + 3 * 30 + 2 * cUpgrade->getRect().w, cAgain->getRect().y, false);
	cMain->Draw(rR, cBg_clear->getRect().x + 4 * 30 + 3 * cUpgrade->getRect().w, cAgain->getRect().y, false);
}

void Upgrade::DrawClearUI_over2(SDL_Renderer* rR)
{
	cAgain->Draw(rR, cBg_clear->getRect().x + 30, cBg_clear->getRect().y + cBg_clear->getRect().h - 100, false);
	cNext_over->Draw(rR, cBg_clear->getRect().x + 2 * 30 + cUpgrade->getRect().w, cAgain->getRect().y, false);
	cUpgrade->Draw(rR, cBg_clear->getRect().x + 3 * 30 + 2 * cUpgrade->getRect().w, cAgain->getRect().y, false);
	cMain->Draw(rR, cBg_clear->getRect().x + 4 * 30 + 3 * cUpgrade->getRect().w, cAgain->getRect().y, false);
}

void Upgrade::DrawClearUI_over3(SDL_Renderer* rR)
{
	cAgain->Draw(rR, cBg_clear->getRect().x + 30, cBg_clear->getRect().y + cBg_clear->getRect().h - 100, false);
	cNext->Draw(rR, cBg_clear->getRect().x + 2 * 30 + cUpgrade->getRect().w, cAgain->getRect().y, false);
	cUpgrade_over->Draw(rR, cBg_clear->getRect().x + 3 * 30 + 2 * cUpgrade->getRect().w, cAgain->getRect().y, false);
	cMain->Draw(rR, cBg_clear->getRect().x + 4 * 30 + 3 * cUpgrade->getRect().w, cAgain->getRect().y, false);
}

void Upgrade::DrawClearUI_over4(SDL_Renderer* rR)
{
	cAgain->Draw(rR, cBg_clear->getRect().x + 30, cBg_clear->getRect().y + cBg_clear->getRect().h - 100, false);
	cNext->Draw(rR, cBg_clear->getRect().x + 2 * 30 + cUpgrade->getRect().w, cAgain->getRect().y, false);
	cUpgrade->Draw(rR, cBg_clear->getRect().x + 3 * 30 + 2 * cUpgrade->getRect().w, cAgain->getRect().y, false);
	cMain_over->Draw(rR, cBg_clear->getRect().x + 4 * 30 + 3 * cUpgrade->getRect().w, cAgain->getRect().y, false);
}

/* ---- upgrade UI ---- */
// defalt
void Upgrade::DrawUpgradeUI(SDL_Renderer *rR)
{
	cUpperPlus->Draw(rR, SInfo::SCREEN_WIDTH / 2 + 10, SInfo::SCREEN_HEIGHT / 2 - 50, false);
	cLowerPlus->Draw(rR, SInfo::SCREEN_WIDTH / 2 + 10, SInfo::SCREEN_HEIGHT / 2 + 15, false);
	cQuit->Draw(rR, cBg_upgrade->getRect().x + cBg_upgrade->getRect().w - (20 + cQuit->getRect().w), cLowerPlus->getRect().y + cLowerPlus->getRect().h - cQuit->getRect().h, false);
}
// upper plus 활성화
void Upgrade::DrawUpgradeUI_over1(SDL_Renderer *rR)
{
	cUpperPlus_over->Draw(rR, SInfo::SCREEN_WIDTH / 2 + 10, SInfo::SCREEN_HEIGHT / 2 - 50, false);
	cLowerPlus->Draw(rR, SInfo::SCREEN_WIDTH / 2 + 10, SInfo::SCREEN_HEIGHT / 2 + 15, false);
	cQuit->Draw(rR, cBg_upgrade->getRect().x + cBg_upgrade->getRect().w - (20 + cQuit->getRect().w), cLowerPlus->getRect().y + cLowerPlus->getRect().h - cQuit->getRect().h, false);
}
// lower plus 활성화
void Upgrade::DrawUpgradeUI_over2(SDL_Renderer *rR)
{
	cUpperPlus->Draw(rR, SInfo::SCREEN_WIDTH / 2 + 10, SInfo::SCREEN_HEIGHT / 2 - 50, false);
	cLowerPlus_over->Draw(rR, SInfo::SCREEN_WIDTH / 2 + 10, SInfo::SCREEN_HEIGHT / 2 + 15, false);
	cQuit->Draw(rR, cBg_upgrade->getRect().x + cBg_upgrade->getRect().w - (20 + cQuit->getRect().w), cLowerPlus->getRect().y + cLowerPlus->getRect().h - cQuit->getRect().h, false);
}
// quit 활성화
void Upgrade::DrawUpgradeUI_over3(SDL_Renderer *rR)
{
	cUpperPlus->Draw(rR, SInfo::SCREEN_WIDTH / 2 + 10, SInfo::SCREEN_HEIGHT / 2 - 50, false);
	cLowerPlus->Draw(rR, SInfo::SCREEN_WIDTH / 2 + 10, SInfo::SCREEN_HEIGHT / 2 + 15, false);
	cQuit_over->Draw(rR, cBg_upgrade->getRect().x + cBg_upgrade->getRect().w - (20 + cQuit->getRect().w), cLowerPlus->getRect().y + cLowerPlus->getRect().h - cQuit->getRect().h, false);
}

void Upgrade::escape()
{
	if (bUpgrade)
		bUpgrade = false;
}

void Upgrade::checkMouseInput(int x, int y)
{
	// upgrad UI
	if (bUpgrade)
	{
		if (is_in_button(x, y, cUpperPlus->getRect()))
			activeMenuOption = 0;
		else if (is_in_button(x, y, cLowerPlus->getRect()))
			activeMenuOption = 1;
		else if (is_in_button(x, y, cQuit->getRect()))
			activeMenuOption = 2;
		else
			activeMenuOption = -1;
	}
	// clear UI
	else
	{
		if (is_in_button(x, y, cAgain->getRect()))
			activeMenuOption = 0;
		else if (is_in_button(x, y, cNext->getRect()))
			activeMenuOption = 1;
		else if (is_in_button(x, y, cUpgrade->getRect()))
			activeMenuOption = 2;
		else if (is_in_button(x, y, cMain->getRect()))
			activeMenuOption = 3;
		else
			activeMenuOption = -1;
	}
	
}

void Upgrade::click(int x, int y)
{
	// upgrad UI
	if (bUpgrade)
	{
		if (is_in_button(x, y, cCharacterUI->getRect()))
			bCheckCharacter = true;

		if (is_in_button(x, y, cVaccineUI->getRect()))
			bCheckCharacter = false;

		switch (activeMenuOption)
		{
		case 0: 
			if (is_in_button(x, y, cUpperPlus->getRect()))
			{
				if (bCheckCharacter)
					characterHP_up(); // 캐릭터 체력 업그레이드
				else			
					vaccineHP_up(); // 백신 체력 업그레이드
			}
			break;
		case 1: // 백신 방어력 업그레이드
			if (is_in_button(x, y, cLowerPlus->getRect()))
			{
				if (bCheckCharacter)
					characterATK_up(); // 캐릭터 공격력 업그레이드
				else
					vaccineDF_up(); // 백신 방어력 업그레이드
			}
			break;
		case 2: // quit
			if (is_in_button(x, y, cQuit->getRect()))
				escape();
			break;
		default:
			break;
		}
	}
	// clear UI
	else
	{
		switch (activeMenuOption)
		{
		case 0: // 다시하기
			if (is_in_button(x, y, cAgain->getRect()))
			{	
				bCalcCoin = false;
				activeMenuOption = -1;
				SCore::getMap()->reset();
				SInfo::getMM()->setStateID(SInfo::getMM()->eGame);
				SInfo::getMusic()->PlayMusic(SInfo::getMusic()->mGame);
			}
			break;
		case 1: // 다음 스테이지
			if (is_in_button(x, y, cNext->getRect()))
			{
				bCalcCoin = false;
				SCore::getMap()->getPlayer()->setHittedNumber(0);
				SCore::getMap()->setCurrentLevel(SCore::getMap()->getCurrentLevel() + 1);
				SCore::getMap()->getPlayer()->resetScore();
				AssetManager::BonusItemReset();
				SCore::getMap()->resetBonusItem();
				SInfo::getMM()->setStateID(SInfo::getMM()->eGame);
				SCore::getMap()->LoadLVL();
			}
			break;
		case 2: // 업그레이드
			if (is_in_button(x, y, cUpgrade->getRect()))
				bUpgrade = true;
			break;
		case 3: // 메인으로
			if (is_in_button(x, y, cMain->getRect()))
			{
				SCore::getMap()->setCurrentLevel(0);
				bCalcCoin = false;
				SCore::getMap()->reset();
				SInfo::getMM()->setStateID(SInfo::getMM()->eMainMenu);
				SInfo::getMusic()->PlayMusic(SInfo::getMusic()->mTitle);
			}
			break;
		default:
			break;
		}
	}
	
}

bool Upgrade::is_in_button(int x, int y, SDL_Rect button)
{
	return (x < button.x || x > button.x + button.w || y < button.y || y > button.y + button.h) ? false : true;
}


void Upgrade::vaccineHP_up()
{
	if (coin >= 10)
	{
		if (SCore::getMap()->getMedicine()->getHP() < SCore::getMap()->getMedicine()->getMaxHP())
		{
			SCore::getMap()->getMedicine()->addHP(50);
			subCoin(10);
		}
		else
		{
			iMedicineFullHPTextTime = SDL_GetTicks();
			bMedicineFullHPText = true;
		}
	}
}

void Upgrade::vaccineDF_up()
{
	if (coin >= 10)
	{
		SCore::getMap()->getMedicine()->upgradeDamage();
		subCoin(10);
	}
}

void Upgrade::characterHP_up()
{
	if (coin >= 10)
	{
		if (SCore::getMap()->getPlayer()->getHP() < SCore::getMap()->getPlayer()->getMaxHP())
		{
			SCore::getMap()->getPlayer()->addHP(30);
			subCoin(10);
		}
		else
		{
			iCharacterFullHPTextTime = SDL_GetTicks();
			bCharacterFullHPText = true;
		}
	}
}

// eUpgradUI는 몬스터가 0개인 상태이므로 업데이트 횟수만 설정한 후 map에서 아래 함수 호출
void Upgrade::characterATK_up()
{
	if (coin >= 10)
	{
		++iUpgradeAttack;
		subCoin(10);
	}
}

void Upgrade::upgradeATK(int monsterid, int idx)
{
	if (iUpgradeAttack > 0)
	{
		ratio = 0.0;

		for (int i = 0; i < iUpgradeAttack; i++)
			ratio += 0.1;

		if (monsterid == 0) // Munzi
			(SCore::getMap()->getVecMunzi())[idx]->setDamage_ratio(ratio);
		if (monsterid == 1) // Orc
			(SCore::getMap()->getVecOrc())[idx]->setDamage_ratio(ratio);
	}
}

// score 100당 하나의 코인이 주어짐
void Upgrade::calcCoin()
{
	if (!bCalcCoin)
	{
		coin += SCore::getMap()->getPlayer()->getScore() / 100;
		total_AcquiredCoin += coin;
		bCalcCoin = true;
	}		
}

void Upgrade::subCoin(int num)
{
	coin -= num;
}

void Upgrade::set_bResetKeypressed(bool flag) { this->bResetKeypressed = flag; }
bool Upgrade::get_bResetKeypressed() { return bResetKeypressed; }
int Upgrade::get_iUpgradeAttack() { return this->iUpgradeAttack; }
void Upgrade::setbCalcCoin(bool flag) { this->bCalcCoin = flag; }
void Upgrade::resetiUpdradeAttack() { this->iUpgradeAttack = 0; }
int Upgrade::getTotalCoin() { return total_AcquiredCoin; }
bool Upgrade::getbCanDrawMedicineFullHPText() { return bCanDrawMedicineFullHPText; }
bool Upgrade::getbCanDrawCharacterFullHPText() { return bCanDrawCharacterFullHPText; }