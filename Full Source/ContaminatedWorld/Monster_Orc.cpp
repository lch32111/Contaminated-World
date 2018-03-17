#include "Monster_Orc.h"
#include "Core.h"
#include <ctime>

template<typename T> inline const T abs(T const& x) { return (x < 0) ? -x : x; }

M_Orc::M_Orc() { }

M_Orc::M_Orc(CIMG* orc_img, CIMG* blood_img, int x, int y, int id)
{
	this->id = id;
	this->imgnumb = 0;

	this->previousFrameTime = 0;
	this->currentFrameTime = 0;
	this->betweenFrametime = 0;
	this->iMoveAnimationTime = 0;

	this->XPos = x;
	this->YPos = y;
	this->YAcc = 0;
	this->interval = 3500;

	this->cursorCollider = Orc_Collider::DEFAULT_MOVE_COLLIDER;
	rMonsterCollider[DEFAULT_MOVE_COLLIDER].x = XPos + 57;
	rMonsterCollider[DEFAULT_MOVE_COLLIDER].y = YPos + 5;
	rMonsterCollider[DEFAULT_MOVE_COLLIDER].w = 68;
	rMonsterCollider[DEFAULT_MOVE_COLLIDER].h = 103;
	rMonsterCollider[HIT_ATTACK_COLLIDER].x = XPos + 4;
	rMonsterCollider[HIT_ATTACK_COLLIDER].y = YPos + 23;
	rMonsterCollider[HIT_ATTACK_COLLIDER].w = 41;
	rMonsterCollider[HIT_ATTACK_COLLIDER].h = 19;

	max_XPos = x + interval;
	if (x - interval <= 0)
		min_XPos = 0;
	else
		min_XPos = x - interval;

	XVel = 2;
	YVel = 1;

	traceDistance = 50;
	attackDistance = 15;

	this->pushVel = 25;

	//·£´ýÇÏ°Ô ¸ó½ºÅÍ ¹æÇâ ¼³Á¤
	srand((unsigned)time(NULL));
	bMonster_Left_Right = rand() % 2;

	bHitted = false;
	bHittedAnimation = false;
	bDie = false;
	bDieAnimation = false;
	slope_position = 0.f;

	eMonsterTarget = MONSTER_TARGET_MEDICINE;
	targetRect[MONSTER_TARGET_CHARACTER] = { 0, 0, 0, 0 };
	targetRect[MONSTER_TARGET_MEDICINE] = { 0, 0, 0, 0 };
	eMonsterState = monsterState::Idle;

	cMonsterIMG = orc_img;

	// Hitted IMG
	cBloodIMG = blood_img;

	this->Monster_Width = cMonsterIMG[0].getRect().w;
	this->Monster_Height = cMonsterIMG[0].getRect().h;
	monsterHP = 100;
	max_HP = 100;
	damage = 10;
	damage_ratio = (float)damage / (float)max_HP;
	HPbarWidth = 80;

	HP_Rect = { (int)(x + Monster_Width / 2 - HPbarWidth / 2),  y - 10, (int)HPbarWidth, 8 };
	HP_Cut = { (int)((x + Monster_Width / 2 - HPbarWidth / 2) + HPbarWidth),  y - 10, 0, 8 };
	Cut_Ratio = (float)(HP_Rect.w * damage) / (float)(max_HP);
	Cut_Rest = 0.f;
}

M_Orc::~M_Orc()
{

}


void M_Orc::Update()
{
	// calculate the time between currend and previous frame.
	previousFrameTime = currentFrameTime;
	currentFrameTime = SDL_GetTicks();
	betweenFrametime = (currentFrameTime - previousFrameTime) / 1000.f; // ÃÊ´ÜÀ§·Î ¸¸µé±â À§ÇØ, 1000À» ³ª´²ÁÜ.
	if (currentFrameTime - previousFrameTime > 1000) betweenFrametime = 16 / 1000.f; // Reset ÇßÀ» ¶§ °ªÀÇ Â÷ÀÌ°¡ ¸¹ÀÌ ³ª±â ¶§¹®¿¡ ¼Óµµ ¿¡·¯¹æÁö ÄÚµåÀÓ.

	if (eMonsterState == monsterState::Hitted)
	{
		eMonsterTarget = MONSTER_TARGET_CHARACTER;
	}

	// Target Update
	if (eMonsterTarget == MONSTER_TARGET_CHARACTER)
	{
		targetRect[MONSTER_TARGET_CHARACTER] = SCore::getMap()->getPlayer()->getRect();
	}
	else if (eMonsterTarget == MONSTER_TARGET_MEDICINE)
	{
		targetRect[MONSTER_TARGET_MEDICINE] = SCore::getMap()->getMedicine()->getRect();
	}

	updateCollider();
	setMonsterState(); // Set the Monster state // The Place into which I can put the AI algorithm.
	moveMonster(); // X axis
	monsterPhysics(); // Y axis
}

