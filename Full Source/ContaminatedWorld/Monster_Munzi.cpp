#include "Monster_Munzi.h"
#include "Core.h"
#include <ctime>

M_Munzi::M_Munzi() { }

M_Munzi::M_Munzi(CIMG* munzi_img, CIMG* blood_img, int x, int y, int id)
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

	max_XPos = x + interval;
	if (x - interval <= 0)
		min_XPos = 0;
	else
		min_XPos = x - interval;

	XVel = 2;
	YVel = 1;
	
	traceDistance = 50;
	attackDistance = 10;

	max_jumpDistance = 50;
	currentJumpDistance = 0;

	this->pushVel = 25;
	this->ground_change = true;

	//·£´ýÇÏ°Ô ¸ó½ºÅÍ ¹æÇâ ¼³Á¤
	srand((unsigned)time(NULL));
	bMonster_Left_Right = rand() % 2;

	bHitted = false;
	bHittedAnimation = false;
	bDie = false;
	bDieAnimation = false;
	bMonsterInAir = true;
	slope_position = 0.f;

	eMonsterTarget = MONSTER_TARGET_MEDICINE;
	targetRect[MONSTER_TARGET_CHARACTER] = { 0, 0, 0, 0 };
	targetRect[MONSTER_TARGET_MEDICINE] = { 0, 0, 0, 0 };
	eMonsterState = monsterState::Idle;
	eMonsterJumpState = monsterJumpState::Jumpping;

	cMonsterIMG = munzi_img;
	cBloodIMG = blood_img;
	
	this->Monster_Width = cMonsterIMG[0].getRect().w;
	this->Monster_Height = cMonsterIMG[0].getRect().h;
	monsterHP = 100;
	max_HP = 100;
	damage = 20;
	damage_ratio = (float)damage / (float)max_HP;
	HPbarWidth = 80;

	HP_Rect = { (int)(x + Monster_Width / 2 - HPbarWidth / 2),  y - 10, (int)HPbarWidth, 8 };
	HP_Cut = { (int)((x + Monster_Width / 2 - HPbarWidth / 2) + HPbarWidth),  y - 10, 0, 8 };
	Cut_Ratio = (float)(HP_Rect.w * damage) / (float)(max_HP);
	Cut_Rest = 0.f;
}

M_Munzi::~M_Munzi()
{
	
}


void M_Munzi::Update()
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

	setMonsterState(); // Set the Monster state // The Place into which I can put the AI algorithm.
	moveMonster(); // X axis
	monsterPhysics(); // Y axis
}

void M_Munzi::Draw(SDL_Renderer* rR, SDL_Rect* Camera)
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
			cBloodIMG->Draw(rR, XPos+20 - Camera->x, YPos+20 - Camera->y, false);
	}

	cMonsterIMG[imgnumb].Draw(rR, XPos - Camera->x, YPos - Camera->y, !bMonster_Left_Right);
}

