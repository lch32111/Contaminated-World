#include "Player.h"
#include "StaticInfo.h"
#include "Core.h"

template<typename T> inline const T abs(T const& x) { return (x < 0) ? -x : x; }

Player::Player() { }
Player::Player(CIMG* character_img, CIMG* weapon_img, int x, int y)
{
	this->score = 0;
	this->HP = this->max_HP = 500;
	this->MP = this->max_MP = 200;
	damage = 20;
	this->Cut_number = 0;

	this->bMove = false;
	this->bLeft_Right = false;
	this->bdirection_changed = false;
	this->bPlayerinAir = false;

	this->eHitState = Hitenum::Hit_Default;

	this->XPos = firstXPos = x;
	this->XVel = 0.f;
	this->max_XVel = 4;

	this->YPos = firstYPos = y;
	this->YVel = 5;
	this->YAcc = 0.f;

	slope_position = 0.f;
	this->cursorCollider = Character_Collider::DEFAULT_MOVE_COLLIDER;
	rCharacterCollider[DEFAULT_MOVE_COLLIDER].x = XPos + 67;
	rCharacterCollider[DEFAULT_MOVE_COLLIDER].y = YPos + 62;
	rCharacterCollider[DEFAULT_MOVE_COLLIDER].w = 120;
	rCharacterCollider[DEFAULT_MOVE_COLLIDER].h = 117;
	rCharacterCollider[DIE_MOVE_COLLIDER].x = XPos + 43;
	rCharacterCollider[DIE_MOVE_COLLIDER].y = YPos + 124;
	rCharacterCollider[DIE_MOVE_COLLIDER].w = 157;
	rCharacterCollider[DIE_MOVE_COLLIDER].h = 55;
	rCharacterCollider[HIT_ATTACK_COLLIDER].x = XPos + 46;
	rCharacterCollider[HIT_ATTACK_COLLIDER].y = YPos + 52;
	rCharacterCollider[HIT_ATTACK_COLLIDER].w = 47;
	rCharacterCollider[HIT_ATTACK_COLLIDER].h = 70;
	
	this->max_skillDistance = 260;
	this->min_skillDistance = 100;

	this->eJumpState = Jumpenum::Jump_Default;
	this->startJumpSpeed = 5.f;
	this->jumpDistance = 200.f;

	this->eCharacterState = Characterenum::Character_Default;
	this->bhitted_Animation = false;
	this->bDie_Animation = false;
	this->previousFrameTime = 0;
	this->currentFrameTime = 0;
	this->betweenFrametime = 0;
	this->iTimePassed = SDL_GetTicks();
	this->iMoveAnimationTime = 0;
	this->iDieAnimationTime = 0;
	this->iHPdownTime = 0;

	this->imgnumb = 0;
	this->effectNumb = 0;

	this->eCharacterWeapon = Character_Weapon::WEAPON_PUNCH;
	WeaponIMG = weapon_img,
	this->isSpearDone = true;
	this->spearRect.w = WeaponIMG[1].getRect().w;
	this->spearRect.h = WeaponIMG[1].getRect().h;
	this->spearDirection = false;
	this->axis = 0.f;
	this->spear_repetition = 0;

	CharacterIMG = character_img;
	Character_Width = CharacterIMG[0].getRect().w;
	Character_Height = CharacterIMG[0].getRect().h;
	this->HP_Rect = { x + Character_Width / 4, y - 30, 120, 15 };
	this->HP_Cut = { x + Character_Width / 4 + 120, y - 30, 0, 15 };
	this->MP_Rect = { x + Character_Width / 4, y - 15, 120, 15 };
	this->MP_Cut = { x + Character_Width / 4 + 120, y - 15, 0, 15 };

	Cut_Ratio = (float)(HP_Rect.w * damage) / (float)(max_HP);
	Cut_Rest = 0.f;

	bCalcScore = false; 
	iFrameTime = 0;

	bNow_hitted = false;
	ifirstHitTime = 0;
}

Player::~Player()
{

}

void Player::Update()
{
	// calculate the time between currend and previous frame.
	previousFrameTime = currentFrameTime;
	currentFrameTime = SDL_GetTicks();
	betweenFrametime = (currentFrameTime - previousFrameTime) / 1000.f; // ÃÊ´ÜÀ§·Î ¸¸µé±â À§ÇØ, 1000À» ³ª´²ÁÜ.
	if (currentFrameTime - previousFrameTime > 1000) betweenFrametime = 16 / 1000.f; // Reset ÇßÀ» ¶§ °ªÀÇ Â÷ÀÌ°¡ ¸¹ÀÌ ³ª±â ¶§¹®¿¡ ¼Óµµ ¿¡·¯¹æÁö ÄÚµåÀÓ.

	UpdateCollider();
	if (!isSpearDone)
		updateSpear();
	movePlayer();    // XÃà, ÀÌµ¿
	playerPhysics(); // YÃà, Á¡ÇÁ, ¹°¸® ¿ªÇÐÀ» Àû¿ëÇÏ´Â »ç¿ëÀÚÀÇ ¼Óµµ¸¦ Á¶ÀýÇØ¼­ À§Ä¡ Á¶Á¤
	UpdateHittedForOneS(); // Hitted Animation 1초만 실행하기 위한 업데이트 함수
}

