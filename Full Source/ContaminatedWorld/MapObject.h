#pragma once

#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "CIMG.h"

class MapObject
{
private:
	CIMG* image;
	int ObjectId;
	int ObjectType; // 0 == background(false), 1 == solid tile(true), 2 == slope tile(false)
	int Width
		 , Height;
	bool bCollision;

	std::pair<int, int> Slope;
public:

	MapObject();
	MapObject(CIMG* img, int id, int type);
	MapObject(CIMG* img, int id, int type, int y1, int y2);
	~MapObject();

	void Draw(SDL_Renderer* rR, int x, int y, SDL_Rect* clip);
	void Draw(SDL_Renderer* rR, int x, int y);

	/* ----- get & set ----- */
	int getWidth();
	int getHeight();
	int getObjectType();
	bool getCollision();
	std::pair<int, int> getSlopeInfo();
};
#endif