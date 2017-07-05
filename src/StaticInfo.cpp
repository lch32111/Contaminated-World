#include "StaticInfo.h"

int SInfo::GAME_WIDTH = 1000;
int SInfo::GAME_HEIGHT = 600;

MenuManager* SInfo::oMM = new MenuManager();	//--

int SInfo::KeyIDRight = 0;
int SInfo::KeyIDLeft = 0;
int SInfo::KeyIDAlt = 0;

bool SInfo::KeyAlt = false;

int SInfo::MenuXpos = SInfo::GAME_WIDTH - 210;	//--
int SInfo::MenuYpos = SInfo::GAME_HEIGHT - 70;

MenuManager* SInfo::getMM() { return oMM; }		//--

