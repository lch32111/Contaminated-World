#include "EndingMenu.h"
#include "Core.h"
#include <string>

EndingMenu::~EndingMenu() { }
EndingMenu::EndingMenu()
{
	isGameSuccess = true;
	iTimePassed = 0;

	// Game Success Variables
	cGameSuccess = SCore::getAssetManager()->getEndingMenuIMG();
	cRankSave = &cGameSuccess[2];
	cRankSave_over = &cGameSuccess[3];

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
	int SaveButtonHeight = cRankSave->getRect().h;
	RankTableHeight = SInfo::SCREEN_HEIGHT - (GameSuccessHeight + SaveButtonHeight);
	RankYaxis = GameSuccessHeight;
	bSaveButtonOver = false;
	SaveButtonRect.x = SInfo::SCREEN_WIDTH - cRankSave->getRect().w;
	SaveButtonRect.y = GameSuccessHeight + RankTableHeight;
	SaveButtonRect.w = cRankSave->getRect().w;
	SaveButtonRect.h = SaveButtonHeight;
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

	isNewBoxDisplayed = false;
	isNameSelected = false;
	isThoughtSelected = false;
	bTextWidthExcessFlag = false;
	bTextWrongSelectionFlag = false;
	bTextNotFilledFlag = false;
	isFirstNameInput = true;
	isFirstThoughtInput = true;
	userNameInput = NULL;
	userThoughtInput = NULL;
	userScore = 0;
	// Layout Variable Setting

	// Game Success Variables
	

	// Game Fail Variables
	cGameFail = &cGameSuccess[1];

	cQuitIcon = SCore::getAssetManager()->getPauseMenuIMG();
	cQuitIcon_over = &cQuitIcon[1];
	cGotoMain = &cQuitIcon[4];
	cGotoMain_over = &cQuitIcon[5];
	this->menuXpos = (SInfo::SCREEN_WIDTH - cQuitIcon->getRect().w) / 2;
	this->menuYpos = SInfo::SCREEN_HEIGHT / 2;
	numOfMenu = 2;
	// Game Fail Variables
}

