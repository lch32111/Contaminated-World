#include "RankingMenu.h"
#include "Core.h"
#include <string>

RankingMenu::RankingMenu()
{
	// Game Success Variables
	cGameRanking = SCore::getAssetManager()->getRankingMenuIMG();

	rankTable = SCore::getAssetManager()->getRankInfo();
	bText = &SCore::getAssetManager()->BText;
	text_Height = bText->getTextHeight("1");

	// Layout Variable Setting
	NumberBoxWidth = bText->getCellWidth() * 2;
	ScoreBoxWidth = bText->getCellWidth() * 3;
	float NumberScoreRatio = float(NumberBoxWidth + ScoreBoxWidth) / SInfo::SCREEN_WIDTH;
	float NameRatio = (1 - NumberScoreRatio) * 0.4;
	float ThoughtRatio = (1 - NumberScoreRatio) * 0.6;
	NameBoxWidth = SInfo::SCREEN_WIDTH * NameRatio;
	ThoughtBoxWidth = SInfo::SCREEN_WIDTH * ThoughtRatio;

	NumberBox.first = 0; NumberBox.second = NumberBoxWidth;
	NameBox.first = NumberBox.second; NameBox.second = NumberBox.second + NameBoxWidth;
	ScoreBox.first = NameBox.second; ScoreBox.second = NameBox.second + ScoreBoxWidth;
	ThoughtBox.first = ScoreBox.second; ThoughtBox.second = ScoreBox.second + ThoughtBoxWidth;

	int GameSuccessHeight = 142; // Manual Setting, Don't Change this If you don't know the ratio of table!!
	int SaveButtonHeight = 50; // Manual Setting, Don't Change this If you don't know the ratio of table!!
	RankTableHeight = SInfo::SCREEN_HEIGHT - (GameSuccessHeight + SaveButtonHeight);
	RankYaxis = GameSuccessHeight;
	rankTableRect.x = 0;
	rankTableRect.y = RankYaxis;
	rankTableRect.w = SInfo::SCREEN_WIDTH;
	rankTableRect.h = RankTableHeight;

	visible_Range = (RankTableHeight - text_Height) / text_Height;
	table_cursor = 0;
	if (rankTable->rankTable_size - visible_Range <= 0)
		table_cursorLimit = 0;
	else
		table_cursorLimit = rankTable->rankTable_size - visible_Range;

	scrollBox_width = 15;
	scrollYmove_Quantity = (int)(RankTableHeight - text_Height) * (1.f / rankTable->rankTable_size);
	scrollBar_height = (RankTableHeight - text_Height) - (scrollYmove_Quantity * table_cursorLimit);
	backgroundScroll =
	{
		SInfo::SCREEN_WIDTH - scrollBox_width,
		RankYaxis + text_Height,
		scrollBox_width,
		RankTableHeight - text_Height
	};
	ScorllBar =
	{
		SInfo::SCREEN_WIDTH - scrollBox_width,
		RankYaxis + text_Height + table_cursor * scrollYmove_Quantity,
		scrollBox_width, scrollBar_height
	};
	isBarClicked = false;
	pastMouseY = 0, currentMouseY = 0;

	numOfMenu = table_cursorLimit + 1;
}

RankingMenu::~RankingMenu() { }

void RankingMenu::Update()
{
	if (activeMenuOption < 0)
		activeMenuOption = 0;

	table_cursor = activeMenuOption;
	ScorllBar.y = RankYaxis + text_Height + table_cursor * scrollYmove_Quantity;

	if (!SCore::bClick)
		isBarClicked = false;
}

void RankingMenu::Draw(SDL_Renderer* rR)
{
	cGameRanking->Draw(rR, 0, 0, false);

	// Rank 정보는 기본적으로 가운데정렬로 Draw함
	SDL_SetRenderDrawColor(rR, 255, 255, 255, 255); // Rank Table Background
	SDL_RenderFillRect(rR, &rankTableRect);
	DrawRankInfo(rR);
	DrawRankLayout(rR);
}

