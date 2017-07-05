#pragma once

#ifndef STATICINFO_H
#define STATICINFO_H

#include "MenuManager.h"

class SInfo
{
private:

	static MenuManager* oMM;	//--

public:

	static int GAME_WIDTH, GAME_HEIGHT;
	static int KeyIDRight, KeyIDLeft, KeyIDAlt;
	static bool KeyAlt;

	static int MenuXpos, MenuYpos;

	static MenuManager* getMM();	//--

};


#endif