void M_Orc::Draw(SDL_Renderer* rR, SDL_Rect* Camera)
{
	if (eMonsterState == monsterState::Attack || eMonsterState == monsterState::Hitted)
	{
		SDL_Rect temp = HP_Rect, temp2 = HP_Cut;
		temp.x -= Camera->x; temp.y -= Camera->y;
		temp2.x -= Camera->x; temp2.y -= Camera->y;

		SDL_SetRenderDrawColor(rR, 0, 0xFF, 0, 0xFF);
		SDL_RenderFillRect(rR, &temp);
		SDL_SetRenderDrawColor(rR, 0, 0, 0, 0xFF);
		SDL_RenderFillRect(rR, &temp2);

		if (eMonsterState == monsterState::Hitted)
			cBloodIMG->Draw(rR, rMonsterCollider[cursorCollider].x + 20 - Camera->x, rMonsterCollider[cursorCollider].y + 20 - Camera->y, false);
	}

	cMonsterIMG[imgnumb].Draw(rR, XPos - Camera->x, YPos - Camera->y, !bMonster_Left_Right);

	// DEBUG START
	/*
	SDL_SetRenderDrawColor(rR, 255, 0, 0, 0xFF);
	SDL_Rect colliR{ XPos - Camera->x, YPos - Camera->y, Monster_Width, Monster_Height };
	SDL_RenderDrawRect(rR, &colliR);

	colliR = rMonsterCollider[cursorCollider];
	colliR.x -= Camera->x; colliR.y -= Camera->y;
	SDL_SetRenderDrawColor(rR, 0, 153, 255, 255);
	SDL_RenderDrawRect(rR, &colliR);

	if (eMonsterState == monsterState::Attack)
	{
		colliR = rMonsterCollider[HIT_ATTACK_COLLIDER];
		colliR.x -= Camera->x; colliR.y -= Camera->y;
		SDL_SetRenderDrawColor(rR, 255, 38, 168, 255);
		SDL_RenderDrawRect(rR, &colliR);
	}
	*/
	// DEBUG END
}

void M_Orc::setMonsterState()
{
	int mX = rMonsterCollider[cursorCollider].x;
	int mY = rMonsterCollider[cursorCollider].y;
	int mW = rMonsterCollider[cursorCollider].w;
	int tX = targetRect[eMonsterTarget].x;
	int tY = targetRect[eMonsterTarget].y;
	int tW = targetRect[eMonsterTarget].w;

	if (eMonsterState != monsterState::Die)
	{
		if (eMonsterState != monsterState::Hitted)
		{
			// Monster Target ÀÌ¶ó¸é
			if (mX + mW < tX)
			{
				// Å¸°ÙÀÌ ¸ó½ºÅÍ °ø°Ý ¹üÀ§ ³»¿¡ ÀÖÀ» ¶§ + YÃà °£ÀÇ Â÷ÀÌµµ Àû¾î¾ßÇÔ.
				if (abs(mX + mW - tX) <= traceDistance && abs(mY - tY) <= 50)
				{
					
					if (abs(mX + mW - tX) <= attackDistance)
						eMonsterState = monsterState::Attack;
					else
						eMonsterState = monsterState::Trace;
				}
				else
					eMonsterState = monsterState::Idle;
			}
			// Target Monster ÀÌ¶ó¸é
			else if (tX + tW < mX)
			{
				if (abs(mX - (tX + tW)) <= traceDistance &&  abs(mY - tY) <= 50)
				{
					if (abs(mX - (tX + tW)) <= attackDistance)
					{
						eMonsterState = monsterState::Attack;
					}
					else
						eMonsterState = monsterState::Trace;
				}
				else
					eMonsterState = monsterState::Idle;
			}
		}
	}
	else
		bDie = true;
}

void M_Orc::monsterPhysics()
{
	if (eMonsterState != monsterState::Die)
	{
		updateYPos(5);
		int PlatformType = SCore::getMap()->getBottomCollidedPlatformType(&rMonsterCollider[cursorCollider]);

		// Solid
		if (PlatformType == 1)
		{
			YVel = 5;
		}
		// Slope
		else if (PlatformType == 2)
		{
			updateYPos(5);
		}
		// Background or not collided
		else
		{
			YAcc = 1.986f;
			YVel += YAcc * betweenFrametime;
			updateYPos(YVel);
		}
	}
}