void RankingMenu::DrawRankLayout(SDL_Renderer* rR)
{
	bText->Draw(rR, "No.", NumberBox.first + (NumberBoxWidth - bText->getTextWidth("No.")) / 2,
		RankYaxis);
	bText->Draw(rR, "Name", NameBox.first + (NameBoxWidth - bText->getTextWidth("Name")) / 2,
		RankYaxis);
	bText->Draw(rR, "Score", ScoreBox.first + (ScoreBoxWidth - bText->getTextWidth("Score")) / 2,
		RankYaxis);
	bText->Draw(rR, "Thought", ThoughtBox.first + (ThoughtBoxWidth - bText->getTextWidth("Thought")) / 2,
		RankYaxis);

	// 세로 라인
	SDL_SetRenderDrawColor(rR, 0, 51, 34, 255);
	SDL_RenderDrawLine(rR, NumberBox.first + 1, RankYaxis, NumberBox.first + 1, RankYaxis + RankTableHeight);
	SDL_RenderDrawLine(rR, NumberBox.second, RankYaxis, NumberBox.second, RankYaxis + RankTableHeight);
	SDL_RenderDrawLine(rR, NameBox.first, RankYaxis, NameBox.first, RankYaxis + RankTableHeight);
	SDL_RenderDrawLine(rR, NameBox.second, RankYaxis, NameBox.second, RankYaxis + RankTableHeight);
	SDL_RenderDrawLine(rR, ScoreBox.first, RankYaxis, ScoreBox.first, RankYaxis + RankTableHeight);
	SDL_RenderDrawLine(rR, ScoreBox.second, RankYaxis, ScoreBox.second, RankYaxis + RankTableHeight);
	SDL_RenderDrawLine(rR, ThoughtBox.first, RankYaxis, ThoughtBox.first, RankYaxis + RankTableHeight);
	SDL_RenderDrawLine(rR, ThoughtBox.second - 1, RankYaxis, ThoughtBox.second - 1, RankYaxis + RankTableHeight);

	// 가로 라인
	SDL_RenderDrawLine(rR, 0, RankYaxis, SInfo::SCREEN_WIDTH, RankYaxis);
	SDL_RenderDrawLine(rR, 0, RankYaxis + text_Height, SInfo::SCREEN_WIDTH, RankYaxis + text_Height);
	SDL_RenderDrawLine(rR, 0, RankYaxis + RankTableHeight, SInfo::SCREEN_WIDTH, RankYaxis + RankTableHeight);

	// Scroll 전체 Box
	SDL_RenderFillRect(rR, &backgroundScroll);

	// Scroll Bar Box
	SDL_SetRenderDrawColor(rR, 255, 247, 138, 255);
	SDL_RenderFillRect(rR, &ScorllBar);
}

void RankingMenu::DrawRankInfo(SDL_Renderer* rR)
{
	for (int i = table_cursor, height_index = 1; i < table_cursor + visible_Range; ++i, ++height_index)
	{
		if (i < rankTable->rankTable_size)
		{
			// Number
			bText->Draw(rR, rankTable->vRank_Number[i],
				NumberBox.first + (NumberBoxWidth - bText->getTextWidth(rankTable->vRank_Number[i])) / 2,
				RankYaxis + (height_index)* text_Height);
			// Name
			bText->Draw(rR, rankTable->vRank_Name[i],
				NameBox.first + (NameBoxWidth - bText->getTextWidth(rankTable->vRank_Name[i])) / 2,
				RankYaxis + (height_index)* text_Height);
			// Score
			bText->Draw(rR, rankTable->vRank_Score[i],
				ScoreBox.first + (ScoreBoxWidth - bText->getTextWidth(rankTable->vRank_Score[i])) / 2,
				RankYaxis + (height_index)* text_Height);
			// Thought
			bText->Draw(rR, rankTable->vRank_Thought[i],
				ThoughtBox.first + (ThoughtBoxWidth - bText->getTextWidth(rankTable->vRank_Thought[i])) / 2,
				RankYaxis + (height_index)* text_Height);
		}
	}
}

void RankingMenu::escape()
{
	SInfo::getMM()->setStateID(SInfo::getMM()->eMainMenu);
}

void RankingMenu::click(int x, int y)
{
	// Scroll Bar Click
	if (is_in_button(x, y, ScorllBar))
	{
		isBarClicked = true;
	}
}
void RankingMenu::checkMouseInput(int x, int y)
{
	pastMouseY = currentMouseY;
	currentMouseY = y;

	// Scroll Click Move
	if (isBarClicked)
	{
		if (currentMouseY - pastMouseY < 0) // up
		{
			activeOption(0);
		}
		else if (currentMouseY - pastMouseY > 0)// down
		{
			activeOption(1);
		}
	}
}

void RankingMenu::postProcessing()
{
	if (rankTable->rankTable_size - visible_Range <= 0)
		table_cursorLimit = 0;
	else
		table_cursorLimit = rankTable->rankTable_size - visible_Range;

	scrollYmove_Quantity = (int)(RankTableHeight - text_Height) * (1.f / rankTable->rankTable_size);
	scrollBar_height = (RankTableHeight - text_Height) - (scrollYmove_Quantity * table_cursorLimit);
	ScorllBar =
	{
		SInfo::SCREEN_WIDTH - scrollBox_width,
		RankYaxis + text_Height + table_cursor * scrollYmove_Quantity,
		scrollBox_width, scrollBar_height
	};

	numOfMenu = table_cursorLimit + 1;

	for (int i = 0; i < rankTable->rankTable_size; ++i)
	{
		for (int j = 0; j < rankTable->vRank_Name[i].size(); ++j)
			if (rankTable->vRank_Name[i][j] == '|')
				rankTable->vRank_Name[i][j] = ' ';

		for (int j = 0; j < rankTable->vRank_Thought[i].size(); ++j)
			if (rankTable->vRank_Thought[i][j] == '|')
				rankTable->vRank_Thought[i][j] = ' ';
	}
}