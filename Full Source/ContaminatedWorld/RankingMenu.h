#ifndef __RANKING_MENU_H__
#define __RANKING_MENU_H__

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

class RankingMenu : public Menu
{
private:
	CIMG* cGameRanking;
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

	void DrawRankLayout(SDL_Renderer* rR);
	void DrawRankInfo(SDL_Renderer* rR);

public:
	RankingMenu();
	~RankingMenu();

	void Update();
	void Draw(SDL_Renderer* rR);

	void escape();
	void click(int x, int y);
	void checkMouseInput(int x, int y);

	void postProcessing();
};

#endif