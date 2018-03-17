#pragma once

#ifndef TITLE_H
#define TITLE_H

#include "header.h"
#include "CIMG.h"

class Title
{
private:
	
	CIMG* cTitle;

public:

	Title();
	~Title();

	void Update();
	void Draw(SDL_Renderer* rR);

	void enter();

};

#endif // !TITLE_H
