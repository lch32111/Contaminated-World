#include "header.h"
#include "Menu.h"

Menu::Menu()
{
	activeMenuOption = -1;
	menuXpos = menuYpos = 0;
}

Menu::~Menu()
{

}

bool Menu::is_in_button(int x, int y, SDL_Rect button)
{
	if (x < button.x || x > button.x + button.w || y < button.y || y > button.y + button.h)
		return false;
	else
		return true;
}


void Menu::activeOption(int key)
{
	// ╩С го аб ©Л : 0 1 2 3
	switch (key)
	{
	case 0: // Up
		if (activeMenuOption - 1 >= 0)
		{
			--activeMenuOption;
		}
		break;
	case 1: // Down
		if (activeMenuOption + 1 <= (numOfMenu - 1))
		{
			++activeMenuOption;
		}
		break;
	default:
		break;
	}
}

void Menu::resetActiveOption()
{
	activeMenuOption = 0;
}