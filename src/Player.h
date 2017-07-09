#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "CIMG.h"

class Player
{
private:
	std::vector<CIMG*> Character;
	int imgnumb;

	float XPos;
	float XVel;
	int max_XVel;

	float YPos;
	float YVel;

	float ground;

	//** Move **//

	bool bMove;
	bool bLeft_Right; // Left == false, Right == TRUE

	//** Move **//

	//** Jump **//

	enum Jumpenum 
	{
		Jumping,   // ������ ���۵Ǿ� �������� �߰�����.
		Falling,   // Max ��ġ���� �ö󰡰� ���� �������� �ִ� ����
		Jump_Default       // �����ϰ� ���� ����
	};
	Jumpenum eJumpState;
	float startJumpSpeed;
	float currentJumpDistance;
	float jumpDistance;

	//** Jump **//

	//** Hit **//

	enum Hitenum
	{
		Hitting,	// ���� ����
		Hit_Default // �����ϰ� ���� ����
	};

	Hitenum eHitState;

	//** Hit **//

	void movePlayer();

public:

	Player(SDL_Renderer* rR, int x, int y);
	
	void Update();

	void moveAnimation();
	void jumpAnimation();
	void fallAnimation();
	void hitAnimation();

	void hit();
	void Jump();
	void startJump();
	void resetJump();
	void playerPhysics();
	
	void startMove();
	void setMoveDirection_X(bool left_right);  // Left == FALSE, Right == TRUE
	void stopMove();

	void UpdateXPos(int speed);
	void UpdateYPos(int speed);

	void Draw(SDL_Renderer* rR, int x, int y, bool rotate);
	

	/* ----- get & set ----- */
	std::vector<CIMG*> getPlayer();
	bool getMove();
	int getXPos();
	int getYPos();
	int getWidth();
	int getHeight();
	bool getRotate();

	void setCharacterimgnumb(int numb);
	
};

#endif
