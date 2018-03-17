#include "MapObject.h"

MapObject::MapObject()
{

}

MapObject::MapObject(CIMG* img, int id, int type)
{
	image = img;
	Width = image->getRect().w;
	Height = image->getRect().h;
	ObjectId = id;
	ObjectType = type;
	if (ObjectType == 1)
		bCollision = true;
	else
		bCollision = false;

	Slope = { 0, 0 };
}

MapObject::MapObject(CIMG* img, int id, int type, int y1, int y2)
{
	image = img;
	Width = image->getRect().w;
	Height = image->getRect().h;
	ObjectId = id;
	ObjectType = type;
	if (ObjectType == 1)
		bCollision = true;
	else
		bCollision = false;
	Slope = { y1, y2 };
}

MapObject::~MapObject()
{

}

void MapObject::Draw(SDL_Renderer* rR, int x, int y, SDL_Rect* clip)
{
	image->Draw(rR, x, y, false, clip);
}

void MapObject::Draw(SDL_Renderer* rR, int x, int y)
{
	image->Draw(rR, x, y, false);
}

int MapObject::getWidth()
{
	return Width;
}

int MapObject::getHeight()
{
	return Height;
}

int MapObject::getObjectType()
{
	return ObjectType;
}

bool MapObject::getCollision()
{
	return bCollision;
}

std::pair<int, int> MapObject::getSlopeInfo()
{
	return Slope;
}