void Player::UpdateCollider()
{
	// imgnumb
	// Default 0, Run 1 ~ 13, Jump 14 ~ 25, Falling 26 ~ 37, Hitted 48 --> All is default move collider
	// Hit 38 ~ 47
	// Die 49 ~ 60
	if (this->imgnumb >= 38 && this->imgnumb <= 47)
	{
		if (bLeft_Right) // Right
			rCharacterCollider[Character_Collider::HIT_ATTACK_COLLIDER].x = XPos + 169;
		else
			rCharacterCollider[Character_Collider::HIT_ATTACK_COLLIDER].x = XPos + 46;
		rCharacterCollider[Character_Collider::HIT_ATTACK_COLLIDER].y = YPos + 52;
	}
	else if (this->imgnumb >= 49 && this->imgnumb <= 60)
	{
		// After Death, change the cursorCollider in order to use DIE_MOVE_COLLIDER when updateing x,ypos
		cursorCollider = Character_Collider::DIE_MOVE_COLLIDER;
		rCharacterCollider[cursorCollider].x = XPos + 43;
		rCharacterCollider[cursorCollider].y = YPos + 124;
	}
	else
	{
		cursorCollider = Character_Collider::DEFAULT_MOVE_COLLIDER;
		if (bLeft_Right) // Right
			rCharacterCollider[Character_Collider::DEFAULT_MOVE_COLLIDER].x = XPos + 75;
		else
			rCharacterCollider[Character_Collider::DEFAULT_MOVE_COLLIDER].x = XPos + 67;
		rCharacterCollider[Character_Collider::DEFAULT_MOVE_COLLIDER].y = YPos + 62;
	}
}

void Player::UpdateHittedForOneS()
{
	if (bNow_hitted)
	{
		if (SDL_GetTicks() - ifirstHitTime >= 1000)
		{
			this->eCharacterState = Characterenum::Character_Default;
			bNow_hitted = false;
			bhitted_Animation = false;
		}
	}
}

void Player::movePlayer()
{
	// ¿òÁ÷ÀÌ°í, ¹æÇâÀÌ ¾È¹Ù²¼´Ù¸é
	if (bMove && !bdirection_changed)
	{
		// ÃÖ´ë ¼Óµµ Á¦ÇÑ
		if (XVel > max_XVel)
			--XVel;
		else if (SDL_GetTicks() - (100 + 35 * XVel) >= iTimePassed && XVel < max_XVel)
		{
			++XVel;
			iTimePassed = SDL_GetTicks();
		}
		else if (XVel == 0)
			XVel == 1;
	}
	else
	{
		if (SDL_GetTicks() - (50 + 15 * (max_XVel - XVel)) >= iTimePassed && XVel != 0)
		{
			--XVel;
			iTimePassed = SDL_GetTicks();
		}

		// ¹æÇâÀÌ ¹Ù²¸¾ß ÇÏ°í, ¼Óµµ°¡ ÃæºÐÈ÷ ÁÙ¾îµé¾úÀ» ¶§
		if (bdirection_changed && XVel <= 1)
		{
			// ¹æÇâÀÌ ¹Ù²¼´Ù´Â °ÍÀ» falseÇØÁÖ°í, ¹Ý´ë¹æÇâÀ¸·Î ¿òÁ÷ÀÌ°Ô²û ÇÑ´Ù.
			bdirection_changed = false;
			bLeft_Right = !bLeft_Right;
		}
	}

	if (eCharacterState != Characterenum::Dead)
	{
		// ¼Óµµ°¡ 0º¸´Ù Å¬ ¶§ 
		if (XVel > 0)
			// ¹æÇâ¿¡ µû¸¥ ÁÂÇ¥ ¾øµ¥ÀÌÆ®
			if (bLeft_Right)
				UpdateXPos(XVel);
			else
				UpdateXPos(-XVel);
		else
			UpdateXPos(0);
	}

	// Character Animation
	if (eCharacterState != Characterenum::Dead)
	{
		if (eHitState != Hitenum::Hitting)
		{
			if (eCharacterState == Characterenum::Hitted)
				hitedAnimation();
			else
			{
				if (eJumpState == Jumpenum::Jump_Default && bMove)
					moveAnimation();
				else if (eJumpState == Jumpenum::Jumping)
					jumpAnimation();
				else if (eJumpState == Jumpenum::Falling)
					fallAnimation();
				else if (!bMove)
					setCharacterimgnumb(0);
			}
		}
		else if (eHitState == Hitenum::Hitting)
		{
			hitAnimation();
		}
	}
	else if (eCharacterState == Characterenum::Dead)
		dieAnimation();
}

