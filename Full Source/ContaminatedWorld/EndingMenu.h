#ifndef __ENDING_MENU_H__
#define __ENDING_MENU_H__

#include "CIMG.h"
#include "Menu.h"
#include "AssetManager.h"

//// Rank Information
//typedef struct RankInfo
//{
//	int rankTable_size;
//	std::vector<std::string> vRank_Number;
//	std::vector<std::string> vRank_Name;
//	std::vector<std::string> vRank_Score;
//	std::vector<std::string> vRank_Thought;
//} RankInfo;


class EndingMenu : public Menu
{
private:
	bool isGameSuccess;
	unsigned int iTimePassed;

	// Success Ending Menu
	CIMG* cGameSuccess;
	CIMG* cRankSave;
	CIMG* cRankSave_over;
	RankInfo* rankTable;
	Bitmap_Text* bText;
	int text_Height;

	int NumberBoxWidth;
	int ScoreBoxWidth;
	int NameBoxWidth;
	int ThoughtBoxWidth;
	std::pair<int, int> NumberBox;
	std::pair<int, int> NameBox;
	std::pair<int, int> ScoreBox;
	std::pair<int, int> ThoughtBox;
	int RankYaxis;
	int RankTableHeight;
	bool bSaveButtonOver;
	SDL_Rect SaveButtonRect;
	SDL_Rect rankTableRect;

	int visible_Range;
	int table_cursor;
	int table_cursorLimit;

	int scrollBox_width;
	int scrollYmove_Quantity;
	int scrollBar_height;
	SDL_Rect backgroundScroll;
	SDL_Rect ScorllBar;
	bool isBarClicked;
	int pastMouseY, currentMouseY;

	bool isNewBoxDisplayed;
	bool isNameSelected;
	bool isThoughtSelected;
	bool bTextWidthExcessFlag;
	bool bTextWrongSelectionFlag;
	bool bTextNotFilledFlag;
	bool isFirstNameInput;
	bool isFirstThoughtInput;
	std::string* userNameInput;
	std::string* userThoughtInput;
	SDL_Rect NewnameBox;
	SDL_Rect NewThoughtBox;
	int userScore;
	int userNumber;

	void insertRankInfo();
	void saveRanking();
	
	void DrawRankLayout(SDL_Renderer* rR);
	void DrawRankInfo(SDL_Renderer* rR);

	// Fail Ending Menu
	CIMG* cGameFail;
	CIMG* cGotoMain;
	CIMG* cGotoMain_over;
	CIMG* cQuitIcon;
	CIMG* cQuitIcon_over;

	int menuXpos;
	int menuYpos;

	void DrawDieMenu(SDL_Renderer* rR);
	void DrawDieMenu_over1(SDL_Renderer* rR);
	void DrawDieMenu_over2(SDL_Renderer* rR);
	void resetGotoMain();
public:
	EndingMenu();
	~EndingMenu();

	void Update();
	void Draw(SDL_Renderer* rR);

	void enter();
	void click(int x, int y);

	void checkMouseInput(int x, int y);

	void setGameSuccess(bool game, int score);
	void appendUserText(char* inputText);
	void popupUserText();
};

#endif