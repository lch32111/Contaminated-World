#ifndef PIMG_H
#define PIMG_H

#include "header.h"

// Texture Pixel Image
class PIMG
{
private:
	SDL_Texture* tIMG;
	void* m_pixels;
	int m_pitch;
	SDL_Rect rRect;

public:
	PIMG();
	PIMG(std::string filename, SDL_Renderer* rR, Uint8 CK_r, Uint8 CK_g, Uint8 CK_b);
	~PIMG();

	void Draw(SDL_Renderer* rR, int x, int y, bool Rotate);
	void Draw(SDL_Renderer* rR, int x, int y, bool Rotate, SDL_Rect* clip);

	//Pixel manipulators
	bool lockTexture();
	bool unlockTexture();


	/* ----- get & set ----- */
	SDL_Texture* getIMG();
	SDL_Rect getRect();
	void setIMG(std::string filename, SDL_Renderer* rR, Uint8 CK_r, Uint8 CK_g, Uint8 CK_b);
	void setWH(int width, int height);
	void* getPixels();
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);
};

#endif