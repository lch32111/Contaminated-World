#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "CIMG.h"

class Player
{
private:
	CIMG* CharacterIMG;
	CIMG* WeaponIMG;
	SDL_Rect spearRect;

	enum class Character_Weapon
	{
		WEAPON_PUNCH,
		WEAPON_SPEAR,
		WEAPON_COUNT
	};
	Character_Weapon eCharacterWeapon;
	
	
	bool spearDirection;
	int spear_repetition;
	float axis;
	bool isSpearDone;

	enum Character_Collider
	{
		DEFAULT_MOVE_COLLIDER,
		DIE_MOVE_COLLIDER,
		HIT_ATTACK_COLLIDER,
		CHARACTER_COLLIDER_COUNT
	};
	Character_Collider cursorCollider;
	SDL_Rect rCharacterCollider[Character_Collider::CHARACTER_COLLIDER_COUNT];

	int score;

	int imgnumb;
	int effectNumb;

	int Character_Width;
	int Character_Height;

	SDL_Rect HP_Rect;
	SDL_Rect HP_Cut;
	SDL_Rect MP_Rect;
	SDL_Rect MP_Cut;
	int HP, MP;
	int max_HP, max_MP;
	int damage;
	float Cut_Ratio;
	float Cut_Rest;
	int Cut_number;

	float XPos;
	float XVel;
	int max_XVel;

	float YPos;
	float YVel;
	float YAcc;

	int firstXPos;
	int firstYPos;
	float slope_position;

	int max_skillDistance;
	int min_skillDistance;

	//** Move **//
	bool bMove;
	bool bLeft_Right; // Left == false, Right == TRUE
	bool bdirection_changed; 
	bool bPlayerinAir;
	//** Move **//

	//** Jump **//
	enum class Jumpenum 
	{
		Jumping,   // 점프가 시작되어 공중으로 뜨고있음.
		Falling,   // Max 위치까지 올라가고 이제 떨어지고 있는 중임
		Jump_Default	// 점프하고 있지 않음
	};
	Jumpenum eJumpState;
	float startJumpSpeed;
	float currentJumpDistance;
	float jumpDistance;
	//** Jump **//

	//** Hit **//
	enum class Hitenum
	{
		Hitting,	// 공격 중임
		Hit_Default // 공격하고 있지 않음
	};
	Hitenum eHitState;
	//** Hit **//

	enum class Characterenum
	{
		Hitted,				// 공격받음
		Dead,				// 죽음
		Falling,			// 추락 중
		Character_Default   // 아무것도 하지 않음
	};
	Characterenum eCharacterState;

	bool bhitted_Animation;
	bool bDie_Animation;
	bool bNow_hitted;

	bool bCalcScore;
	unsigned int iFrameTime;

	unsigned int previousFrameTime;
	unsigned int currentFrameTime;
	unsigned int iTimePassed;
	float betweenFrametime;
	unsigned int iMoveAnimationTime;
	unsigned int iDieAnimationTime;
	unsigned int iHPdownTime;
	unsigned int ifirstHitTime;

	void movePlayer();
	void playerPhysics();
	void Hit_Collision();
	void startJump();
	void resetJump();
	
	void setCharacterimgnumb(int numb);
	void moveAnimation();
	void jumpAnimation();
	void fallAnimation();
	void hitAnimation();
	void hitedAnimation();
	void dieAnimation();
	
	void UpdateCollider();
	void UpdateXPos(int speed);
	void UpdateYPos(int speed);

	void UpdateHittedForOneS();
	void spawnSpear(const int mouseX, const int mouseY);
	void updateSpear();

public:
	Player();
	Player(CIMG* character_img, CIMG* weapon_img, int x, int y);
	~Player();
	
	void Update();
	void Draw(SDL_Renderer* rR, SDL_Rect* Camera);
	void resetPlayer(SDL_Renderer* rR);
	void addScore(int add_score);
	void resetScore();

	void HPdown();
	void hit(const int mouseX, const int mouseY);
	void Jump();
	void startMove();
	void stopMove();
	void startRun();
	void stopRun();
	void setMoveDirection_X(bool left_right);  // Left == FALSE, Right == TRUE
	void setDirectionChanged(bool changed);
	void changeWeapon();
	
	void calcSCore(int time);
	void addHP(int hp);
	
	/* ----- get & set ----- */
	CIMG* getPlayerImage();
	bool getMove();
	float getXPos();
	float getYPos();
	int getWidth();
	int getHeight();
	SDL_Rect getRect();
	int getHP();
	int getMaxHP();
	int getMP();
	int getHittedNumber();
	bool getRotate();
	int getJumpState();
	int getHitState();
	int getCharacterState();
	int getScore();
	bool getbCalcScore();
	void setHittedNumber(int num);
	
};

#endif
