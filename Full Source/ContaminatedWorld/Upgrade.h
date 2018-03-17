#pragma once

#ifndef UPGRADE_H
#define UPGRADE_H

#include "header.h"
#include "CIMG.h"
class Upgrade
{
private:
	
	// clear UI
	CIMG* cBg_clear;
	CIMG* cAgain;
	CIMG* cAgain_over;
	CIMG* cNext;
	CIMG* cNext_over;
	CIMG* cUpgrade;
	CIMG* cUpgrade_over;
	CIMG* cMain;
	CIMG* cMain_over;
	CIMG *cText_Again;
	CIMG *cText_Next;
	CIMG *cText_Upgrade;
	CIMG *cText_Main;
	
	// upgrade UI 
	CIMG* cBg_upgrade;
	CIMG* cCharacterUI;
	CIMG* cCharacterUI_over;
	CIMG* cVaccineUI;
	CIMG* cVaccineUI_over;
	CIMG* cHP;
	CIMG* cDF;
	CIMG* cATK;
	CIMG* cUpperPlus;
	CIMG* cUpperPlus_over;
	CIMG* cLowerPlus;
	CIMG* cLowerPlus_over;
	CIMG* cQuit;
	CIMG* cQuit_over;
	CIMG *cText_Character;
	CIMG *cText_Vaccine;

	CIMG* cCoin;

	int total_AcquiredCoin;
	int coin;

	int activeMenuOption;
	bool bUpgrade;	// upgrade 상태인지 아닌지 체크
	bool bCheckCharacter;
	bool bCalcCoin;
	bool bResetKeypressed;	// keypressed 리셋여부를 확인하는 변수
	int iUpgradeAttack;	// 스테이지 클리어시 캐릭터 공격력 업그레이드 한 횟수
	float ratio;

	void subCoin(int num);

	// 업그레이드 풀 업그레이드 시 경고문구
	bool bMedicineFullHPText;
	bool bCanDrawMedicineFullHPText;
	unsigned int iMedicineFullHPTextTime;

	bool bCharacterFullHPText;
	bool bCanDrawCharacterFullHPText;
	unsigned int iCharacterFullHPTextTime;

	void UpdatMedicineFullHPText();
	void UpdatCharacterFullHPText();
	
public:

	Upgrade();
	~Upgrade();

	void Update();
	void Draw(SDL_Renderer *rR);

	void DrawClearUI(SDL_Renderer* rR);
	void DrawClearUI_over1(SDL_Renderer* rR);
	void DrawClearUI_over2(SDL_Renderer* rR);
	void DrawClearUI_over3(SDL_Renderer* rR);
	void DrawClearUI_over4(SDL_Renderer* rR);

	void DrawUpgradeUI(SDL_Renderer *rR);
	void DrawUpgradeUI_over1(SDL_Renderer *rR);
	void DrawUpgradeUI_over2(SDL_Renderer *rR);
	void DrawUpgradeUI_over3(SDL_Renderer *rR);

	void escape();
	void checkMouseInput(int x, int y);
	void click(int x, int y);
	
	bool is_in_button(int x, int y, SDL_Rect button);

	void vaccineHP_up();
	void vaccineDF_up(); 
	void characterHP_up();
	void characterATK_up();

	void upgradeATK(int monsterid, int idx);

	void calcCoin();		// score 코인으로 바꾸기
	
	void resetiUpdradeAttack();

	void setbCalcCoin(bool flag);
	void set_bResetKeypressed(bool flag);
	bool get_bResetKeypressed();
	int get_iUpgradeAttack();
	int getTotalCoin();
	
	bool getbCanDrawMedicineFullHPText();
	bool getbCanDrawCharacterFullHPText();
};

#endif // !UPGRADE_H
