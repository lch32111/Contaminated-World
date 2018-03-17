#pragma once

#ifndef MONSTER_MUNZI_H
#define MONSTER_MUNZI_H

#include "header.h"
#include "CIMG.h"
#include <vector>

class M_Munzi
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

	int max_jumpDistance;
	int currentJumpDistance;

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

	enum class monsterJumpState
	{
		Jumpping,
		Falling,
		//Jump_default
	};

	SDL_Rect targetRect[MONSTER_TARGET_COUNT];
	monsterTarget eMonsterTarget;
	monsterState eMonsterState;
	monsterJumpState eMonsterJumpState;

	int pushVel;
	bool ground_change;

	// true = right, false = left
	bool bMonster_Left_Right;
	bool bHitted;
	bool bHittedAnimation;
	bool bDie;
	bool bDieAnimation;
	bool bMonsterInAir;
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
	void dieAnimation();

	void setMonsterState();
	void moveMonster();
	void monsterPhysics();
	void updateXPos(int speed);
	void updateYPos(int speed);

	void HPdown();

	void changeDirection(bool direction);
	void reverseDirection();
public:
	M_Munzi();
	M_Munzi(CIMG* munzi_img, CIMG* blood_img, int x, int y, int id);
	~M_Munzi();

	void Update();
	void Draw(SDL_Renderer* rR, SDL_Rect* Camera);

	void setDamage_ratio(float ratio);

	/*----get & set ----*/
	float getXPos();
	float getYPos();
	int getWidth();
	int getHeight();
	int getImgnumb();
	int getMonsterState();
	bool getbDie();
	void setID(int ID);
	void set_HittedMonsterState();
};
#endif