void M_Orc::moveMonster()
{
	if (eMonsterState == monsterState::Idle)
	{
		// ¸¸¾à ¿À¸¥ÂÊ ¹æÇâÀ» ÇâÇÑ´Ù¸é
		if (bMonster_Left_Right)
		{
			if (rMonsterCollider[cursorCollider].x >= max_XPos)
			{
				reverseDirection();
				updateXPos(-XVel);
			}
			else if (rMonsterCollider[cursorCollider].x + rMonsterCollider[cursorCollider].w >= SInfo::LEVEL_WIDTH)
			{
				reverseDirection();
				updateXPos(-XVel);
			}
			else
				updateXPos(XVel);
		}
		// ¿ÞÂÊÀ» ÇâÇÏ°í ÀÖ´Ù¸é
		else
		{
			if (rMonsterCollider[cursorCollider].x <= min_XPos)
			{
				reverseDirection();
				updateXPos(XVel);
			}
			else if (rMonsterCollider[cursorCollider].x <= 0)
			{
				reverseDirection();
				updateXPos(XVel);
			}
			else
				updateXPos(-XVel);
		}
	}
	else if (eMonsterState == monsterState::Trace)
	{
		int mX = rMonsterCollider[cursorCollider].x;
		int mW = rMonsterCollider[cursorCollider].w;
		int tX = targetRect[eMonsterTarget].x;
		int tW = targetRect[eMonsterTarget].w;

		// ¸ó½ºÅÍ°¡ Å¸°Ù ¿À¸¥ÂÊ¿¡ ÀÖ´Ù¸é (Å¸°Ù , ¸ó½ºÅÍ)
		if (mX > tX + tW)
		{
			if (bMonster_Left_Right)
				reverseDirection();

			updateXPos(-XVel);
		}
		// ¸ó½ºÅÍ°¡ Å¸°Ù ¿ÞÂÊ¿¡ ÀÖ´Ù¸é (¸ó½ºÅÍ , Å¸°Ù)
		else if(mX + mW < tX)
		{
			if (!bMonster_Left_Right)
				reverseDirection();

			updateXPos(XVel);
		}
	}
	else if (eMonsterState == monsterState::Attack)
	{
		int mX = rMonsterCollider[cursorCollider].x;
		int cX = targetRect[eMonsterTarget].x;
		int cW = targetRect[eMonsterTarget].w;

		if (bMonster_Left_Right)
		{
			// (Ä³¸¯ÅÍ, ¸ó½ºÅÍ(¿À¸¥ÂÊ)) 
			if (mX >= cX + cW)
			{
				reverseDirection();
			}
			else
			{
				// ¿ìÃøÀ¸·Î ÁøÇàÇÏ´Â µµÁß È­¸é ¿À¸¥ÂÊ ³¡¿¡ µµ´ÞÇÒ ¶§
				if (rMonsterCollider[cursorCollider].x >= SInfo::LEVEL_WIDTH - 3)
					reverseDirection();
			}
		}
		// ¿ÞÂÊ ¹Ù¶óº¸°íÀÖ´Âµ¥
		else
		{
			// (¸ó½ºÅÍ, Ä³¸¯ÅÍ)
			if (mX + rMonsterCollider[cursorCollider].w <= cX)
			{
				reverseDirection();
			}
			else
			{
				// ÁÂÃøÀ¸·Î ÁøÇàÇÏ´Â µµÁß È­¸é ¿ÞÂÊ ³¡¿¡ µµ´ÞÇÒ ¶§
				if (rMonsterCollider[cursorCollider].x <= 0 + 3) // °¨¼Ò ¼Óµµ
				{
					reverseDirection();
				}
			}
		}
	}
	else if (eMonsterState == monsterState::Hitted)
	{
		if (!bHitted)
		{
			HPdown();

			int mX = rMonsterCollider[cursorCollider].x;
			int cX = targetRect[eMonsterTarget].x;
			int cW = targetRect[eMonsterTarget].w;

			if (cX + cW / 2 <= mX)
			{
				if (bMonster_Left_Right)
					reverseDirection();

				updateXPos((XVel * pushVel));
			}
			else if (cX + cW / 2 >= mX + rMonsterCollider[cursorCollider].w)
			{
				if (!bMonster_Left_Right)
					reverseDirection();

				updateXPos(-(XVel * pushVel));
			}
			else
			{
				if (cX + cW / 2 <= mX + rMonsterCollider[cursorCollider].w / 2)
				{
					if (bMonster_Left_Right)
						reverseDirection();

					updateXPos((XVel * pushVel));
				}
				else if (cX + cW / 2 >= mX + rMonsterCollider[cursorCollider].w / 2)
				{

					if (!bMonster_Left_Right)
						reverseDirection();

					updateXPos(-(XVel * pushVel));
				}
			}

			bHitted = true;
		}

		hittedAnimation();
	}


	if (eMonsterState == monsterState::Idle || eMonsterState == monsterState::Trace)
		moveAnimation();
	else if (eMonsterState == monsterState::Attack)
		attackAnimation();
}

