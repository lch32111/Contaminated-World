#include "BitmapText.h"
#include "StaticInfo.h"
#include "Core.h"

Bitmap_Text::Bitmap_Text()
{
	this->font = NULL;
	this->m_newLine = this->m_space = this->font_row = this->font_col = 0;
}

// Colorkey RGB 245 247 242 
Bitmap_Text::Bitmap_Text(PIMG* img)
{
	font = img;
	this->font_row = 8;
	this->font_col = 16;
	

	if (!buildFont())
		printf("Failed to build font // Bitmap_Text.cpp\n");
	this->m_space = 6;
	this->m_newLine = 24;
}

Bitmap_Text::~Bitmap_Text()
{

}

bool Bitmap_Text::buildFont()
{
	bool success = true;

	//Lock pixels for access
	if (!font->lockTexture())
	{
		printf("Unable to lock bitmap font texture!\n");
		success = false;
	}
	else
	{
		//Set the background color
		Uint32 bgColor = font->getPixel32(0, 0);

		//Set the cell dimensions
		cellW = font->getRect().w / font_col;
		int cellH = font->getRect().h / font_row;

		//New line variables
		int top = cellH;
		int baseA = cellH;

		//The current character we're setting
		int currentChar = 0;

		//Go through the cell rows
		for (int rows = 0; rows < font_row; ++rows)
		{
			//Go through the cell columns
			for (int cols = 0; cols < font_col; ++cols)
			{
				//Set the character offset
				charRect[currentChar].x = cellW * cols;
				charRect[currentChar].y = cellH * rows;

				//Set the dimensions of the character
				charRect[currentChar].w = cellW;
				charRect[currentChar].h = cellH;

				//Find Left Side
				//Go through pixel columns
				for (int pCol = 0; pCol < cellW; ++pCol)
				{
					//Go through pixel rows
					for (int pRow = 0; pRow < cellH; ++pRow)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pCol;
						int pY = (cellH * rows) + pRow;

						//If a non colorkey pixel is found
						if (font->getPixel32(pX, pY) != bgColor)
						{
							//Set the x offset
							charRect[currentChar].x = pX;

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Right Side
				//Go through pixel columns
				for (int pColW = cellW - 1; pColW >= 0; --pColW)
				{
					//Go through pixel rows
					for (int pRowW = 0; pRowW < cellH; ++pRowW)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pColW;
						int pY = (cellH * rows) + pRowW;

						//If a non colorkey pixel is found
						if (font->getPixel32(pX, pY) != bgColor)
						{
							//Set the width
							charRect[currentChar].w = (pX - charRect[currentChar].x) + 1;

							//Break the loops
							pColW = -1;
							pRowW = cellH;
						}
					}
				}

				//Find Top
				//Go through pixel rows
				for (int pRow = 0; pRow < cellH; ++pRow)
				{
					//Go through pixel columns
					for (int pCol = 0; pCol < cellW; ++pCol)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pCol;
						int pY = (cellH * rows) + pRow;

						//If a non colorkey pixel is found
						if (font->getPixel32(pX, pY) != bgColor)
						{
							//If new top is found
							if (pRow < top)
							{
								top = pRow;
							}

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Bottom of A
				if (currentChar == 'A')
				{
					//Go through pixel rows
					for (int pRow = cellH - 1; pRow >= 0; --pRow)
					{
						//Go through pixel columns
						for (int pCol = 0; pCol < cellW; ++pCol)
						{
							//Get the pixel offsets
							int pX = (cellW * cols) + pCol;
							int pY = (cellH * rows) + pRow;

							//If a non colorkey pixel is found
							if (font->getPixel32(pX, pY) != bgColor)
							{
								//Bottom of a is found
								baseA = pRow;

								//Break the loops
								pCol = cellW;
								pRow = -1;
							}
						}
					}
				}

				//Go to the next character
				++currentChar;
			}
		}

		//Calculate space
		m_space = cellW / 2;

		//Calculate new line
		m_newLine = baseA - top;

		//Lop off excess top pixels
		for (int i = 0; i < font_row * font_col; ++i)
		{
			charRect[i].y += top;
			charRect[i].h -= top;
		}

		font->unlockTexture();
	}

	return success;
} // buildfont()

void Bitmap_Text::Draw(SDL_Renderer* rR, std::string BText, unsigned int x, unsigned int y)
{
	if (font != NULL)
	{
		//Temp offsets
		int curX = x, curY = y;

		//Go through the text
		for (int i = 0; i < BText.length(); ++i)
		{
			//If the current character is a space
			if (BText[i] == ' ')
			{
				//Move over
				curX += m_space;
			}
			//If the current character is a newline
			else if (BText[i] == '\n')
			{
				//Move down
				curY += m_newLine;

				//Move back
				curX = x;
			}
			else
			{
				//Get the ASCII value of the character
				int ascii = (unsigned char)BText[i];

				//Show the character
				font->Draw(rR, curX, curY, false, &charRect[ascii]);

				//Move over the width of the character with one pixel of padding
				curX += charRect[ascii].w + 1;
			}
		}
	}
}

void Bitmap_Text::DrawXCenter(SDL_Renderer* rR, std::string BText, unsigned int y)
{
	int centerX = (SInfo::SCREEN_WIDTH - getTextWidth(BText)) / 2;

	if (font != NULL)
	{
		//Temp offsets
		int curX = centerX, curY = y;

		//Go through the text
		for (int i = 0; i < BText.length(); ++i)
		{
			//If the current character is a space
			if (BText[i] == ' ')
			{
				//Move over
				curX += m_space;
			}
			//If the current character is a newline
			else if (BText[i] == '\n')
			{
				//Move down
				curY += m_newLine;

				//Move back
				curX = centerX;
			}
			else
			{
				//Get the ASCII value of the character
				int ascii = (unsigned char)BText[i];

				//Show the character
				font->Draw(rR, curX, curY, false, &charRect[ascii]);

				//Move over the width of the character with one pixel of padding
				curX += charRect[ascii].w + 1;
			}
		}
	}

}

int Bitmap_Text::getTextWidth(std::string text)
{
	int t_width = 0;
	for (int i = 0; i < text.size(); ++i)
	{
		if (text[i] == ' ')
		{
			t_width += m_space;
		}
		else if (text[i] != '\n')
		{
			t_width += charRect[(unsigned int)text[i]].w + 1;
		}
	}
	return t_width;
}

int Bitmap_Text::getTextHeight(std::string text)
{
	int t_height = 0;
	if (text.size() != 0)
		t_height += m_newLine;

	for (int i = 0; i < text.size(); ++i)
	{
		if (text[i] == '\n')
		{
			t_height += m_newLine;
		}
	}
	return t_height;
}

int Bitmap_Text::getCellWidth() { return cellW; }