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

	float YPos;
	float YVel;

	//** Move **//

	bool bMove;
	bool bLeft_Right; // Left == false, Right == TRUE

	//** Move **//

	//** Jump **//

	enum Jumpenum 
	{
		Jumping,   // 점프가 시작되어 공중으로 뜨고있음.
		Falling,   // Max 위치까지 올라가고 이제 떨어지고 있는 중임
		None       // 점프하고 있지 않음
	};
	Jumpenum eJumpState;
	float startJumpSpeed;
	float currentJumpDistance;
	float jumpDistance;

	//** Jump **//

	void movePlayer();

public:

	Player(SDL_Renderer* rR, int x, int y);
	
	void Update();

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
	bool getRotate();
	
};

#endif