void M_Orc::updateCollider()
{
	// imgnumb
	// Run 0 ~ 10
	// Hit 11 ~ 16
	if (this->imgnumb >= 11 && this->imgnumb <= 16)
	{
		if (bMonster_Left_Right) // Right
			rMonsterCollider[Orc_Collider::HIT_ATTACK_COLLIDER].x = XPos + 129;
		else
			rMonsterCollider[Orc_Collider::HIT_ATTACK_COLLIDER].x = XPos + 4;
		rMonsterCollider[Orc_Collider::HIT_ATTACK_COLLIDER].y = YPos + 23;
	}
	else
	{
		cursorCollider = Orc_Collider::DEFAULT_MOVE_COLLIDER;
		if (bMonster_Left_Right) // Right
			rMonsterCollider[Orc_Collider::DEFAULT_MOVE_COLLIDER].x = XPos + 49;
		else
			rMonsterCollider[Orc_Collider::DEFAULT_MOVE_COLLIDER].x = XPos + 57;
		rMonsterCollider[Orc_Collider::DEFAULT_MOVE_COLLIDER].y = YPos + 5;
	}
}

void M_Orc::updateXPos(int speed)
{
	XPos += speed;
	rMonsterCollider[cursorCollider].x += speed;

	if (rMonsterCollider[cursorCollider].x < 0)
	{
		XPos = 0 - (rMonsterCollider[cursorCollider].x - XPos);
		rMonsterCollider[cursorCollider].x = 0;
	}
	else if (rMonsterCollider[cursorCollider].x + rMonsterCollider[cursorCollider].w > SInfo::LEVEL_WIDTH)
	{
		XPos = XPos - (rMonsterCollider[cursorCollider].x + rMonsterCollider[cursorCollider].w - SInfo::LEVEL_WIDTH);
		rMonsterCollider[cursorCollider].x = SInfo::LEVEL_WIDTH - rMonsterCollider[cursorCollider].w;
	}

	int col;
	if (SCore::getMap()->XCollisionMapObject(&col, &rMonsterCollider[cursorCollider]))
	{
		int Xpenetration = SCore::getMap()->getXPenetrationDistance(&col, &rMonsterCollider[cursorCollider]);
		rMonsterCollider[cursorCollider].x -= Xpenetration;
		XPos -= Xpenetration;
	}

	HP_Rect.x = (int)(XPos + Monster_Width / 2 - HPbarWidth / 2);
	HP_Cut.x = HP_Rect.x + HP_Rect.w - HP_Cut.w;
}

void M_Orc::updateYPos(int speed)
{
	YPos += speed;
	rMonsterCollider[cursorCollider].y += speed;

	if (rMonsterCollider[cursorCollider].y < 0)
	{
		YPos = 0;
		rMonsterCollider[cursorCollider].y = 0;
	}
	else if (rMonsterCollider[cursorCollider].y + rMonsterCollider[cursorCollider].h > SInfo::LEVEL_WIDTH)
	{
		YPos = YPos - (rMonsterCollider[cursorCollider].y + rMonsterCollider[cursorCollider].h - SInfo::LEVEL_WIDTH);
		rMonsterCollider[cursorCollider].y = SInfo::LEVEL_WIDTH - rMonsterCollider[cursorCollider].h;
	}

	int row, col;
	if (SCore::getMap()->YCollisionMapObject(&row, &speed, &rMonsterCollider[cursorCollider]))
	{
		int YPenetration = SCore::getMap()->getYPenetrationDistance(&row, &rMonsterCollider[cursorCollider]);
		rMonsterCollider[cursorCollider].y -= YPenetration;
		YPos -= YPenetration;
		resetYVel();
	}

	if (SCore::getMap()->isSlopeTile(&row, &col, &rMonsterCollider[cursorCollider]) >= 0)
	{
		slope_position = SCore::getMap()->getSlopePosition(&row, &col, &rMonsterCollider[cursorCollider]);

		if (rMonsterCollider[cursorCollider].y >= slope_position)
		{
			YPos = slope_position - (rMonsterCollider[cursorCollider].y - YPos);
			rMonsterCollider[cursorCollider].y = slope_position;
		}
	}

	HP_Rect.y = HP_Cut.y = YPos - 10;
}

