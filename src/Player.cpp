#include "Player.h"
#include "StaticInfo.h"
#include "Core.h"

#define abs(x) (x < 0 : -x : x)

Player::Player(SDL_Renderer* rR, int x, int y)
{
	bMove = false;
	bLeft_Right = false;
	eHitState = Hitenum::Hit_Default;
	XPos = x;
	XVel = 0;
	max_XVel = 6;

	YPos = y;
	YVel = 0;

	ground = y;
	
	eJumpState = Jumpenum::Jump_Default;
	startJumpSpeed = 6.f;
	jumpDistance = 120.f;
	
	imgnumb = 0;
	Character.push_back(new CIMG("character/character", rR));

	// Run
	Character.push_back(new CIMG("character/character_run1", rR)); // number 1
	Character.push_back(new CIMG("character/character_run2", rR));
	Character.push_back(new CIMG("character/character_run3", rR));
	Character.push_back(new CIMG("character/character_run4", rR));
	Character.push_back(new CIMG("character/character_run5", rR));
	Character.push_back(new CIMG("character/character_run6", rR));
	Character.push_back(new CIMG("character/character_run7", rR));
	Character.push_back(new CIMG("character/character_run8", rR));
	Character.push_back(new CIMG("character/character_run9", rR));
	Character.push_back(new CIMG("character/character_run10", rR));
	Character.push_back(new CIMG("character/character_run11", rR));
	Character.push_back(new CIMG("character/character_run12", rR));
	Character.push_back(new CIMG("character/character_run13", rR));

	// Jump
	Character.push_back(new CIMG("character/character_jump1", rR)); // number 14
	Character.push_back(new CIMG("character/character_jump2", rR));
	Character.push_back(new CIMG("character/character_jump3", rR));
	Character.push_back(new CIMG("character/character_jump4", rR));
	Character.push_back(new CIMG("character/character_jump5", rR));
	Character.push_back(new CIMG("character/character_jump6", rR));
	Character.push_back(new CIMG("character/character_jump7", rR));
	Character.push_back(new CIMG("character/character_jump8", rR));
	Character.push_back(new CIMG("character/character_jump9", rR));
	Character.push_back(new CIMG("character/character_jump10", rR));
	Character.push_back(new CIMG("character/character_jump11", rR));
	Character.push_back(new CIMG("character/character_jump12", rR));

	// Falling
	Character.push_back(new CIMG("character/character_fall1", rR)); // number 26
	Character.push_back(new CIMG("character/character_fall2", rR));
	Character.push_back(new CIMG("character/character_fall3", rR));
	Character.push_back(new CIMG("character/character_fall4", rR));
	Character.push_back(new CIMG("character/character_fall5", rR));
	Character.push_back(new CIMG("character/character_fall6", rR));
	Character.push_back(new CIMG("character/character_fall7", rR));
	Character.push_back(new CIMG("character/character_fall8", rR));
	Character.push_back(new CIMG("character/character_fall9", rR));
	Character.push_back(new CIMG("character/character_fall10", rR));
	Character.push_back(new CIMG("character/character_fall11", rR));
	Character.push_back(new CIMG("character/character_fall12", rR));

	// Hit
	Character.push_back(new CIMG("character/character_hit1", rR)); // number 38
	Character.push_back(new CIMG("character/character_hit2", rR));
	Character.push_back(new CIMG("character/character_hit3", rR));
	Character.push_back(new CIMG("character/character_hit4", rR));
	Character.push_back(new CIMG("character/character_hit5", rR));
	Character.push_back(new CIMG("character/character_hit6", rR));
	Character.push_back(new CIMG("character/character_hit7", rR));
	Character.push_back(new CIMG("character/character_hit8", rR));
	Character.push_back(new CIMG("character/character_hit9", rR));
	Character.push_back(new CIMG("character/character_hit10", rR));
	Character.push_back(new CIMG("character/character_hit11", rR));


}

void Player::Update()
{
	playerPhysics(); // Y축, 점프, 물리 역학을 적용하는 사용자의 속도를 조절해서 위치 조정
	movePlayer();    // X축, 이동
}

void Player::moveAnimation()
{
	if (imgnumb >= 13)
		setCharacterimgnumb(1); // run initial image
	else
		++imgnumb;

}

void Player::jumpAnimation()
{
	if (imgnumb >= 25 || imgnumb <14)
		setCharacterimgnumb(14); // jump initial image
	else
		++imgnumb;
}

void Player::fallAnimation()
{
	if (imgnumb >= 37 || imgnumb < 26)
		setCharacterimgnumb(26); // fall initial image
	else
		++imgnumb;
}

