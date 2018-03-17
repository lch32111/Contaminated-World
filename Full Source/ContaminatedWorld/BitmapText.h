#ifndef _BITMAP_TEXT_H_
#define _BITMAP_TEXT_H_

#include "PIMG.h"

// basicfont.png에 맞춰진 클래스임
class Bitmap_Text
{
private:
	PIMG* font;
	SDL_Rect charRect[128];
	int m_newLine, m_space;

	int font_row, font_col;
	int cellW;
	bool buildFont();
public:
	Bitmap_Text();
	Bitmap_Text(PIMG* img);
	~Bitmap_Text();

	void Draw(SDL_Renderer* rR, std::string BText, unsigned int x, unsigned int y);
	void DrawXCenter(SDL_Renderer* rR, std::string BText, unsigned int y);

	int getTextWidth(std::string text);
	int getTextHeight(std::string text);
	int getCellWidth();
};

#endif