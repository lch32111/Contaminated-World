#pragma once
#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include "Menu.h"

class OptionMenu : public Menu
{
private:
	SDL_Rect rOptionBox;
	SDL_Rect rVolumeBG;
	SDL_Rect rVolume;
	SDL_Rect rMute;

	bool escapeToMainMenu;

	bool mute;
	int muteTemp;
	int mouseXpos;
	int mouseYpos;

public:
	OptionMenu();
	~OptionMenu();

	void Update();
	void Draw(SDL_Renderer* rR);

	void enter();
	void escape();
	void click(int x, int y);

	void activeVolumeControl(int key);
	void swipeMute();
	void updateVolumeRect();

	void checkMouseInput(int x, int y);

	void set_escapeToMainMenu(bool flag);
};

#endif // !OPTIONMENU_H