// yÃà °ü¸®
void Player::playerPhysics()
{
	// Á×Áö¾Ê¾Ò´Ù¸é
	if (eCharacterState != Characterenum::Dead)
	{
		if (eJumpState == Jumpenum::Jumping)
		{
			YAcc = (currentJumpDistance / jumpDistance > 0.5f ? 0.972f : 0.986f);
			// While jumping, gravity pull the character into the ground.
			// So That's the reason why I subtract velocity with the acceleration
			YVel -= YAcc * betweenFrametime;

			// ¼Óµµ¿¡ µû¸¥ YÁÂÇ¥ ¾÷µ¥ÀÌÆ®
			UpdateYPos(-(YVel));
			currentJumpDistance += YVel;  // YÁÂÇ¥ ÀÌµ¿ÇßÀ¸´Ï Á¡ÇÁ ÀÌµ¿°Å¸® °»½Å

			// »ç¿ëÀÚ°¡ Alt¿¡¼­ ¹öÆ°À» ¶¼°í, Á¡ÇÁ°Å¸®°¡ ÀÏÁ¤ ÀÌ»óÀÌ¸é
			if ((!SInfo::KeySpace) && currentJumpDistance > 50)
			{
				jumpDistance = 50;
			}

			// Á¡ÇÁ °Å¸®¸¸Å­ Á¡ÇÁÇß´Ù¸é->falling
			if (currentJumpDistance >= jumpDistance)
			{
				eJumpState = Jumpenum::Falling;
			}

		}
		else if (eJumpState == Jumpenum::Falling)
		{
			YAcc = 1.986f;
			YVel += YAcc * betweenFrametime;

			UpdateYPos(YVel);
			currentJumpDistance -= YVel;

			if (currentJumpDistance <= 0)
			{
				eJumpState = Jumpenum::Jump_Default;
				resetJump();
			}
		}
		// Á¡ÇÁÇÏ°í ÀÖÁö ¾ÊÀº ±âº» »óÅÂ + °øÁß¿¡ ÀÖÀ» ¶§¿¡´Â °è¼Ó ¶³¾îÁö°Ô²û ÇÔ
		else if (eJumpState == Jumpenum::Jump_Default)
		{
			int PlatformType = SCore::getMap()->getBottomCollidedPlatformType(&rCharacterCollider[cursorCollider]);

			// Solid
			if (PlatformType == 1)
			{
				bPlayerinAir = false;
				resetJump();
			}
			// Slope
			else if (PlatformType == 2)
			{
				bPlayerinAir = false;
				// Ä³¸¯ÅÍ°¡ SlopeÀ§¿¡ ÀÖÀ» ¶§, YPos¸¦ ¾÷µ¥ÀÌÆ® ½ÃÄÑÁÖ´Â ÀÌÀ¯´Â
				// Slope¿¡ ÀÖ´Â Ä³¸¯ÅÍÀÇ À§Ä¡¸¦ º¯°æÇØÁà¾ßÇÏ±â ¶§¹®ÀÌ´Ù.
				// ±×¸®°í ÀÌ ¶§´Â °¡¼Óµµ¸¦ Àû¿ëÇÏÁö ¾Ê¾Æ¾ß, Physics¿¡ ¹®Á¦°¡¾ø¾îÁø´Ù.
				// °è¼Ó °¡¼Óµµ¸¦ Àû¿ëÇÑ´Ù¸é Slope¿¡¼­ ´Ù¸¥ Á¾·ùÀÇ tile·Î ³»·Á°¡°ÔµÇ¾î 
				// ¹ØÀ¸·Î Á¡ÇÁÇÏ°Ô µÇ¸é °©ÀÚ±â ºü¸¥ ¼Óµµ·Î ¶³¾îÁö°Ô µÈ´Ù.
				UpdateYPos(startJumpSpeed); 
			}
			// Background or not collided
			else
			{
				bPlayerinAir = true;
				YAcc = 1.986f;
				YVel += YAcc * betweenFrametime;
				UpdateYPos(YVel);
			}
		}
	}
	// °øÁß¿¡¼­ Á×¾ú´Ù¸é
	else if (eCharacterState == Characterenum::Dead)
	{
		int row, speed = 1;
		if (!SCore::getMap()->YCollisionMapObject(&row, &speed, &rCharacterCollider[cursorCollider]))
			UpdateYPos(startJumpSpeed);
		else {}
	}
}