void M_Munzi::setMonsterState()
{
	int mX = XPos;
	int mY = YPos;
	int mW = Monster_Width;
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

void M_Munzi::monsterPhysics()
{
	// ¸ó½ºÅÍÀÇ Ground°¡ ¾ÈÃ£¾Æ Á³´Ù¸é
	if(!ground_change)
	{
		YVel = 2;
		// ¸ó½ºÅÍ°¡ °øÁß¿¡ ÀÖÁö ¾Ê´Ù¸é
		if (eMonsterJumpState == monsterJumpState::Jumpping)
		{
			updateYPos(-YVel);
			currentJumpDistance += YVel;
			if (currentJumpDistance >= max_jumpDistance)
			{
				eMonsterJumpState = monsterJumpState::Falling;
			}
		}
		else if (eMonsterJumpState == monsterJumpState::Falling)
		{
			updateYPos(YVel);
			currentJumpDistance -= YVel;
	
			if (currentJumpDistance <= 0)
			{
				eMonsterJumpState = monsterJumpState::Jumpping;

				int row, col, slope, speed = 1;
				SDL_Rect temp{ XPos, YPos, Monster_Width, Monster_Height };
				if (SCore::getMap()->YCollisionMapObject(&row, &speed, &temp))
					ground_change = false;
				else
					ground_change = true;
			}
		}
	}
	else
	{
		YAcc = 0.986f;
		YVel += YAcc * betweenFrametime;
		updateYPos(YVel);
	}
}

void M_Munzi::moveMonster()
{
	if (eMonsterState == monsterState::Idle)
	{
		// ¸¸¾à ¿À¸¥ÂÊ ¹æÇâÀ» ÇâÇÑ´Ù¸é
		if (bMonster_Left_Right)
		{
			if (XPos >= max_XPos)
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
			if (XPos <= min_XPos)
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
		int mX = XPos;
		int cX = targetRect[eMonsterTarget].x;

		// ¸ó½ºÅÍ°¡ Ä³¸¯ÅÍ ¿À¸¥ÂÊ¿¡ ÀÖ´Ù¸é (Ä³¸¯ÅÍ , ¸ó½ºÅÍ)
		if (mX > cX)
		{
			if (bMonster_Left_Right)
				reverseDirection();

			updateXPos(-XVel);
		}
		// ¸ó½ºÅÍ°¡ Ä³¸¯ÅÍ ¿ÞÂÊ¿¡ ÀÖ´Ù¸é (¸ó½ºÅÍ , Ä³¸¯ÅÍ)
		else
		{
			if (!bMonster_Left_Right)
				reverseDirection();
			
			updateXPos(XVel);
		}
	}
	else if (eMonsterState == monsterState::Attack)
	{
		int mX = XPos;
		int cX = targetRect[eMonsterTarget].x;
		int cW = targetRect[eMonsterTarget].w;

		if (bMonster_Left_Right)
		{
			// (Ä³¸¯ÅÍ, ¸ó½ºÅÍ(¿À¸¥ÂÊ)) 
			if (mX >= cX + cW)
			{
				reverseDirection();
				updateXPos(-(XVel + 1));
			}
			else
			{	
				// ¿ìÃøÀ¸·Î ÁøÇàÇÏ´Â µµÁß È­¸é ¿À¸¥ÂÊ ³¡¿¡ µµ´ÞÇÒ ¶§
				if (XPos >= SInfo::LEVEL_WIDTH - 3)
				{
					reverseDirection();
					updateXPos(-(XVel + 1));
				}
				else
					updateXPos(XVel + 1);
			}
		}
		// ¿ÞÂÊ ¹Ù¶óº¸°íÀÖ´Âµ¥
		else
		{
			// (¸ó½ºÅÍ, Ä³¸¯ÅÍ)
			if (mX + Monster_Width <= cX)
			{
				reverseDirection();
				updateXPos(XVel + 1);
			}
			else
			{
				// ÁÂÃøÀ¸·Î ÁøÇàÇÏ´Â µµÁß È­¸é ¿ÞÂÊ ³¡¿¡ µµ´ÞÇÒ ¶§
				if (XPos <= 0 + 3) // °¨¼Ò ¼Óµµ
				{
					reverseDirection();
					updateXPos(XVel + 1);
				}
				else
					updateXPos(-(XVel + 1));
			}
		}
	}
	else if (eMonsterState == monsterState::Hitted)
	{
		if (!bHitted)
		{
			HPdown();

			int mX = XPos;
			int cX = targetRect[eMonsterTarget].x;
			int cW = targetRect[eMonsterTarget].w;

			if (cX + cW / 2 <= mX)
			{
				if (bMonster_Left_Right)
					reverseDirection();

				updateXPos((XVel * pushVel));
			}
			else if(cX + cW / 2 >= mX + Monster_Width)
			{
				if (!bMonster_Left_Right)
					reverseDirection();

				updateXPos(-(XVel * pushVel));
			}
			else
			{
				if (cX + cW / 2 <= mX + Monster_Width / 2)
				{
					if (bMonster_Left_Right)
						reverseDirection();

					updateXPos((XVel * pushVel));
				}
				else if (cX + cW / 2 >= mX + Monster_Width / 2)
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
	else if (eMonsterState == monsterState::Die)
		dieAnimation();
}

void M_Munzi::updateXPos(int speed)
{
	XPos += speed;

	if ((XPos < 0))
	{
		if (eMonsterState == monsterState::Idle)
			reverseDirection();
		XPos = 0;
	}
	else if (XPos + Monster_Width > SInfo::LEVEL_WIDTH)
	{
		if (eMonsterState == monsterState::Idle)
			reverseDirection();
		XPos = SInfo::LEVEL_WIDTH - Monster_Width;
	}

	SDL_Rect temp{ XPos, YPos, Monster_Width, Monster_Height };
	int col;
	if (SCore::getMap()->XCollisionMapObject(&col, &temp))
	{
		XPos -= SCore::getMap()->getXPenetrationDistance(&col, &temp);

		if (eMonsterState == monsterState::Idle)
			reverseDirection();
	}

	HP_Rect.x = (int)(XPos + Monster_Width / 2 - HPbarWidth / 2);
	HP_Cut.x = HP_Rect.x + HP_Rect.w - HP_Cut.w;
}

void M_Munzi::updateYPos(int speed)
{
	YPos += speed;

	if (YPos < 0)
		YPos = 0;
	else if(YPos + Monster_Height > SInfo::LEVEL_HEIGHT)
		YPos -= SInfo::LEVEL_HEIGHT - Monster_Height;
	
	SDL_Rect temp{ XPos, YPos, Monster_Width, Monster_Height };
	int row, col;
	if (SCore::getMap()->YCollisionMapObject(&row, &speed, &temp))
	{
		YPos -= SCore::getMap()->getYPenetrationDistance(&row, &temp);
		ground_change = false;
	}

	if (SCore::getMap()->isSlopeTile(&row, &col, &temp) >= 0)
	{
		slope_position = SCore::getMap()->getSlopePosition(&row, &col, &temp);

		if (YPos >= slope_position)
			YPos = slope_position;
	}

	HP_Rect.y = HP_Cut.y = YPos - 10;
}

void M_Munzi::HPdown()
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
	
	
if(monsterHP <= 0)
		monsterHP = 0;
	if (monsterHP == 0)
	{
		eMonsterState = monsterState::Die;
		bDie = true;
	}
}


void M_Munzi::changeDirection(bool direction)
{
	bMonster_Left_Right = direction;
}

void M_Munzi::reverseDirection()
{
	bMonster_Left_Right = ( (bMonster_Left_Right) ? false : true);
}


void M_Munzi::moveAnimation()
{
	if (SDL_GetTicks() - 30 * XVel > iMoveAnimationTime)
	{
		iMoveAnimationTime = SDL_GetTicks();

		if (imgnumb >= 14)
			imgnumb = 0;
		else
			++imgnumb;
	}
}

void M_Munzi::attackAnimation()
{
	if (SDL_GetTicks() - 30 * XVel > iMoveAnimationTime)
	{
		iMoveAnimationTime = SDL_GetTicks();

		if (imgnumb < 15 || imgnumb >= 29)
			imgnumb = 15;
		else
			++imgnumb;
	}
}

void M_Munzi::hittedAnimation()
{
	if (eMonsterState != monsterState::Die)
	{
		if (!bHittedAnimation)
		{
			iMoveAnimationTime = SDL_GetTicks();
			bHittedAnimation = true;
		}
		else if (SDL_GetTicks() - iMoveAnimationTime >= 200)
		{
			eMonsterState = monsterState::Attack;
			bHittedAnimation = false;
			bHitted = false;
		}
	}
}

void M_Munzi::dieAnimation()
{
	if (!bDieAnimation)
	{
		iMoveAnimationTime = SDL_GetTicks();
		bDieAnimation = true;
	}
	if (SDL_GetTicks() - iMoveAnimationTime >= 300)
	{
		bDieAnimation = false;
		bDie = true;
	}
}


void M_Munzi::setDamage_ratio(float ratio)
{
	this->damage_ratio += ratio;

	// ÃÖ¼Ò 10%, ÃÖ´ë 90%ÀÇ µ¥¹ÌÁö ºñÀ²À» À¯Áö
	if (damage_ratio <= 0.1)
		damage_ratio = 0.1;	
	if (damage_ratio >= 0.9)
		damage_ratio = 0.9;

	damage = max_HP * damage_ratio;
	Cut_Ratio = (float)(HP_Rect.w * damage / max_HP);
}


float M_Munzi::getXPos() { return XPos; }
float M_Munzi::getYPos() { return YPos; }
int M_Munzi::getWidth() { return Monster_Width; }
int M_Munzi::getHeight() { return Monster_Height; }
int M_Munzi::getImgnumb() { return imgnumb; }
int M_Munzi::getMonsterState() { return (int)eMonsterState; }
bool M_Munzi::getbDie() { return bDie; }
void M_Munzi::setID(int ID) { id = ID; }
void M_Munzi::set_HittedMonsterState() { this->eMonsterState = monsterState::Hitted; }

