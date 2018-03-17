#pragma once

#ifndef CORE_H
#define CORE_H

#include "header.h"
#include "StaticInfo.h"
#include "Map.h"
#include "AssetManager.h"

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

	bool bKeypressed, bMousePressed; // keyInput, mouseInput flag 
	bool bRight_Key, bLeft_Key; // Key -> Pressed == TRUE, Unpressed == FALSE
	bool bMenuPressed;
	bool bMouseLeftClick;
	bool bDoubleClick;
	
	uint32_t mouseState;
	int mouseXpos, mouseYpos;

	static SInfo* oSInfo;
	static Map* oMap;
	static AssetManager* oAssetManager;

	void MouseInput();
	void KeyboardInput();
	void MenuMouseInput();
	void PlayMouseInput();
	void KeyboardInputEnding();
	void InputMenu();
	void InputPlay();
	void Update();
	void Draw();

public:
	SCore(void);
	~SCore(void);

	static bool bQuitGame;
	static bool bClick;
	static bool bTextInputActive;
	static void startTextInput();
	static void stopTextInput();
	
	void mainLoop();

	// ------ get & set -----
	static Map* getMap();
	static AssetManager* getAssetManager();
};


#endif