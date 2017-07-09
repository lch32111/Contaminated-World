#pragma once

#ifndef MAP_H
#define MAP_H

#include "CIMG.h"
#include "Player.h"
#include <vector>

class Map
{
	// Map���� �׸� ĳ����, ����, ��� ��
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


	// �� Map���� ��Ÿ�� ���� �����ϴ� �޼ҵ��
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