void Player::UpdateXPos(int speed)
{
	XPos += speed;
	rCharacterCollider[cursorCollider].x += speed;

	if(eCharacterState != Characterenum::Hitted)
	{
		if (SCore::getMap()->CollisionMonster(&rCharacterCollider[cursorCollider]))
		{
			if (bLeft_Right)
			{
				XPos -= 1 * 10;
				rCharacterCollider[cursorCollider].x -= 1 * 10;
			}
			else
			{
				XPos -= -1 * 10;
				rCharacterCollider[cursorCollider].x -= -1 * 10;
			}

			HPdown();
		}
	}

	if ((rCharacterCollider[cursorCollider].x < 0))
	{
		XPos = 0 - (rCharacterCollider[cursorCollider].x - XPos);
		rCharacterCollider[cursorCollider].x = 0;
	}
	else if ((rCharacterCollider[cursorCollider].x + rCharacterCollider[cursorCollider].w > SInfo::LEVEL_WIDTH))
	{
		XPos = XPos - (rCharacterCollider[cursorCollider].x + rCharacterCollider[cursorCollider].w - SInfo::LEVEL_WIDTH);
		rCharacterCollider[cursorCollider].x = SInfo::LEVEL_WIDTH - rCharacterCollider[cursorCollider].w;
	}
	
	int col;
	if (SCore::getMap()->XCollisionMapObject(&col, &rCharacterCollider[cursorCollider]))
	{
		int Xpenetration = SCore::getMap()->getXPenetrationDistance(&col, &rCharacterCollider[cursorCollider]);
		rCharacterCollider[cursorCollider].x -= Xpenetration;
		XPos -= Xpenetration;
	}

	HP_Rect.x = MP_Rect.x = XPos + Character_Width / 4;
	HP_Cut.x = HP_Rect.x + HP_Rect.w - HP_Cut.w;
}

void Player::UpdateYPos(int speed)
{
	YPos += speed;
	rCharacterCollider[cursorCollider].y += speed;

	if ((rCharacterCollider[cursorCollider].y < 0))
	{
		YPos = 0 - (rCharacterCollider[cursorCollider].y - YPos);
		rCharacterCollider[cursorCollider].y = 0;
	}
	else if ((rCharacterCollider[cursorCollider].y + rCharacterCollider[cursorCollider].h > SInfo::LEVEL_WIDTH))
	{
		YPos = YPos - (rCharacterCollider[cursorCollider].y + rCharacterCollider[cursorCollider].h - SInfo::LEVEL_WIDTH);
		rCharacterCollider[cursorCollider].y = SInfo::LEVEL_WIDTH - rCharacterCollider[cursorCollider].h;
	}

	int row, col;  // the variables for fast Y axis Collision and Slope Collision
	if (SCore::getMap()->YCollisionMapObject(&row, &speed, &rCharacterCollider[cursorCollider]))
	{
		int YPenetration = SCore::getMap()->getYPenetrationDistance(&row, &rCharacterCollider[cursorCollider]);
		rCharacterCollider[cursorCollider].y -= YPenetration;
		YPos -= YPenetration;

		bPlayerinAir = false;
		resetJump();
	}
	else
		bPlayerinAir = true;

	if (SCore::getMap()->isSlopeTile(&row, &col, &rCharacterCollider[cursorCollider]) >= 0)
	{
		// the variable for checking if the character is above the real slope while in the slope tile.
		slope_position = SCore::getMap()->getSlopePosition(&row, &col, &rCharacterCollider[cursorCollider]);

		// if the character is under the real slope, allocate the slope position into YPos
		if (rCharacterCollider[cursorCollider].y >= slope_position)
		{
			YPos = slope_position - (rCharacterCollider[cursorCollider].y - YPos);
			rCharacterCollider[cursorCollider].y = slope_position;
		}

		bPlayerinAir = false;
	}

	HP_Rect.y = YPos - 30;
	HP_Cut.y = YPos - 30;
	MP_Rect.y = YPos - 15;
}