void M_Orc::hitCharacter()
{
	SCore::getMap()->AttackCollisionCharacter(&rMonsterCollider[Orc_Collider::HIT_ATTACK_COLLIDER]);
}

void M_Orc::hitMedicine()
{
	SCore::getMap()->AttackCollisionMedicine(&rMonsterCollider[Orc_Collider::HIT_ATTACK_COLLIDER]);
}

void M_Orc::HPdown()
{
	if (monsterHP > 0)
	{
		monsterHP -= damage;
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
	}
	if (monsterHP <= 0)
		monsterHP = 0;

	if (monsterHP == 0)
	{
		eMonsterState = monsterState::Die;
		bDie = true;
	}
}


void M_Orc::changeDirection(bool direction)
{
	bMonster_Left_Right = direction;
}

void M_Orc::reverseDirection()
{
	bMonster_Left_Right = ((bMonster_Left_Right) ? false : true);
}

void M_Orc::resetYVel()
{
	YVel = 5;
}


void M_Orc::moveAnimation()
{
	if (SDL_GetTicks() - 30 * XVel > iMoveAnimationTime)
	{
		iMoveAnimationTime = SDL_GetTicks();

		if (imgnumb >= 10)
			imgnumb = 0;
		else
			++imgnumb;
	}
}

void M_Orc::attackAnimation()
{
	if (SDL_GetTicks() - 50 * XVel > iMoveAnimationTime)
	{
		iMoveAnimationTime = SDL_GetTicks();

		if (imgnumb == 15)
			if (eMonsterTarget == MONSTER_TARGET_CHARACTER)
				hitCharacter();
			else if (eMonsterTarget == MONSTER_TARGET_MEDICINE)
				hitMedicine();

		if (imgnumb < 11 || imgnumb >= 16)
			imgnumb = 11;
		else
			++imgnumb;
	}
}

void M_Orc::hittedAnimation()
{
	if (eMonsterState != monsterState::Die)
	{
		if (!bHittedAnimation)
		{
			iMoveAnimationTime = SDL_GetTicks();
			cMonsterIMG[imgnumb].setAlpha(cMonsterIMG[imgnumb].getIMG(), 150);
			bHittedAnimation = true;
		}
		else if (SDL_GetTicks() - iMoveAnimationTime >= 200)
		{
			// ÀÏÁ¤½Ã°£ÀÌ Áö³ª¸é Åõ¸íµµ¸¦ ¿ø·¡´ë·Î µ¹·ÁÁÜ
			cMonsterIMG[imgnumb].resetAlpah(cMonsterIMG[imgnumb].getIMG());

			eMonsterState = monsterState::Attack;
			bHittedAnimation = false;
			bHitted = false;
		}
	}
}

void M_Orc::setDamage_ratio(float ratio)
{
	this->damage_ratio += ratio;

	// ÃÖ¼Ò 1%, ÃÖ´ë 99%ÀÇ µ¥¹ÌÁö ºñÀ²À» À¯Áö
	if (damage_ratio <= 0)
		damage_ratio = 0.01;
	if (damage_ratio >= 1)
		damage_ratio = 0.99;

	damage = max_HP * damage_ratio;
	Cut_Ratio = (float)(HP_Rect.w * damage / max_HP);
}

int M_Orc::getXPos() { return rMonsterCollider[cursorCollider].x; }
int M_Orc::getYPos() { return rMonsterCollider[cursorCollider].y; }
int M_Orc::getWidth() { return rMonsterCollider[cursorCollider].w; }
int M_Orc::getHeight() { return rMonsterCollider[cursorCollider].h; }
int M_Orc::getImgnumb() { return imgnumb; }
int M_Orc::getMonsterState() { return (int)eMonsterState; }
bool M_Orc::getbDie() { return bDie; }
void M_Orc::setID(int ID) { id = ID; }
void M_Orc::set_HittedMonsterState() { this->eMonsterState = monsterState::Hitted; }
