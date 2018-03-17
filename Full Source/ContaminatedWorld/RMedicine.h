#ifndef _RMEDICINE_H_
#define _RMEDICINE_H_

#include "CIMG.h"

// Radioactive Medicine
class RMedicine
{
private:
	CIMG* cMedicine;
	SDL_Rect MRect;

	int HP, max_HP;
	int damage;
	float damage_ratio;
	SDL_Rect HP_Rect;
	SDL_Rect HP_Cut;
	int Cut_number;
	float Cut_Ratio;
	float Cut_Rest;

	bool isAvailable;
	bool ishitted;
	bool firsthit;

	unsigned int iTimePassed;
	unsigned int iTimePassed2;

	void HPdown();
public:
	RMedicine();
	RMedicine(CIMG* img, int x, int y);

	void Update();
	void Draw(SDL_Renderer*rR, SDL_Rect* camera);


	bool getisAvailable();
	int getHP();
	int getMaxHP();
	SDL_Rect getRect();
	void setHitted();
	void setPosition(int x, int y);
	void setHP(int hp);
	void addHP(int hp);
	void upgradeDamage();

};

#endif