void Player::spawnSpear(const int mouseX, const int mouseY)
{
	isSpearDone = false;

	// Spear Rect Setting
	if (bLeft_Right) // right
		spearRect.x = rCharacterCollider[Character_Collider::DEFAULT_MOVE_COLLIDER].x + rCharacterCollider[Character_Collider::DEFAULT_MOVE_COLLIDER].w;
	else
		spearRect.x = rCharacterCollider[Character_Collider::DEFAULT_MOVE_COLLIDER].x;
	spearRect.y = rCharacterCollider[Character_Collider::DEFAULT_MOVE_COLLIDER].y;
	
	// SCREEN TO WORLD POSITION Translation
	int CameraX = XPos + (Character_Width - SInfo::SCREEN_WIDTH) / 2;
	int CameraY = YPos + (Character_Height - SInfo::SCREEN_HEIGHT) / 2;
	if (CameraX < 0) 	CameraX = 0;
	if (CameraY < 0) 	CameraY = 0;
	if (CameraX > SInfo::LEVEL_WIDTH - SInfo::SCREEN_WIDTH)
		CameraX = SInfo::LEVEL_WIDTH - SInfo::SCREEN_WIDTH;
	if (CameraY > SInfo::LEVEL_HEIGHT - SInfo::SCREEN_HEIGHT)
		CameraY = SInfo::LEVEL_HEIGHT - SInfo::SCREEN_HEIGHT;
	int differenceX = (XPos - CameraX + 67) - mouseX; // Characer Screen Space Position + MOvE COLLIDER
	if (bLeft_Right) 
		differenceX = (XPos - CameraX + 75 + 120) - mouseX; // Default move collider( x + w ) 
	int differenceY = (YPos - CameraY + 62) - mouseY;
	int mouseWorldPositionX = spearRect.x - differenceX;
	int mouseWorldPositionY = spearRect.y - differenceY;
	// SCREEN TO WORLD POSITION Translation

	if (mouseWorldPositionX == spearRect.x || mouseWorldPositionY == spearRect.y)
		axis = 0;
	else
		axis = (float)(mouseWorldPositionY - spearRect.y) / (mouseWorldPositionX - spearRect.x);


	/* ¿ø°Å¸® °ø°Ý Á¦¾à »çÇ×*/
	// 1. »ç¿ëÀÚ°¡ º¸´Â ¹æÇâÀÇ ¹Ý´ëÂÊÀ¸·Î Å¬¸¯Çß´Ù¸é Á÷¼±À¸·Î ³ª°¡°Ô²û ¸¸µë
	if (bLeft_Right)
	{
		if (spearRect.x > mouseWorldPositionX)
				axis = 0;
	}
	else
	{
		if (spearRect.x < mouseWorldPositionX)
				axis = 0;
	}
	// 2. Ä³¸¯ÅÍ move colliderÀÇ xÁÂÇ¥ »çÀÌ¿¡ mouse¸¦ Å¬¸¯Çß´Ù¸é Á÷¼±À¸·Î ³ª°¡°Ô²û ¸¸µë
	// ¿Ö³ÄÇÏ¸é »çÀÌ¿¡ Å¬¸¯ÇÏ¸é ±â¿ï±â°¡ ¸Å¿ìÄ¿¼­, ¸Å¿ì ºü¸£±â ¶§¹®¿¡ ±×·± spear ¿òÁ÷ÀÓÀ» ¸¸µéÁö ¾Ê±â À§ÇØ¼­
	if ((mouseWorldPositionX >= rCharacterCollider[Character_Collider::DEFAULT_MOVE_COLLIDER].x &&
		mouseWorldPositionX <= rCharacterCollider[Character_Collider::DEFAULT_MOVE_COLLIDER].x 
		+ rCharacterCollider[Character_Collider::DEFAULT_MOVE_COLLIDER].w))
		axis = 0;


	if(!bLeft_Right) // ¿ÞÂÊ ÀÌ¸é
		axis *= -1; // ÄÄÇ»ÅÍ ÁÂÇ¥°è¿¡ ¸ÂÃß±â À§ÇØ
	spearDirection = bLeft_Right;
	spear_repetition = 0;
}

void Player::updateSpear()
{
	spear_repetition++;

	// SpearÀÇ ¿òÁ÷ÀÓ ¼Óµµ Á¶Àý
	int moveDistance;
	if (abs(axis) <= 1) // ±â¿ï±â°¡ 1º¸´Ù ÀÛÀ¸¸é yÃàÀº ¾ó¸¶ ¾È¿òÁ÷ÀÌ¸é µÇ±â ¶§¹®¿¡ xÃà Áõ°¡·®À» 10À¸·Î
		moveDistance = 10;
	else
	{
		moveDistance = 18 / abs(axis); // ±â¿ï±â°¡ 1º¸´Ù Å©¸é, yÃà ¿òÁ÷ÀÌ´Â ¼Óµµ¸¦ ¸ÅÇÁ·¹ÀÓ´ç 18·Î ¸ÂÃçÁÜ.

		// À§ÀÇ ³ª´« °á°ú·Î movedistance°¡ 0.xx°¡ µÇ¾î truncate·Î 0ÀÌ µÇ´Âµ¥, axis°¡ 18º¸´Ù Å©±â ¶§¹®¿¡, moveDistance¸¦ 1·Î ¸ÂÃß¾î xÃàÀº Á¶±Ý¾¿¸¸ ¿òÁ÷ÀÌµµ·Ï
		if (moveDistance == 0) 
			moveDistance = 1;
	}
	

	/* X Position Update */
	if (spearDirection) // right
		spearRect.x += moveDistance;
	else
		spearRect.x -= moveDistance;
	if (SCore::getMap()->AttackCollisionMonster(&spearRect))
	{
		isSpearDone = true;
	}

	if (spearRect.x < 0 || spearRect.x + spearRect.w > SInfo::LEVEL_WIDTH)
		isSpearDone = true;
	int row, col;
	if (SCore::getMap()->XCollisionMapObject(&col, &spearRect))
		isSpearDone = true;

	/* Y Position Update */
	spearRect.y += axis * moveDistance;
	if (spearRect.y < 0 || spearRect.y + spearRect.h > SInfo::LEVEL_HEIGHT)
		isSpearDone = true;
	
	int speed = axis;
	if (SCore::getMap()->YCollisionMapObject(&col, &speed, &spearRect))
		isSpearDone = true;
	if (SCore::getMap()->isSlopeTile(&row, &col, &spearRect) >= 0)
	{
		slope_position = SCore::getMap()->getSlopePosition(&row, &col, &spearRect);
		if (spearRect.y >= slope_position)
			isSpearDone = true;
	}

	// °è¼Ó ³¯¾Æ°¡Áö ¾Ê°Ô ÇÏ±â À§ÇØ
	if (spear_repetition > 50)
		isSpearDone = true;
}

