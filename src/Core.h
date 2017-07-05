#pragma once

#ifndef CORE_H
#define CORE_H

#include "header.h"
#include "Map.h"

class SCore // System Core
{
private:
	SDL_Window* sWindow;
	SDL_Renderer* sRenderer;
	SDL_Event* sEvent;

	// FPS START

	long frameTime;
	static const int MIN_FRAME_TIME = 16;
	unsigned long lFPSTime;
	int iNumofFPS, iFPS;

	// FPS END


	// Key -> Pressed == TRUE, Unpressed == FALSE
	bool bRight_Key, bLeft_Key;
	bool bMenuPressed;	//--

	// Direction LEFT == FALSE, RIGHT == TRUE
	bool bLeft_Right;
	

	static Map* oMap;

	void Input();
	void MouseInput();
	void Update();
	void Draw();

public:
	SCore(void);
	~SCore(void);

	static bool bQuitGame;
	
	void mainLoop();

	static Map* getMap();
};

#endif