#include "Title.h"
#include "StaticInfo.h"
#include "Core.h"
#include "Music.h"

Title::Title()
{
	cTitle = SCore::getAssetManager()->getTitleIMG();
}

Title::~Title()
{

}

void Title::Update()
{
	SInfo::getMusic()->changeMusic();
	SInfo::getMusic()->PlayMusic();
}

void Title::Draw(SDL_Renderer* rR)
{
	cTitle->Draw(rR, 0, 0, false);
}

void Title::enter()
{
	SInfo::getMM()->currentGameState = SInfo::getMM()->eMainMenu;
}
