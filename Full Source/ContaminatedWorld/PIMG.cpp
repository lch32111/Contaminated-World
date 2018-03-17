#include "PIMG.h"

PIMG::PIMG() { }

PIMG::PIMG(std::string filename, SDL_Renderer* rR, Uint8 CK_r, Uint8 CK_g, Uint8 CK_b)
{
	setIMG(filename, rR, CK_r, CK_g, CK_b);
}

PIMG::~PIMG()
{
	if (tIMG != NULL)
	{
		SDL_DestroyTexture(tIMG);
		tIMG = NULL;
		rRect = { 0,0,0,0 };
		m_pixels = NULL;
		m_pitch = 0;
	}
}

void PIMG::Draw(SDL_Renderer* rR, int x, int y, bool Rotate)
{
	rRect.x = x;
	rRect.y = y;
	if (!Rotate)
		SDL_RenderCopy(rR, tIMG, NULL, &rRect);
	else
		SDL_RenderCopyEx(rR, tIMG, NULL, &rRect, 180, NULL, SDL_FLIP_VERTICAL);
}

void PIMG::Draw(SDL_Renderer* rR, int x, int y, bool Rotate, SDL_Rect* clip)
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

bool PIMG::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if (m_pixels != NULL)
	{
		printf("Texture is already locked!\n");
		success = false;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(tIMG, NULL, &m_pixels, &m_pitch) != 0)
		{
			printf("Unable to lock texture! %s\n", SDL_GetError());
			success = false;
		}
	}

	return success;
}

bool PIMG::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if (m_pixels == NULL)
	{
		printf("Texture is not locked!\n");
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture(tIMG);
		m_pixels = NULL;
		m_pitch = 0;
	}

	return success;
}

/* ----- get & set ----- */
SDL_Texture* PIMG::getIMG() { return tIMG; }
SDL_Rect PIMG::getRect() { return rRect; }

void PIMG::setIMG(std::string filename, SDL_Renderer* rR, Uint8 CK_r, Uint8 CK_g, Uint8 CK_b)
{
	// 파일 이미지 확장자 변경 가능, 파일주소에 한글이 들어있으면 안됌
	filename = "files/images/" + filename + ".png";
	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
	SDL_Texture* newTexture = NULL;

	if (loadedSurface == NULL)
	{
		printf("Image load fail // PIMG.cpp // Error : %s\n", SDL_GetError());
	}
	else
	{
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);
		if (formattedSurface == NULL)
		{
			printf("Loaded surface convert fail // PIMG.cpp // Error :  %s\n", SDL_GetError());
		}
		else
		{
			newTexture = SDL_CreateTexture(rR, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				printf("Blank Texture creation fail // PIMG.cpp // Error : %s", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &m_pixels, &m_pitch);

				//Copy loaded/formatted surface pixels
				memcpy(m_pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				rRect.w = formattedSurface->w;
				rRect.h = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)m_pixels;
				int pixelCount = (m_pitch / 4) * rRect.h;  // m_pitch에는 픽셀 row당 bytes의 수가 들어가 있어, 한 픽셀당 4 bytes로 되어 있어 4를 나눈다.

				//Map colors				
				Uint32 colorKey = SDL_MapRGB(formattedSurface->format, CK_r, CK_g, CK_b);
				Uint32 transparent = SDL_MapRGBA(formattedSurface->format, CK_r, CK_g, CK_b, 0x00);

				//Color key pixels
				for (int i = 0; i < pixelCount; ++i)
				{
					if (pixels[i] == colorKey)
					{
						pixels[i] = transparent;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				m_pixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		SDL_FreeSurface(loadedSurface);
	}

	tIMG = newTexture;
}

void PIMG::setWH(int width, int height)
{
	rRect.w = width;
	rRect.h = height;
}

void* PIMG::getPixels()
{
	return m_pixels;
}

int PIMG::getPitch()
{
	return m_pitch;
}

Uint32 PIMG::getPixel32(unsigned int x, unsigned int y)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32*)m_pixels;

	//Get the pixel requested
	return pixels[(y * (m_pitch / 4)) + x];
}