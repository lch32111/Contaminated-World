#include "header.h"
#include "Menu.h"

Menu::Menu()
{
	activeMenuOption = 0;
}

void Menu::activeOption(int key)
{
	switch (key)
	{
		case 0:
			if (activeMenuOption + 1 <= (numOfMenu - 1))
			{
				activeMenuOption++;
			}
			break;
		case 1:
			if (activeMenuOption - 1 >= 0 )
			{
				activeMenuOption--;
			}
			break;
	}
	
}