void Player::hit(const int mouseX, const int mouseY)
{
	if (eHitState == Hitenum::Hit_Default && isSpearDone)
		eHitState = Hitenum::Hitting;

	if (eCharacterWeapon == Character_Weapon::WEAPON_SPEAR && isSpearDone)
		spawnSpear(mouseX, mouseY);
}

void Player::Hit_Collision()
{
	// °ø°ÝÇØ¼­, Ãæµ¹ÀÏ¾î³µÀ» ¶§
	// ÇöÀç ÀÌ¹ÌÁö·Î ¾ÈµÇ°í, ±âº»ÀÌ¹ÌÁö¿Í, È÷Æ® ÀÌ¹ÌÁö Å©±â°¡ ´Ù¸¦ ¶§ È®ÀÎ °¡´É
	SCore::getMap()->AttackCollisionMonster(&rCharacterCollider[HIT_ATTACK_COLLIDER]);
}

void Player::Jump()
{
	startJump();
}


void Player::startJump()
{
	if (!bPlayerinAir)
	{
		if (eJumpState == Jumpenum::Jump_Default)
		{
			YVel = startJumpSpeed;
			currentJumpDistance = 0;
			jumpDistance = 120.f;
			eJumpState = Jumpenum::Jumping;
		}
	}
}

void Player::resetJump()
{
	currentJumpDistance = 0;
	YVel = 5;
	eJumpState = Jumpenum::Jump_Default;
}

void Player::startMove()
{
	bMove = true;
	XVel = 1;
}

void Player::stopMove()
{
	--XVel;
	bMove = false;
}

void Player::startRun()
{
	max_XVel += 2;
}

void Player::stopRun()
{
	max_XVel -= 2;
}

void Player::setMoveDirection_X(bool left_right)
{
	this->bLeft_Right = left_right;
}

void Player::setDirectionChanged(bool changed)
{
	this->bdirection_changed = changed;
}

void Player::changeWeapon()
{
	eCharacterWeapon = Character_Weapon((int)eCharacterWeapon + 1);
	
	if (eCharacterWeapon == Character_Weapon::WEAPON_COUNT)
		eCharacterWeapon = Character_Weapon::WEAPON_PUNCH;
}

void Player::Draw(SDL_Renderer* rR, SDL_Rect* Camera)
{
	if (eCharacterState == Characterenum::Hitted)
	{
		SDL_Rect temp = HP_Rect, temp2 = HP_Cut, temp3 = MP_Rect;
		temp.x -= Camera->x; temp.y -= Camera->y;
		temp2.x -= Camera->x; temp2.y -= Camera->y;
		temp3.x -= Camera->x; temp3.y -= Camera->y;

		SDL_SetRenderDrawColor(rR, 188, 0, 17, 255);
		SDL_RenderFillRect(rR, &temp);
		SDL_SetRenderDrawColor(rR, 0, 0, 0, 255);
		SDL_RenderFillRect(rR, &temp2);
		SDL_SetRenderDrawColor(rR, 0, 17, 188, 255);
		SDL_RenderFillRect(rR, &temp3);
	}

	// Spear Draw
	if (eCharacterWeapon == Character_Weapon::WEAPON_SPEAR)
	{
		SDL_Rect CharacterSpearRect;
		if (bLeft_Right) // Right
			CharacterSpearRect.x = XPos + 174;
		else
			CharacterSpearRect.x = XPos + 74;
		CharacterSpearRect.y = YPos + 30;

		WeaponIMG[0].Draw(rR, CharacterSpearRect.x - Camera->x, CharacterSpearRect.y - Camera->y, bLeft_Right);

		if (!isSpearDone)
			WeaponIMG[1].Draw(rR, spearRect.x - Camera->x, spearRect.y - Camera->y, spearDirection);
	}

	if (eCharacterState == Characterenum::Dead)
		CharacterIMG[imgnumb].Draw(rR, (int)XPos - Camera->x, (int)YPos - Camera->y, false);
	else
		CharacterIMG[imgnumb].Draw(rR, (int)XPos - Camera->x, (int)YPos - Camera->y, bLeft_Right);

	// DEBUG START
	/*
	SDL_SetRenderDrawColor(rR, 255, 0, 0, 0xFF);
	SDL_Rect colliR{ XPos - Camera->x, YPos - Camera->y, Character_Width, Character_Height };
	SDL_RenderDrawRect(rR, &colliR);

	colliR = rCharacterCollider[cursorCollider];
	colliR.x -= Camera->x; colliR.y -= Camera->y;
	SDL_SetRenderDrawColor(rR, 0, 153, 255, 255);
	SDL_RenderDrawRect(rR, &colliR);

	if (eHitState == Hitenum::Hitting)
	{
		colliR = rCharacterCollider[HIT_ATTACK_COLLIDER];
		colliR.x -= Camera->x; colliR.y -= Camera->y;
		SDL_SetRenderDrawColor(rR, 255, 38, 168, 255);
		SDL_RenderDrawRect(rR, &colliR);
	}
	*/
	// DEBUG END
}

