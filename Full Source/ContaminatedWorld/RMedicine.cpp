#include "RMedicine.h"
#include "Core.h"

RMedicine::RMedicine() {}
RMedicine::RMedicine(CIMG* img ,int x, int y)
{
	cMedicine = img;
	MRect = { x, y, cMedicine->getRect().w, cMedicine->getRect().h };

	HP = max_HP = 600;
	damage = 20;
	damage_ratio = (float)damage / (float)max_HP;

	HP_Rect = { x, y - 30, 100, 8 };
	HP_Cut = { x + 100, y - 30, 0, 8 };
	Cut_Ratio = (float)(HP_Rect.w * damage) / (float)(max_HP);
	Cut_Rest = 0.f;

	isAvailable = true;
	ishitted = false;
	firsthit = false;

	iTimePassed = 0;
	iTimePassed2 = 0;
}

void RMedicine::Update()
{
	if(isAvailable)
	{
		if (!ishitted)
			if (SCore::getMap()->CollisionBodyMonster(&MRect))
				ishitted = true;

		if (ishitted)
		{
			// ¸ÂÀº ½ÃÁ¡¿¡ ½Ã°£ ¼³Á¤
			if (firsthit == false)
			{
				iTimePassed2 = SDL_GetTicks();
				firsthit = true;
			}

			HPdown();

			// 1ÃÊ°¡ Áö³ª¸é hitted°¡ Ç®·Á¼­ Åõ¸í»óÅÂ¸¦ Ç®¾î³õÀ½
			if (SDL_GetTicks() - iTimePassed2 >= 1000)
			{
				iTimePassed2 = SDL_GetTicks();
				ishitted = false;
				firsthit = false;
			}
		}
	}
}

void RMedicine::HPdown()
{
	// 1ÃÊ¿¡ ÇÑ ¹ø¾¿¸¸ ÇÇ°¡ ´âÀ½
	if (SDL_GetTicks() - iTimePassed >= 1000)
	{
		iTimePassed = SDL_GetTicks();
		HP -= damage;
		HP_Cut.w += Cut_Ratio;

		// 소수점 값을 저장 후 1이 넘어가면 HP_Cut.w에 더해준다.
		Cut_Rest += Cut_Ratio - (int)Cut_Ratio;
		if (Cut_Rest > 1)
		{
			HP_Cut.w += (int)Cut_Rest;
			Cut_Rest -= (int)Cut_Rest;
		}
		if (HP_Cut.w > HP_Rect.w)
			HP_Cut.w = HP_Rect.w;

		HP_Cut.x = HP_Rect.x + HP_Rect.w - HP_Cut.w;	// HP_Cut.x + HP_Cut.w = HP_Rect.x + HP_Rect.w (³¡ÀÌ µ¿ÀÏ)

		if (HP <= 0)
			HP = 0;

		if (HP == 0)
			isAvailable = false;
	}
}

void RMedicine::Draw(SDL_Renderer*rR, SDL_Rect* Camera)
{
	if(isAvailable)
	{
		if (ishitted)
		{
			cMedicine->setAlpha(cMedicine->getIMG(), 150);
			cMedicine->Draw(rR, MRect.x - Camera->x, MRect.y - Camera->y, false);
			
			SDL_Rect temp = HP_Rect, temp2 = HP_Cut;
			temp.x -= Camera->x; temp.y -= Camera->y;
			temp2.x -= Camera->x; temp2.y -= Camera->y;

			SDL_SetRenderDrawColor(rR, 0xFF, 38, 168, 0xFF);
			SDL_RenderFillRect(rR, &temp);
			SDL_SetRenderDrawColor(rR, 0, 0, 0, 0xFF);
			SDL_RenderFillRect(rR, &temp2);
		}
		else
		{
			cMedicine->setAlpha(cMedicine->getIMG(), 255);
			cMedicine->Draw(rR, MRect.x - Camera->x, MRect.y - Camera->y, false);
		}

		// Debug
		/*
		SDL_SetRenderDrawColor(rR, 255, 0, 0, 0xFF);
		SDL_Rect colliR{ MRect.x - Camera->x, MRect.y - Camera->y, MRect.w, MRect.h };
		SDL_RenderDrawRect(rR, &colliR);
		*/
	}
}

void RMedicine::setPosition(int x, int y) 
{ 
	MRect.x = x; MRect.y = y; 
	HP_Rect.x = x;
	HP_Cut.x = HP_Rect.x + HP_Rect.w - HP_Cut.w;
	HP_Rect.y = HP_Cut.y = y - 30;
}

bool RMedicine::getisAvailable() { return isAvailable; }
int RMedicine::getHP() { return HP; }
int RMedicine::getMaxHP() { return max_HP; }
SDL_Rect RMedicine::getRect() { return MRect; }
void RMedicine::setHitted() { ishitted = true; }
void RMedicine::setHP(int hp) { HP = hp; }

// ¹é½Å Ã¼·Â °­È­
void RMedicine::addHP(int hp) 
{
	HP += hp;
	if (HP > max_HP)
		HP = max_HP;

	HP_Cut.w = HP_Rect.w - (HP * HP_Rect.w / max_HP);
	HP_Cut.x = HP_Rect.x + HP_Rect.w - HP_Cut.w;
}	

// ¹é½Å ¹æ¾î·Â °­È­
void RMedicine::upgradeDamage() 
{
	damage_ratio--;
	if (damage_ratio <= 0)
		damage_ratio = 0.01;	// ÃÖ¼Ò µ¥¹ÌÁö ºñÀ²À» 1%·Î À¯Áö

	damage = max_HP * damage_ratio;
	Cut_Ratio = (float)(HP_Rect.w * damage / max_HP);
} 
