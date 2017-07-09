#include "StaticInfo.h"

int SInfo::GAME_WIDTH = 1000;
int SInfo::GAME_HEIGHT = 600;

MenuManager* SInfo::oMM = new MenuManager();	//--

int SInfo::KeyIDRight = 0;
int SInfo::KeyIDLeft = 0;
int SInfo::KeyIDAlt = 0;

bool SInfo::KeyAlt = false;

int SInfo::QuitMenuXpos = SInfo::GAME_WIDTH - 220;	//--
int SInfo::QuitMenuYpos = SInfo::GAME_HEIGHT - 70;
int SInfo::ContinueMenuXpos = 20;	
int SInfo::ContinueMenuYpos = SInfo::GAME_HEIGHT - 70;

MenuManager* SInfo::getMM() { return oMM; }		//--

