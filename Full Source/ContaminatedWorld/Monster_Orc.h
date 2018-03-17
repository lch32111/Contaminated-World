#ifndef _MONSTER_ORC_H
#define _MONSTER_ORC_H

#include "header.h"
#include "CIMG.h"
#include <vector>

class M_Orc
{
private:
	int id;
	CIMG* cMonsterIMG;
	CIMG* cBloodIMG;
	int imgnumb;

	unsigned int previousFrameTime;
	unsigned int currentFrameTime;
	float betweenFrametime;
	unsigned int iMoveAnimationTime;

	float XPos, YPos;
	float YAcc;
	float interval;
	float max_XPos, max_YPos, min_XPos, min_YPos;
	float XVel, YVel;
	float Cut_Ratio;
	float Cut_Rest;

	int traceDistance, attackDistance;

	enum Orc_Collider
	{
		DEFAULT_MOVE_COLLIDER,
		HIT_ATTACK_COLLIDER,
		Orc_COLLIDER_COUNT
	};
	Orc_Collider cursorCollider;
	SDL_Rect rMonsterCollider[Orc_Collider::Orc_COLLIDER_COUNT];

	enum monsterTarget
	{
		MONSTER_TARGET_CHARACTER,
		MONSTER_TARGET_MEDICINE,
		MONSTER_TARGET_COUNT
	};

	enum class monsterState
	{
		Idle,		// 휴먼상태
		Trace,		// 추적상태
		Attack,		// 공격상태
		Hitted,		// 맞는상태
		Die			// 사망상태
	};

	SDL_Rect targetRect[MONSTER_TARGET_COUNT];
	monsterTarget eMonsterTarget;
	monsterState eMonsterState;

	int pushVel;

	// true = right, false = left
	bool bMonster_Left_Right;
	bool bHitted;
	bool bHittedAnimation;
	bool bDie;
	bool bDieAnimation;
	float slope_position;

	int monsterHP;
	int max_HP;
	int damage;
	float damage_ratio;
	float HPbarWidth;

	SDL_Rect HP_Rect;
	SDL_Rect HP_Cut;

	int Monster_Width;
	int Monster_Height;

	void moveAnimation();
	void attackAnimation();
	void hittedAnimation();

	void setMonsterState();
	void moveMonster();
	void monsterPhysics();
	void updateCollider();
	void updateXPos(int speed);
	void updateYPos(int speed);

	void hitCharacter();
	void hitMedicine();
	void HPdown();

	void changeDirection(bool direction);
	void reverseDirection();
	void resetYVel();
public:
	M_Orc();
	M_Orc(CIMG* orc_img, CIMG* blood_img, int x, int y, int id);
	~M_Orc();

	void Update();
	void Draw(SDL_Renderer* rR, SDL_Rect* Camera);

	/*----get & set ----*/
	int getXPos();
	int getYPos();
	int getWidth();
	int getHeight();
	int getImgnumb();
	int getMonsterState();
	bool getbDie();
	void setID(int ID);
	void set_HittedMonsterState();
	void setDamage_ratio(float ratio);
};

#endif
