#include "StaticInfo.h"

Music* SInfo::oMusic;
MenuManager* SInfo::oMM;

int SInfo::SCREEN_WIDTH = 1000;
int SInfo::SCREEN_HEIGHT = 600;
int SInfo::LEVEL_WIDTH = 7000;
int SInfo::LEVEL_HEIGHT = 7000;

SInfo::SInfo() { }

SInfo::SInfo(const char* anything)
{
	oMusic = new Music();
	oMM = new MenuManager();
}

SInfo::~SInfo()
{
}

int SInfo::KeyIDA = 0;
int SInfo::KeyIDD = 0;
int SInfo::KeyIDSpace = 0;
int SInfo::KeyIDShift = 0;
int SInfo::KeyIDB = 0;

bool SInfo::KeyShift = false;
bool SInfo::KeySpace = false;

int SInfo::ContinueMenuXpos = 60;
int SInfo::GotoMainMenuXpos = SInfo::SCREEN_WIDTH / 2 - 100;
int SInfo::QuitMenuXpos = SInfo::SCREEN_WIDTH - 260;
int SInfo::MenuYpos = SInfo::SCREEN_HEIGHT - 80;

MenuManager* SInfo::getMM() { return oMM; }		
Music* SInfo::getMusic() { return oMusic; }

