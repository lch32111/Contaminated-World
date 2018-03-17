#include "OptionMenu.h"
#include "StaticInfo.h"
#include "Core.h"

OptionMenu::OptionMenu()
{
	this->rOptionBox.w = SInfo::SCREEN_WIDTH / 2;
	this->rOptionBox.h = SInfo::SCREEN_HEIGHT / 2;
	this->rOptionBox.x = SInfo::SCREEN_WIDTH / 2 - rOptionBox.w / 2;
	this->rOptionBox.y = SInfo::SCREEN_HEIGHT / 5 * 2;

	rVolumeBG.w = SInfo::getMusic()->getVolume() * 4;
	rVolumeBG.h = 30;
	rVolumeBG.x = SInfo::SCREEN_WIDTH / 2 - rVolumeBG.w / 2;
	rVolumeBG.y = rOptionBox.y + rOptionBox.h / 2 - rVolumeBG.h / 2 - 30;

	rVolume.x = SInfo::SCREEN_WIDTH / 2 - rVolumeBG.w / 2;
	rVolume.y = rOptionBox.y + rOptionBox.h / 2 - rVolumeBG.h / 2 - 30;
	rVolume.h = 30;
	rVolume.w = SInfo::getMusic()->getVolume() * 4;

	rMute.x = rVolumeBG.x + rVolumeBG.w / 2 - 25;
	rMute.y = rVolumeBG.y + 120;
	rMute.w = 50;
	rMute.h = 30;

	this->numOfMenu = 2;	// 볼륨 조절, 음소거
	this->activeMenuOption = 0;
	this->mute = false;
	this->escapeToMainMenu = true;
}

OptionMenu::~OptionMenu()
{

}

void OptionMenu::Update()
{

}

void OptionMenu::Draw(SDL_Renderer* rR)
{
	SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(rR, 0xff, 0xff, 0xff, 100);
	SDL_RenderFillRect(rR, &rOptionBox);

	SDL_SetRenderDrawColor(rR, 4, 4, 4, 245);
	SDL_RenderFillRect(rR, &rVolumeBG);

	SDL_SetRenderDrawColor(rR, activeMenuOption == 0 ? 150 : 90,
		activeMenuOption == 0 ? 150 : 90,
		activeMenuOption == 0 ? 150 : 90, 255);
	if (rVolume.w >= 400)
		rVolume.w = 400;
	SDL_RenderFillRect(rR, &rVolume);

	SDL_SetRenderDrawColor(rR, 0, 0, 0, 0);
	SDL_RenderFillRect(rR, &rMute);

	// ------- 옵션 메뉴 텍스트 존 -----------

	SCore::getMap()->getText()->Draw(rR, "VOLUME", rVolumeBG.x + rVolumeBG.w / 2 - 50, rVolumeBG.y - 50);
	SCore::getMap()->getText()->Draw(rR, "MUTE", rVolumeBG.x + rVolumeBG.w / 2 - 35, rVolumeBG.y + 80);
	if (!mute)
	{
		SCore::getMap()->getText()->Draw(rR, "OFF", rVolumeBG.x + rVolumeBG.w / 2 - 25, rVolumeBG.y + 120);
	}
	else
	{
		SCore::getMap()->getText()->Draw(rR, "ON", rVolumeBG.x + rVolumeBG.w / 2 - 18, rVolumeBG.y + 120);
	}

	// ------- 옵션 메뉴 텍스트 존 -----------

	if (activeMenuOption == 0)
	{
		SDL_SetRenderDrawColor(rR, 255, 255, 255, 255);
		SDL_RenderDrawRect(rR, &rVolumeBG);
	}
	else
	{
		SDL_SetRenderDrawColor(rR, 160, 160, 160, 55);
		SDL_RenderDrawRect(rR, &rVolumeBG);
	}
}

void OptionMenu::enter()
{
	switch (activeMenuOption)
	{
	case 0:
		SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cVolumeControl);
		break;
	case 1:
		break;
	}
}

void OptionMenu::escape()
{
	if (escapeToMainMenu)
	{
		SInfo::getMM()->setStateID(SInfo::getMM()->eMainMenu);
	}
	else
	{
		SInfo::getMM()->setStateID(SInfo::getMM()->ePause);
	}
}

void OptionMenu::activeVolumeControl(int key) //Update라는 이름 수정하는게 좋을 것 같다.
{
	Menu::activeOption(key);
	// 상 하 좌 우 :: 0 1 2 3
	if (activeMenuOption == 0 && (key == 2 || key == 3))
	{
		switch (key)
		{
		case 3: //RIGHT
			if (SInfo::getMusic()->getVolume() < 100)
			{
				SInfo::getMusic()->setVolume(SInfo::getMusic()->getVolume() + 5);
			}
			else
			{
				SInfo::getMusic()->setVolume(100);
			}
			if (mute)
			{
				mute = false;
			}
			break;
		case 2: //LEFT
			if (SInfo::getMusic()->getVolume() > 0) //0보다 클 때만 볼륨 줄일 수 있다.
			{
				SInfo::getMusic()->setVolume(SInfo::getMusic()->getVolume() - 5);
			}
			else
			{
				SInfo::getMusic()->setVolume(0);
			}
			if (mute && SInfo::getMusic()->getVolume() == 0)
			{
				mute = true;
			}
			break;
		}
		updateVolumeRect();
		SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cVolumeControl);
	}
	else if (activeMenuOption == 1 && (key == 2 || key == 3))
	{
		switch (key)
		{
		case 3: //RIGHT
			swipeMute();
			break;
		case 2: //LEFT
			swipeMute();
			break;
		}
	}
}

void OptionMenu::swipeMute()
{
	if (mute) //음소거인 상태에서 다시 음소거가 아닌 상태로
	{
		SInfo::getMusic()->setVolume(muteTemp);
		mute = false;
		rVolume.w = SInfo::getMusic()->getVolume() * 4;
		SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cswipeUnmute);
	}
	else //음소거가 아닌 상태에서 다시 음소거 상태로
	{
		muteTemp = SInfo::getMusic()->getVolume();
		SInfo::getMusic()->setVolume(0);
		mute = true;
		rVolume.w = 0;
	}
}

void OptionMenu::updateVolumeRect()
{
	rVolume.w = SInfo::getMusic()->getVolume() * 4;
}

void OptionMenu::checkMouseInput(int x, int y)
{
	if (is_in_button(x, y, this->rVolumeBG))
		activeMenuOption = 0;
	else if (is_in_button(x, y, this->rMute))
		activeMenuOption = 1;
	else
		activeMenuOption = -1;
}

void OptionMenu::click(int x, int y)
{
	switch (activeMenuOption)
	{
	case 0:
		if (is_in_button(x, y, this->rVolumeBG))
		{
			SInfo::getMusic()->setVolume((x - rVolumeBG.x) / 4);
			if (mute)
				swipeMute();
		}
		updateVolumeRect();
		SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cVolumeControl);
		break;
	case 1:
		if (is_in_button(x, y, this->rMute))
			swipeMute();
		break;
	}
}

void OptionMenu::set_escapeToMainMenu(bool flag) { this->escapeToMainMenu = flag; }