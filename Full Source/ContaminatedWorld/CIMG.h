#ifndef CIMG_H
#define CIMG_H

#include "header.h"

// Texture Core Image
class CIMG
{
private:
	SDL_Texture* tIMG;
	SDL_Rect rRect;

public:
	CIMG();
	CIMG(std::string filename, SDL_Renderer* rR);
	~CIMG();

	void Draw(SDL_Renderer* rR, int x, int y, bool Rotate);
	void Draw(SDL_Renderer* rR, int x, int y, bool Rotate, SDL_Rect* clip);

	// 투명도 설정
	void setAlpha(SDL_Texture* IMG, Uint8 alpha);
	void resetAlpah(SDL_Texture* IMG);


	/* ----- get & set ----- */
	SDL_Texture* getIMG();
	SDL_Rect getRect();
	void setIMG(std::string filename, SDL_Renderer* rR);
	void setIMG_colorkey(std::string filename, SDL_Renderer* rR, Uint8 red, Uint8 green, Uint8 blue);
	void setWH(int width, int height);
};

#endif