void Player::hitAnimation()
{
	// 공격이 끝났으면 Hit_Default로
	if (imgnumb == 48)
		eHitState = Hitenum::Hit_Default;

	if (imgnumb >= 48 || imgnumb < 38)
		setCharacterimgnumb(38); // hit initial image
	else
		++imgnumb;

}

void Player::hit()
{
	eHitState = Hitting;
}

void Player::Jump()
{
	startJump();
}

void Player::startJump()
{
	if (eJumpState == Jumpenum::Jump_Default)
	{
		YVel = startJumpSpeed;
		currentJumpDistance = 0;
		jumpDistance = 120.f;
		eJumpState = Jumpenum::Jumping;
	}
}

void Player::resetJump()
{
	currentJumpDistance = 0;
	YVel = 0;

}

void Player::playerPhysics()
{
	printf("ypos: %f\n", YPos);
	// 사용자가 어디 위로 올라갔을 때
	if (eJumpState == Jumpenum::Jump_Default && ground != YPos && !SCore::getMap()->CollisionMonster())
	{
		currentJumpDistance = ground - YPos;
		YVel = startJumpSpeed;
		eJumpState = Jumpenum::Falling;
	}

	if (eJumpState == Jumpenum::Jumping)
	{
		// 속도에 따른 Y좌표 업데이트
		UpdateYPos(-YVel);
		currentJumpDistance += YVel;  // Y좌표 이동했으니 점프 이동거리 갱신


		// 사용자가 Alt에서 버튼을 떼고, 점프거리가 일정 이상이면
		if ( (!SInfo::KeyAlt) && currentJumpDistance > 50)
		{
			jumpDistance = 50;
		}

		// 점프 거리만큼 점프했다면->falling
		if (currentJumpDistance >= jumpDistance)
		{
			eJumpState = Jumpenum::Falling;
		}

	}
	else if (eJumpState == Jumpenum::Falling)
	{
		UpdateYPos(YVel);
		currentJumpDistance -= YVel;

		if (currentJumpDistance <= 0)
		{
			eJumpState = Jumpenum::Jump_Default;
			resetJump();
		}
	}
}

void Player::startMove()
{
	bMove = true;
	XVel = 1;
}

void Player::setMoveDirection_X(bool left_right)
{
	this->bLeft_Right = left_right;
}


void Player::movePlayer()
{
	// 공격하지 않는다면
	if (eHitState == Hitenum::Hit_Default)
	{
		if (bMove)
		{
			// 오른쪽 방향으로 갈 때
			if (bLeft_Right)
				++XVel;
			// 왼쪽 방향으로 갈 때
			else if (!bLeft_Right)
				--XVel;

			if (XVel > 0 && XVel >= max_XVel)
				--XVel;
			else if (XVel < 0 && -XVel >= max_XVel)
				++XVel;
				
			UpdateXPos(XVel);
		}

		// Sprite Animation
		if (eJumpState == Jumpenum::Jump_Default && bMove)
			moveAnimation();
		else if (eJumpState == Jumping)
			jumpAnimation();
		else if (eJumpState == Falling)
			fallAnimation();
		else if (!bMove)
			setCharacterimgnumb(0);
	}
	else if(eHitState == Hitting)
		hitAnimation();

}

void Player::UpdateXPos(int speed)
{
	XPos += speed;

	if ((XPos < 0) || (XPos + Character[imgnumb]->getRect().w > SInfo::GAME_WIDTH) || SCore::getMap()->CollisionMonster())
		XPos -= speed;
}

void Player::UpdateYPos(int speed)
{
	YPos += speed;

	if ((YPos < 0) || (YPos + Character[imgnumb]->getRect().h > SInfo::GAME_HEIGHT) || SCore::getMap()->CollisionMonster())
		YPos -= speed;

}

void Player::stopMove()
{
	bMove = false;
}


void Player::Draw(SDL_Renderer* rR, int x, int y, bool rotate)
{
	Character[imgnumb]->Draw(rR, x, y , rotate);
}

std::vector<CIMG*> Player::getPlayer() { return  Character; }
bool Player::getMove() { return bMove; }
int Player::getXPos() { return XPos; }
int Player::getYPos() { return YPos; }
int Player::getWidth() { return Character[imgnumb]->getRect().w; }
int Player::getHeight() { return Character[imgnumb]->getRect().h; }
bool Player::getRotate() { return (bLeft_Right ? true : false); }

void Player::setCharacterimgnumb(int numb)
{
	imgnumb = numb;
}