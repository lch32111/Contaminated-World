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
	this->bLeft_Right =  true; // ĳ���ʹ� �������� ���ϵ���
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

			// �������� �͵� �ʱ�ȭ START
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("Audio Initialization fail // Core.cpp // Error : %s", SDL_GetError());
				bQuitGame = false;
			}


			// �������� �͵� �ʱ�ȭ END
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

		SDL_PollEvent(sEvent);                       // ���� EVENT�� ó���ϰ� �ʹٸ�, While(SDL_PollEvent(sEvent) != 0)){ } ���� �ٲ����.
		SDL_SetRenderDrawColor(sRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(sRenderer);

		// ��漳�� �� �Է�, ������Ʈ, draw START

		/*
		MouseInput(); // ��Ȳ�� ���� Input�� MouseInput�� ���ĵ� ��
		*/
		Input();
		Update();
		Draw();
		
		// ��漳�� �� �Է�, ������Ʈ, draw END

		// Frame ��� START
		printf("FPS: %d\n", iNumofFPS);
		if (SDL_GetTicks() - 1000 >= lFPSTime)
		{
			lFPSTime = SDL_GetTicks();
			iNumofFPS = iFPS;
			iFPS = 0;
		}
		++iFPS;
		// FRAME ��� END

		SDL_RenderPresent(sRenderer);

		// Frame ���߱� START
		if (SDL_GetTicks() - frameTime < MIN_FRAME_TIME)
		{
			SDL_Delay(MIN_FRAME_TIME - (SDL_GetTicks() - frameTime));
		}
		// Frame ���߱� END
	}
}

void SCore::Input()
{
	// â�� �������� ��� ��� ����.
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
			// �޴���ư�� �ȴ����ְ� && ���� ���°� �����÷��� ������ ��
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

	// ������ Ű�� ���ȴٸ�
	if (bRight_Key)
	{
		// ���� ���� �־��ٸ�
		if (!bLeft_Right)
		{
			bLeft_Right = true;  // ����������
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection_X(bLeft_Right);
			
		}
		// �Ȱ��� ���������� ���ٸ�
		else if(!oMap->getPlayer()->getMove())
		{
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection_X(bLeft_Right);
		}
	}
	
	// ���� Ű�� ���ȴٸ�
	if (bLeft_Key)
	{
		// ������ ���� �־��ٸ�
		if (bLeft_Right)
		{
			bLeft_Right = false;   // ��������
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