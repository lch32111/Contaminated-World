#pragma once

#ifndef STATICINFO_H
#define STATICINFO_H

#include "MenuManager.h"
#include "Music.h"

class SInfo
{
private:
	static MenuManager* oMM;	
	static Music* oMusic;
public:
	SInfo();
	SInfo(const char* anything);
	~SInfo();

	static int SCREEN_WIDTH, SCREEN_HEIGHT;
	static int LEVEL_WIDTH, LEVEL_HEIGHT;
	static int KeyIDA; // LEFT MOVE
	static int KeyIDD; // RIGHT MOVE
	static int KeyIDSpace; // JUMP
	static int KeyIDShift; // RUN
	static int KeyIDB; // Change Weapon
	
	static bool KeySpace, KeyShift;

	static int ContinueMenuXpos, GotoMainMenuXpos, QuitMenuXpos;
	static int MenuYpos;

	static MenuManager* getMM();
	static Music* getMusic();

};

#endif
