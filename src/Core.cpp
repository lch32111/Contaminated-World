#include "header.h"
#include "Core.h"
#include "CIMG.h"
 #include "StaticInfo.h"
#include <SDL_mixer.h>

Map* SCore::oMap = new Map();

// Static initialization start
bool SCore::bQuitGame = false;
// Static initialization end

/* ******************************************** */

SCore::SCore(void)
{
	this->bQuitGame = false;
	this->iFPS = 0;
	this->iNumofFPS = 0;
	this->lFPSTime = 0;
	this->bRight_Key = this->bLeft_Key = false;
	this->bLeft_Right =  true; // 캐릭터는 오른쪽을 향하도록
	this->bMenuPressed = false;


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize // Core.cpp // Error : %s\n", SDL_GetError());
		bQuitGame = true;
	}
	else
	{

		sWindow = SDL_CreateWindow("Contaminated_World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SInfo::GAME_WIDTH, SInfo::GAME_HEIGHT, SDL_WINDOW_SHOWN);
		if (sWindow == NULL)
		{
			printf("sWindow creation fail // Core.cpp // Error : %s", SDL_GetError());
			bQuitGame = true;
		}

		sRenderer = SDL_CreateRenderer(sWindow, -1, SDL_RENDERER_ACCELERATED);
		if (sRenderer == NULL)
		{
			printf("sRenderer creation fail // Core.cpp // Error : %s", SDL_GetError());
			bQuitGame = false;
		}
		else
		{
			sEvent = new SDL_Event();
			oMap = new Map(sRenderer);

			// 여러가지 것들 초기화 START
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("Audio Initialization fail // Core.cpp // Error : %s", SDL_GetError());
				bQuitGame = false;
			}


			// 여러가지 것들 초기화 END
			SInfo::KeyIDRight = SDLK_RIGHT;
			SInfo::KeyIDLeft = SDLK_LEFT;
			SInfo::KeyIDAlt = SDLK_LALT;
			SInfo::KeyIDCtrl = SDLK_LCTRL;
			SInfo::KeyAlt = false;
			SInfo::KeyCtrl = false;

		}

	}
}

SCore::~SCore(void)
{
	delete sEvent;
	SDL_DestroyRenderer(sRenderer);
	SDL_DestroyWindow(sWindow);
	sWindow = NULL;
	sRenderer = NULL;

	SDL_Quit();
}

/* ******************************************** */

void SCore::mainLoop()
{
	lFPSTime = SDL_GetTicks();

	while (!bQuitGame && sEvent->type != SDL_QUIT)
	{
		frameTime = SDL_GetTicks();

		SDL_PollEvent(sEvent);                       // 다중 EVENT를 처리하고 싶다면, While(SDL_PollEvent(sEvent) != 0)){ } 으로 바꿔야함.
		SDL_SetRenderDrawColor(sRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(sRenderer);

		// 배경설정 및 입력, 업데이트, draw START

		/*
		MouseInput(); // 상황에 따라 Input과 MouseInput을 합쳐도 됨
		*/
		Input();
		Update();
		Draw();
		
		// 배경설정 및 입력, 업데이트, draw END

		// Frame 출력 START
		printf("FPS: %d\n", iNumofFPS);
		if (SDL_GetTicks() - 1000 >= lFPSTime)
		{
			lFPSTime = SDL_GetTicks();
			iNumofFPS = iFPS;
			iFPS = 0;
		}
		++iFPS;
		// FRAME 출력 END

		SDL_RenderPresent(sRenderer);

		// Frame 맞추기 START
		if (SDL_GetTicks() - frameTime < MIN_FRAME_TIME)
		{
			SDL_Delay(MIN_FRAME_TIME - (SDL_GetTicks() - frameTime));
		}
		// Frame 맞추기 END
	}
}

void SCore::Input()
{
	// 창이 내려갔을 경우 어떻게 할지.
	if (sEvent->type == SDL_WINDOWEVENT)
	{
		switch (sEvent->window.event)
		{
		case SDL_WINDOWEVENT_FOCUS_LOST:
			break;
		}
	}

	if (sEvent->type == SDL_KEYUP)
	{
		if (sEvent->key.keysym.sym == SInfo::KeyIDRight)
		{
			bRight_Key = false;
		}

		if (sEvent->key.keysym.sym == SInfo::KeyIDLeft)
		{
			bLeft_Key = false;
		}

		if (sEvent->key.keysym.sym == SInfo::KeyIDAlt)
		{
			SInfo::KeyAlt = false;
		}

		if (sEvent->key.keysym.sym == SInfo::KeyIDCtrl)
		{

		}

	}

	if (sEvent->type == SDL_KEYDOWN)
	{
		if (sEvent->key.keysym.sym == SInfo::KeyIDRight)
		{
			bRight_Key = true;
		}

		if (sEvent->key.keysym.sym == SInfo::KeyIDLeft)
		{
			bLeft_Key = true;
		}
		
		if (sEvent->key.keysym.sym == SInfo::KeyIDAlt)
		{
			if (!SInfo::KeyAlt)
			{
				SInfo::KeyAlt = true;
				oMap->getPlayer()->Jump();
			}
		}
		if (sEvent->key.keysym.sym == SInfo::KeyIDCtrl)
		{
				oMap->getPlayer()->hit();
		}

		switch (sEvent->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			// 메뉴버튼이 안눌려있고 && 현재 상태가 게임플레이 상태일 때
			if (!bMenuPressed && SInfo::getMM()->getStateID() == SInfo::getMM()->eGame)
			{
				SInfo::getMM()->setStateID(SInfo::getMM()->ePause);
				bMenuPressed = true;
			}
			else
			{
				SInfo::getMM()->setStateID(SInfo::getMM()->eGame);
				bMenuPressed = false;
			}
			break;
		default:
			break;
		}
	}

	// 오른쪽 키가 눌렸다면
	if (bRight_Key)
	{
		// 왼쪽 보고 있었다면
		if (!bLeft_Right)
		{
			bLeft_Right = true;  // 오른쪽으로
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection_X(bLeft_Right);
			
		}
		// 똑같이 오른쪽으로 간다면
		else if(!oMap->getPlayer()->getMove())
		{
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection_X(bLeft_Right);
		}
	}
	
	// 왼쪽 키가 눌렸다면
	if (bLeft_Key)
	{
		// 오른쪽 보고 있었다면
		if (bLeft_Right)
		{
			bLeft_Right = false;   // 왼쪽으로
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection_X(bLeft_Right);
			
		}
		else if (!oMap->getPlayer()->getMove())
		{
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection_X(bLeft_Right);
		}
	}


	if (oMap->getPlayer()->getMove() && !bRight_Key && !bLeft_Key )
	{
		oMap->getPlayer()->stopMove();
	}
}

void SCore::Update()
{
	oMap->Update();
}

void SCore::Draw()
{
	//--
	oMap->Draw(sRenderer);
	
	if (bMenuPressed) 
	{
		oMap->DrawMenu(sRenderer);
	}
}

Map* SCore::getMap() { return SCore::oMap; }	//--