void EndingMenu::insertRankInfo()
{
	// 1. Search Insert_Index
	int insertIndex = 0;

	// 3개 이상 일 땐 이 알고리즘 통해서 index search
	if (rankTable->rankTable_size >= 3)
	{
		for (int i = 0; i < rankTable->rankTable_size - 1; ++i)
		{
			int left = atoi(rankTable->vRank_Score[i].c_str());
			int right = atoi(rankTable->vRank_Score[i + 1].c_str());

			// First Index Case
			if (i == 0)
			{
				if (left < userScore)
				{
					insertIndex = 0;
					break;
				}
				else if (left >= userScore && right < userScore)
				{
					insertIndex = i + 1;
					break;
				}

			}
			// Last Index Case
			else if (i == rankTable->rankTable_size - 2)
			{
				if (left >= userScore && right < userScore)
				{
					insertIndex = i + 1;
					break;
				}
				else
				{
					insertIndex = rankTable->rankTable_size;
					break;
				}
			}
			// Middel Index case
			else
			{
				if (left >= userScore && right < userScore)
				{
					insertIndex = i + 1;
					break;
				}
			}
		}
	}
	else
	{
		if (rankTable->rankTable_size == 1)
		{
			int left = atoi(rankTable->vRank_Score[0].c_str());

			if (left >= userScore)
			{
				insertIndex = 1;
			}
		}
		else if (rankTable->rankTable_size == 2)
		{
			int left = atoi(rankTable->vRank_Score[0].c_str());
			int right = atoi(rankTable->vRank_Score[1].c_str());

			if (left < userScore)
			{
				insertIndex = 0;
			}
			else if (left >= userScore && right < userScore)
			{
				insertIndex = 1;
			}
			else
				insertIndex = 2;
		}

	}
	

	userNumber = insertIndex; // the variable for displaying user text input through the height

	// 2. Insert
	if (insertIndex == 0) // Begin
	{
		std::vector<std::string>::iterator it = rankTable->vRank_Number.begin();
		rankTable->vRank_Number.insert(it, "1");

		it = rankTable->vRank_Name.begin();
		rankTable->vRank_Name.insert(it, "Please Enter Your Name");

		it = rankTable->vRank_Score.begin();
		rankTable->vRank_Score.insert(it, std::to_string(userScore));

		it = rankTable->vRank_Thought.begin();
		rankTable->vRank_Thought.insert(it, "Please Enter What You Want To Say");
	}
	else
	{
		std::vector<std::string>::iterator it = rankTable->vRank_Number.begin() + insertIndex;
		rankTable->vRank_Number.insert(it, std::to_string(insertIndex + 1));

		it = rankTable->vRank_Name.begin() + insertIndex;
		rankTable->vRank_Name.insert(it, "Please Enter Your Name");

		it = rankTable->vRank_Score.begin() + insertIndex;
		rankTable->vRank_Score.insert(it, std::to_string(userScore));

		it = rankTable->vRank_Thought.begin() + insertIndex;
		rankTable->vRank_Thought.insert(it, "Please Enter What You Want To Say");
	}

	// 3. PostProcessing for Table and View
	rankTable->rankTable_size += 1;

	for (int i = 0; i < rankTable->rankTable_size; ++i)
		rankTable->vRank_Number[i] = std::to_string(i + 1);
	
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

	if (insertIndex > table_cursorLimit)
		activeMenuOption = table_cursorLimit; // To prevent the viewpoint from  not going beyond the limitation
	else
		activeMenuOption = insertIndex; // To change the viewpoint on the table

	userNameInput = &(rankTable->vRank_Name[insertIndex]);
	userThoughtInput = &(rankTable->vRank_Thought[insertIndex]);

	// To prevent the case of doing a game continuously
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

void EndingMenu::saveRanking()
{
	// Error Checking 1
	if (isFirstNameInput || isFirstThoughtInput)
	{
		bTextNotFilledFlag = true;
		iTimePassed = SDL_GetTicks();
		return;
	}

	// Error Checking 2
	if (rankTable->vRank_Name[userNumber].size() == 0 || rankTable->vRank_Thought[userNumber].size() == 0)
	{
		bTextNotFilledFlag = true;
		iTimePassed = SDL_GetTicks();
		return;
	}

	// Space Processing
	for (int i = 0; i < rankTable->rankTable_size; ++i)
	{
		for (int j = 0; j < rankTable->vRank_Name[i].size(); ++j)
			if (rankTable->vRank_Name[i][j] == ' ')
				rankTable->vRank_Name[i][j] = '|';

		for (int j = 0; j < rankTable->vRank_Thought[i].size(); ++j)
			if (rankTable->vRank_Thought[i][j] == ' ')
				rankTable->vRank_Thought[i][j] = '|';
	}

	// File Writing
	FILE* cwrtFile;
	fopen_s(&cwrtFile, "TestRankTable.cwrt", "wb");

	fprintf(cwrtFile, "# THE NUMBER OF RANK ITEMS\r\n");
	fprintf(cwrtFile, "# RANK_NUMBER // RANK_NAME // RANK_SCORE // CONTENTS\r\n");
	fprintf(cwrtFile, "NUMBER %d\r\n", rankTable->rankTable_size);
	for (int i = 0; i < rankTable->rankTable_size; ++i)
	{
		fprintf(cwrtFile, "%s ", rankTable->vRank_Number[i].c_str());
		fprintf(cwrtFile, "%s ", rankTable->vRank_Name[i].c_str());
		fprintf(cwrtFile, "%s ", rankTable->vRank_Score[i].c_str());
		fprintf(cwrtFile, "%s\r\n", rankTable->vRank_Thought[i].c_str());
	}

	fclose(cwrtFile);

	SCore::stopTextInput();

	// reset Variables
	bSaveButtonOver = false;
	isBarClicked = false;
	isNewBoxDisplayed = false;
	isNameSelected = false;
	isThoughtSelected = false;
	bTextWidthExcessFlag = false;
	bTextWrongSelectionFlag = false;
	bTextNotFilledFlag = false;
	isFirstNameInput = true;
	isFirstThoughtInput = true;

	resetGotoMain();
}

void EndingMenu::DrawRankLayout(SDL_Renderer* rR)
{
	bText->Draw(rR, "No.", NumberBox.first + (NumberBoxWidth - bText->getTextWidth("No.")) / 2, 
							RankYaxis);
	bText->Draw(rR, "Name", NameBox.first + (NameBoxWidth - bText->getTextWidth("Name")) / 2,
							RankYaxis);
	bText->Draw(rR, "Score", ScoreBox.first + (ScoreBoxWidth - bText->getTextWidth("Score")) / 2, 
							RankYaxis);
	bText->Draw(rR, "Thought", ThoughtBox.first +  (ThoughtBoxWidth - bText->getTextWidth("Thought")) / 2, 
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

void EndingMenu::DrawRankInfo(SDL_Renderer* rR)
{
	int displaying_check = 0;

	for (int i = table_cursor, height_index = 1; i < table_cursor + visible_Range; ++i, ++height_index)
	{
		if (i < rankTable->rankTable_size)
		{
			// User Input Box Highlight
			if (i == userNumber)
			{
				NewnameBox = { NameBox.first, RankYaxis + (height_index) * text_Height, NameBoxWidth, text_Height };
				NewThoughtBox = { ThoughtBox.first, RankYaxis + (height_index)* text_Height , ThoughtBoxWidth, text_Height };
				
				SDL_SetRenderDrawColor(rR, 171, 208, 188, 255);
				SDL_RenderFillRect(rR, &NewnameBox);
				SDL_RenderFillRect(rR, &NewThoughtBox);

				++displaying_check;
			}

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

	if (displaying_check == 0)
	{
		isNewBoxDisplayed = false;
		isNameSelected = false;
		isThoughtSelected = false;
	}
	else
	{
		isNewBoxDisplayed = true;
	}
}

void EndingMenu::DrawDieMenu(SDL_Renderer* rR)
{
	cGotoMain->Draw(rR, menuXpos, menuYpos, false);
	cQuitIcon->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 10 * 2, false);
}

// 메인으로 메뉴 활성화
void EndingMenu::DrawDieMenu_over1(SDL_Renderer* rR)
{
	cGotoMain_over->Draw(rR, menuXpos, menuYpos, false);
	cQuitIcon->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 10 * 2, false);
}

// 게임종료 메뉴 활성화
void EndingMenu::DrawDieMenu_over2(SDL_Renderer* rR)
{
	cGotoMain->Draw(rR, menuXpos, menuYpos, false);
	cQuitIcon_over->Draw(rR, menuXpos, menuYpos + SInfo::SCREEN_HEIGHT / 10 * 2, false);
}


void EndingMenu::enter()
{
	if (isGameSuccess)
	{

	}
	else
	{
		switch (activeMenuOption)
		{
		case 0: // 메인으로
			resetGotoMain();
			break;
		case 1: // 게임 종료
			SInfo::getMM()->getMainMenu()->quitGame();
			break;
		}
	}
}

void EndingMenu::click(int x, int y)
{
	if (isGameSuccess)
	{
		// Scroll Bar Click
		if (is_in_button(x, y, ScorllBar))
		{
			isBarClicked = true;
		}

		// User Input Box Click
		if (isNewBoxDisplayed)
		{
			if (is_in_button(x, y, NewnameBox))
			{
				isNameSelected = true;
				isThoughtSelected = false;
			}
			else if (is_in_button(x, y, NewThoughtBox))
			{
				isThoughtSelected = true;
				isNameSelected = false;
			}
			else
			{
				isNameSelected = false;
				isThoughtSelected = false;
			}
		}

		// Save Ranking
		if (is_in_button(x, y, SaveButtonRect))
		{
			saveRanking();
		}
	}
	else
	{
		switch (activeMenuOption)
		{
		case 0: // 메인으로
			if (is_in_button(x, y, cGotoMain->getRect()))
				resetGotoMain();
			break;
		case 1: // 게임 종료
			if (is_in_button(x, y, cQuitIcon->getRect()))
				SCore::bQuitGame = true;
			break;
		}
	}
}

void EndingMenu::checkMouseInput(int x, int y)
{
	if (isGameSuccess)
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
			else if(currentMouseY - pastMouseY > 0)// down
			{
				activeOption(1);
			}
		}

		// Save Button Over
		if (is_in_button(x, y, SaveButtonRect))
			bSaveButtonOver = true;
		else
			bSaveButtonOver = false;
	}
	else
	{
		if (is_in_button(x, y, cGotoMain->getRect()))
			activeMenuOption = 0;

		else if (is_in_button(x, y, cQuitIcon->getRect()))
			activeMenuOption = 1;
		else
			activeMenuOption = -1;
	}
}

void EndingMenu::resetGotoMain()
{
	SCore::getMap()->setCurrentLevel(0);
	SCore::getMap()->reset();
	SInfo::getMM()->getUpgradeUI()->setbCalcCoin(false);
	SInfo::getMM()->setStateID(SInfo::getMM()->eMainMenu);
	SInfo::getMusic()->PlayMusic(SInfo::getMusic()->mTitle);
}


void EndingMenu::Update()
{
	if (isGameSuccess)
	{
		if (activeMenuOption < 0)
			activeMenuOption = 0;
		
		table_cursor = activeMenuOption;
		ScorllBar.y = RankYaxis + text_Height + table_cursor * scrollYmove_Quantity;

		if (!SCore::bClick)
			isBarClicked = false;

		if (bTextWidthExcessFlag)
		{
			if (SDL_GetTicks() - iTimePassed >= 1500) // 1.5초 동안 Error Message 보이기
			{
				bTextWidthExcessFlag = false;
			}
		}

		if (bTextWrongSelectionFlag)
		{
			if (SDL_GetTicks() - iTimePassed >= 1500)
			{
				bTextWrongSelectionFlag = false;
			}
		}

		if (bTextNotFilledFlag)
		{
			if (SDL_GetTicks() - iTimePassed >= 1500)
			{
				bTextNotFilledFlag = false;
			}
		}
	}
}

void EndingMenu::Draw(SDL_Renderer* rR)
{
	if (isGameSuccess)
	{
		cGameSuccess->Draw(rR, 0, 0, false);

		// Rank 정보는 기본적으로 가운데정렬로 Draw함
		SDL_SetRenderDrawColor(rR, 255, 255, 255, 255); // Rank Table Background
		SDL_RenderFillRect(rR, &rankTableRect);
		DrawRankInfo(rR);
		DrawRankLayout(rR);
		
		if (bSaveButtonOver)
			cRankSave_over->Draw(rR, SaveButtonRect.x, SaveButtonRect.y, false);
		else
			cRankSave->Draw(rR, SaveButtonRect.x, SaveButtonRect.y, false);

		if (bTextWidthExcessFlag)
		{
			bText->DrawXCenter(rR, "Text Too Long!!", SInfo::SCREEN_HEIGHT / 2);
		}

		if (bTextWrongSelectionFlag)
		{
			bText->DrawXCenter(rR, "You Can't enter |", SInfo::SCREEN_HEIGHT / 2);
		}

		if (bTextNotFilledFlag)
		{
			bText->DrawXCenter(rR, "Please Fill Your Name And Thought", SInfo::SCREEN_HEIGHT / 2);
		}
	}
	else
	{
		cGameFail->Draw(rR, 0, 0, false);

		switch (activeMenuOption)
		{
		case 0:	// 메인으로 활성화
			DrawDieMenu_over1(rR);
			break;
		case 1:	// 게임종료
			DrawDieMenu_over2(rR);
			break;
		default:
			DrawDieMenu(rR);
			break;
		}
	}
}

void EndingMenu::setGameSuccess(bool game, int score)
{
	EndingMenu::isGameSuccess = game;

	// success
	if (isGameSuccess) 
	{
		numOfMenu = table_cursorLimit + 1;
		activeMenuOption = 0;
		userScore = score;
		insertRankInfo();
		SCore::startTextInput();
		isNameSelected = true;
	}
	// fail
	else 
	{
		numOfMenu = 2;
	}
}

void EndingMenu::appendUserText(char* inputText)
{
	if (isNameSelected)
	{
		if (isFirstNameInput)
		{
			isFirstNameInput = false;
			userNameInput->clear();
		}

		*userNameInput += inputText;

		// Error Checking
		if (bText->getTextWidth(*userNameInput) >= NameBoxWidth)
		{
			userNameInput->pop_back();
			bTextWidthExcessFlag = true;
			iTimePassed = SDL_GetTicks();
		}
		else if (*inputText == '|')
		{
			userNameInput->pop_back();
			bTextWrongSelectionFlag = true;
			iTimePassed = SDL_GetTicks();
		}
	}
	else if (isThoughtSelected)
	{
		if (isFirstThoughtInput)
		{
			isFirstThoughtInput = false;
			userThoughtInput->clear();
		}

		*userThoughtInput += inputText;

		// Error Checking
		if (bText->getTextWidth(*userThoughtInput) >= ThoughtBoxWidth)
		{
			userThoughtInput->pop_back();
			bTextWidthExcessFlag = true;
			iTimePassed = SDL_GetTicks();
		}
		else if (*inputText == '|')
		{
			userThoughtInput->pop_back();
			bTextWrongSelectionFlag = true;
			iTimePassed = SDL_GetTicks();
		}
	}
}

void EndingMenu::popupUserText()
{
	if (isNameSelected)
	{
		if (userNameInput->size() > 0)
			userNameInput->pop_back();
	}
	else if (isThoughtSelected)
	{
		if (userThoughtInput->size() > 0)
			userThoughtInput->pop_back();
	}
	
}