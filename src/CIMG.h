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
	
	/* ----- get & set ----- */
	SDL_Texture* getIMG();
	SDL_Rect getRect();
	void setIMG(std::string filename, SDL_Renderer* rR);
	void setWH(int width, int height);

};

#endif