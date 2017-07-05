#include "Player.h"
#include "StaticInfo.h"

Player::Player(SDL_Renderer* rR, int x, int y)
{
	bMove = false;
	bLeft_Right = false;
	XPos = x;
	XVel = 0;

	YPos = y;
	YVel = 0;
	imgnumb = 0;
	eJumpState = Jumpenum::None;
	startJumpSpeed = 6.f;
	jumpDistance = 120.f;
	Character.push_back(new CIMG("character", rR));
}

void Player::Update()
{
	playerPhysics(); // Y��, ����, ���� ������ �����ϴ� ������� �ӵ��� �����ؼ� ��ġ ����
	movePlayer();    // X��, �̵�
}

void Player::Jump()
{
	startJump();
}

void Player::startJump()
{
	if (eJumpState == Jumpenum::None)
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
	if (eJumpState == Jumpenum::Jumping)
	{
		// �ӵ��� ���� Y��ǥ ������Ʈ
		UpdateYPos(-YVel);
		currentJumpDistance += YVel;  // Y��ǥ �̵������� ���� �̵��Ÿ� ����


		// ����ڰ� Alt���� ��ư�� ����, �����Ÿ��� ���� �̻��̸�
		if ( (!SInfo::KeyAlt) && currentJumpDistance > 50)
		{
			jumpDistance = 50;
		}

		// ���� �Ÿ���ŭ �����ߴٸ�->falling
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
			eJumpState = Jumpenum::None;
			resetJump();
		}
	}

	printf("yvel: %f ypos : %f cujumpd: %f\n", YVel, YPos, currentJumpDistance);
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
	if (bMove)
	{
		// ������ �������� �� ��
		if (bLeft_Right)
			++XVel;
		// ���� �������� �� ��
		else
			--XVel;

		UpdateXPos(XVel);
	}
}

void Player::UpdateXPos(int speed)
{
	XPos += speed;

	if ((XPos < 0) || (XPos + Character[imgnumb]->getRect().w > SInfo::GAME_WIDTH))
		XPos -= speed;
}

void Player::UpdateYPos(int speed)
{
	YPos += speed;

	if ((YPos < 0) || (YPos + Character[imgnumb]->getRect().h > SInfo::GAME_HEIGHT))
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
bool Player::getRotate() { return (bLeft_Right ? true : false); }
