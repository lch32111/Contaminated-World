#include "CIMG.h"

CIMG::CIMG() { rRect = { 0, 0, 0, 0 }; }

CIMG::CIMG(std::string filename, SDL_Renderer* rR)
{
	setIMG(filename, rR);
}

CIMG::~CIMG()
{
	if (tIMG != NULL)
	{
		SDL_DestroyTexture(tIMG);
		tIMG = NULL;
		rRect = { 0,0,0,0 };
	}
}

void CIMG::Draw(SDL_Renderer* rR, int x, int y, bool Rotate)
{
	rRect.x = x;
	rRect.y = y;
	if (!Rotate)
		SDL_RenderCopy(rR, tIMG, NULL, &rRect);
	else
		SDL_RenderCopyEx(rR, tIMG, NULL, &rRect, 180, NULL, SDL_FLIP_VERTICAL);
}

void CIMG::Draw(SDL_Renderer* rR, int x, int y, bool Rotate, SDL_Rect* clip)
{
	SDL_Rect renderRect = { x, y, rRect.w, rRect.h };

	if (clip != NULL)
	{
		renderRect.w = clip->w;
		renderRect.h = clip->h;
	}

	if (!Rotate)
		SDL_RenderCopy(rR, tIMG, clip, &renderRect);
	else
		SDL_RenderCopyEx(rR, tIMG, clip, &renderRect, 180, NULL, SDL_FLIP_VERTICAL);
}



/* ----- get & set ----- */
SDL_Texture* CIMG::getIMG() { return tIMG; }
SDL_Rect CIMG::getRect() { return rRect; }

void CIMG::setIMG(std::string filename, SDL_Renderer* rR)
{
	// 파일 이미지 확장자 변경 가능, 파일주소에 한글이 들어있으면 안됌
	filename = "files/images/" + filename + ".png";
	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());

	if (loadedSurface == NULL)
	{
		printf("Image load fail // CIMG.cpp // Error : %s\n", SDL_GetError());
	}
	else
	{
		// Color key image, colorkey 할 이미지 정하고 배경색 설정하기
		// SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));

		tIMG = SDL_CreateTextureFromSurface(rR, loadedSurface);

		if (tIMG == NULL)
		{
			printf("Texture creation fail // CIMG.cpp // Error : %s\n", SDL_GetError());
		}
		else
		{
			rRect.w = loadedSurface->w;
			rRect.h = loadedSurface->h;
		}
	}

	SDL_FreeSurface(loadedSurface);
}

void CIMG::setIMG_colorkey(std::string filename, SDL_Renderer* rR, Uint8 red, Uint8 green, Uint8 blue)
{
	// 파일 이미지 확장자 변경 가능, 파일주소에 한글이 들어있으면 안됌
	filename = "files/images/" + filename + ".png";
	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());

	if (loadedSurface == NULL)
	{
		printf("Image load fail // CIMG.cpp // Error : %s\n", SDL_GetError());
	}
	else
	{
		// Color key image, colorkey 할 이미지 정하고 배경색 설정하기
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, red, green, blue));
		tIMG = SDL_CreateTextureFromSurface(rR, loadedSurface);

		if (tIMG == NULL)
		{
			printf("Texture creation fail // CIMG.cpp // Error : %s\n", SDL_GetError());
		}
		else
		{
			rRect.w = loadedSurface->w;
			rRect.h = loadedSurface->h;
		}
	}

	SDL_FreeSurface(loadedSurface);
}

void CIMG::setAlpha(SDL_Texture* IMG, Uint8 alpha)
{
	SDL_SetTextureAlphaMod(IMG, alpha);
}

void CIMG::resetAlpah(SDL_Texture* IMG)
{
	SDL_SetTextureAlphaMod(IMG, 255);
}

void CIMG::setWH(int width, int height)
{
	rRect.w = width;
	rRect.h = height;
}