void Player::HPdown()
{
	eCharacterState = Characterenum::Hitted;
	if (SDL_GetTicks() - iHPdownTime > 1000)
	{
		iHPdownTime = SDL_GetTicks();
		if (HP > 0)
		{
			HP -= damage;
			++Cut_number;

			// HP_CUT BOX 조정
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

			HP_Cut.x = HP_Rect.x + HP_Rect.w - HP_Cut.w;   // HP_Cut.x + HP_Cut.w = HP_Rect.x + HP_Rect.w (끝이 동일)
		}
	}
	if (HP <= 0)
	{
		HP = 0;
		HP_Cut.w = HP_Rect.w;
	}
	if (HP == 0)
		eCharacterState = Characterenum::Dead;
}

void Player::resetPlayer(SDL_Renderer* rR)
{
	Cut_number = 0;
	
	bMove = false;
	bLeft_Right = false;
	bdirection_changed = false;

	eHitState = Hitenum::Hit_Default;

	XPos = firstXPos;
	YPos = firstYPos;

	XVel = YVel = 0;
	resetJump();

	eJumpState = Jumpenum::Jump_Default;
	jumpDistance = 120.f;

	eCharacterState = Characterenum::Character_Default;
	bhitted_Animation = false;
	iMoveAnimationTime = iDieAnimationTime = 0;

	imgnumb = 0;

	HP = 200;
	MP = 200;

	HP_Rect = { firstXPos + Character_Width / 4, firstYPos - 30, 120, 15 };
	HP_Cut = { firstXPos + Character_Width / 4 + 120, firstYPos - 30, 0, 15 };
	MP_Rect = { firstXPos + Character_Width / 4, firstYPos - 15, 120, 15 };
	MP_Cut = { firstXPos + Character_Width / 4 + 120, firstYPos - 15, 0, 15 };
}

void Player::moveAnimation()
{
	if (SDL_GetTicks() - 40 - 3 * XVel > iMoveAnimationTime)
	{
		iMoveAnimationTime = SDL_GetTicks();

		if (imgnumb >= 13)
			setCharacterimgnumb(1); // run initial image
		else
			++imgnumb;
	}

}

void Player::jumpAnimation()
{
	if (SDL_GetTicks() - 25 * XVel > iMoveAnimationTime)
	{
		iMoveAnimationTime = SDL_GetTicks();

		if (imgnumb >= 25 || imgnumb < 14)
			setCharacterimgnumb(14); // jump initial image
		else
			++imgnumb;
	}
}

void Player::fallAnimation()
{
	if (SDL_GetTicks() - 25 * XVel > iMoveAnimationTime)
	{
		iMoveAnimationTime = SDL_GetTicks();

		if (imgnumb >= 37 || imgnumb < 26)
			setCharacterimgnumb(26); // fall initial image
		else
			++imgnumb;
	}
}

void Player::hitAnimation()
{
	// °ø°ÝÀÌ ³¡³µÀ¸¸é Hit_Default·Î
	if (SDL_GetTicks() - 20 * 2 > iMoveAnimationTime)
	{
		if (eCharacterWeapon == Character_Weapon::WEAPON_PUNCH)
		{
			iMoveAnimationTime = SDL_GetTicks();

			if (imgnumb == 45)
			{
				Hit_Collision();
				SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cattackmouth);
				SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cpunch);
				SInfo::getMusic()->increaseAttackindex();
			}

			if (imgnumb == 47)
				eHitState = Hitenum::Hit_Default;

			if (imgnumb >= 47 || imgnumb < 38)
				setCharacterimgnumb(38); // hit initial image
			else
				++imgnumb;
		}
		else if (eCharacterWeapon == Character_Weapon::WEAPON_SPEAR)
		{
			iMoveAnimationTime = SDL_GetTicks();

			if (imgnumb == 45)
			{
				SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cattackmouth);
				SInfo::getMusic()->increaseAttackindex();
			}

			if (imgnumb == 47)
				eHitState = Hitenum::Hit_Default;

			if (imgnumb >= 47 || imgnumb < 38)
				setCharacterimgnumb(38); // hit initial image
			else
				++imgnumb;
		}
	}

}

