#pragma once

#ifndef MAP_H
#define MAP_H

#include "CIMG.h"
#include "Player.h"
#include <vector>

class Map
{
	// Map에서 그릴 캐릭터, 몬스터, 배경 등
private:

	CIMG Background;
	Player* Character;
	int CharacterX, CharacterY;

	CIMG Monster;
	//
	CIMG ContinueIcon;
	CIMG ContinueIcon_over;
	CIMG QuitIcon;
	CIMG QuitIcon_over;	

	void LoadTestData(SDL_Renderer* rR);


	// 그 Map에서 나타날 것을 제어하는 메소드들
public:

	Map();		//--
	Map(SDL_Renderer* rR);

	void Draw(SDL_Renderer* rR);
	void DrawBackground(SDL_Renderer* rR);
	void DrawCharacter(SDL_Renderer* rR);
	void DrawMonster(SDL_Renderer* rR);
	
	void DrawMenu(SDL_Renderer* rR);	//--
	void DrawMenu_over(SDL_Renderer* rR);	//--



	void Update();
	void UpdatePlayer();

	void addMonster();


	/* ----- get & set ----- */
	Player* getPlayer();
};

#endif