void Player::hitedAnimation()
{
	if (!bNow_hitted)
		ifirstHitTime = SDL_GetTicks();

	// Hitted µÈ »óÅÂ¿¡¼­ °ø°ÝÇßÀ» ¶§, Hitted AnimationÀ¸·Î ´Ù½ÃµÇµ¹¾Æ ¿Àµµ·Ï
	if (eCharacterState == Characterenum::Hitted)
		setCharacterimgnumb(48); // hitted initial image

	if (!bhitted_Animation)
	{
		bNow_hitted = true;
		iMoveAnimationTime = SDL_GetTicks();
		bhitted_Animation = true;
	}
}

void Player::dieAnimation()
{
	if (!bDie_Animation)
	{
		SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cdead);
		iDieAnimationTime = SDL_GetTicks();
		bDie_Animation = true;
	}
	if (SDL_GetTicks() - 20 * 1 > iMoveAnimationTime)
	{
		iMoveAnimationTime = SDL_GetTicks();

		if (imgnumb < 50 || imgnumb >= 60)
			setCharacterimgnumb(50);
		++imgnumb;
	}

	// 3ÃÊ°£ die ¾Ö´Ï¸ÞÀÌ¼Ç À¯Áö ÈÄ Pause »óÅÂ·Î º¯°æ
	if (SDL_GetTicks() - iDieAnimationTime >= 3000)
	{
		SInfo::getMM()->setStateID(SInfo::getMM()->eEnding);
		SInfo::getMM()->getEndingMenu()->setGameSuccess(false, 0);
		SInfo::getMusic()->PlayMusic(SInfo::getMusic()->mDead);
	}
}

void Player::calcSCore(int time)
{
	if (!bCalcScore)
		if (time > 0)
			if (SDL_GetTicks() - iFrameTime > 30)
			{
				iFrameTime = SDL_GetTicks();
				addScore(10);		// ³²Àº ½Ã°£¸¸Å­ Á¡¼ö°¡ Áõ°¡ÇÏ´Â ¸ð½ÀÀ» ½Ã°¢ÀûÀ¸·Î º¸¿©ÁÖ±â À§ÇØ
				SCore::getMap()->set_iMapTime2(--time); // 0.5ÃÊ¸¶´Ù ³²Àº½Ã°£ 1¿ï °¨¼Ò, Á¡¼ö 10À» Áõ°¡

				if (time <= 0)
				{
					SCore::getMap()->set_iMapTime2(0);
					bCalcScore = true;
				}
			}
}

void Player::addScore(int add_score)
{
	score += add_score;
}

void Player::resetScore()
{
	score = 0;
}

void Player::addHP(int hp)
{
	this->HP += hp;
	if (this->HP >= max_HP)
		HP = max_HP;

	HP_Cut.w = HP_Rect.w - ( HP * HP_Rect.w / max_HP );
	HP_Cut.x = HP_Rect.x + HP_Rect.w - HP_Cut.w;
}


CIMG* Player::getPlayerImage() { return  CharacterIMG; }
bool Player::getMove() { return bMove; }
float Player::getXPos() { return rCharacterCollider[DEFAULT_MOVE_COLLIDER].x; }
float Player::getYPos() { return rCharacterCollider[DEFAULT_MOVE_COLLIDER].y; }
int Player::getWidth() { return rCharacterCollider[DEFAULT_MOVE_COLLIDER].w; }
int Player::getHeight() { return rCharacterCollider[DEFAULT_MOVE_COLLIDER].h; }
SDL_Rect Player::getRect() { return rCharacterCollider[DEFAULT_MOVE_COLLIDER]; }
int Player::getHP() { return HP; }
int Player::getMaxHP() { return max_HP; }
int Player::getMP() { return MP; }
int Player::getHittedNumber() { return Cut_number; }
void Player::setHittedNumber(int num) { Cut_number = num; }
bool Player::getRotate() { return (bLeft_Right ? true : false); }

int Player::getJumpState() { return (int)eJumpState; }
int Player::getHitState() { return (int)eHitState; }
int Player::getCharacterState() { return (int)eCharacterState; }
int Player::getScore() { return this->score; }

void Player::setCharacterimgnumb(int numb) { imgnumb = numb; }
bool Player::getbCalcScore() { return bCalcScore; }
