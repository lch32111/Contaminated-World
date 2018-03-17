#include "header.h"
#include "Core.h"
#include "CIMG.h"
#include <SDL_mixer.h>

// Static initialization start
AssetManager* SCore::oAssetManager;
SInfo* SCore::oSInfo;
Map* SCore::oMap;
bool SCore::bQuitGame = false;
bool SCore::bClick = false;
bool SCore::bTextInputActive = false;
// Static initialization end

/* ******************************************** */
SCore::SCore(void)
{
	this->bQuitGame = false;
	this->iFPS = 0;
	this->iNumofFPS = 0;
	this->lFPSTime = 0;

	this->bRight_Key = this->bLeft_Key = false;
	this->bKeypressed = this->bMousePressed = false;
	this->bMenuPressed = false;
	this->bMouseLeftClick = false;
	this->mouseState = 0;
	this->mouseXpos = this->mouseYpos = 0;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize // Core.cpp // Error : %s\n", SDL_GetError());
		bQuitGame = true;
	}
	else
	{
		sWindow = SDL_CreateWindow("Contaminated_World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SInfo::SCREEN_WIDTH, SInfo::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (sWindow == NULL)
		{
			printf("sWindow creation fail // Core.cpp // Error : %s\n", SDL_GetError());
			bQuitGame = true;
		}

		sRenderer = SDL_CreateRenderer(sWindow, -1, SDL_RENDERER_ACCELERATED);
		if (sRenderer == NULL)
		{
			printf("sRenderer creation fail // Core.cpp // Error : %s\n", SDL_GetError());
			bQuitGame = false;
		}
		else
		{
			sEvent = new SDL_Event();
			oAssetManager = new AssetManager(sRenderer);
			oSInfo = new SInfo("SInfo");
			oMap = new Map("Map");

			// �������� �͵� �ʱ�ȭ START
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("Audio Initialization fail // Core.cpp // Error : %s\n", SDL_GetError());
				bQuitGame = false;
			}

			SInfo::getMusic()->PlayMusic();

			// �������� �͵� �ʱ�ȭ END
			SInfo::KeyIDA = SDLK_a;
			SInfo::KeyIDD = SDLK_d;
			SInfo::KeyIDShift = SDLK_LSHIFT;
			SInfo::KeyIDSpace = SDLK_SPACE;
			SInfo::KeyIDB = SDLK_b;
			SInfo::KeySpace = false;
			SInfo::KeyShift = false;
		}
	}
}

SCore::~SCore(void)
{
	delete oMap;
	delete oSInfo;
	delete oAssetManager;
	delete sEvent;
	
	SDL_DestroyRenderer(sRenderer);
	SDL_DestroyWindow(sWindow);
	sWindow = NULL;
	sRenderer = NULL;

	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
}

/* ******************************************** */

void SCore::mainLoop()
{
	lFPSTime = SDL_GetTicks();

	while (!bQuitGame && sEvent->type != SDL_QUIT)
	{
		frameTime = SDL_GetTicks();

		SDL_SetRenderDrawColor(sRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(sRenderer);
		
		// ��漳�� �� �Է�, ������Ʈ, draw START
		while (SDL_PollEvent(sEvent) != 0)
		{
			MouseInput();
			KeyboardInput();
		}
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

void SCore::MouseInput()
{
	switch (SInfo::getMM()->getStateID())
	{
	case MenuManager::gameState::eMainMenu: 
	case MenuManager::gameState::ePause:
	case MenuManager::gameState::eOption:
	case MenuManager::gameState::eRanking:
	case MenuManager::gameState::eUpgradeUI:
	case MenuManager::gameState::eEnding:
		MenuMouseInput();
		break;
	case MenuManager::gameState::eGame:
		PlayMouseInput();
		break;
	default:
		break;
	}
}

void SCore::MenuMouseInput()
{
	uint32_t mouseState;
	mouseState = sEvent->button.button;
	SDL_GetMouseState(&mouseXpos, &mouseYpos);
	if (!bKeypressed && (sEvent->type == SDL_MOUSEMOTION || sEvent->type == SDL_MOUSEBUTTONDOWN || sEvent->type == SDL_MOUSEBUTTONUP))
		SInfo::getMM()->checkMouseInput(mouseXpos, mouseYpos);


	switch (sEvent->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (!bClick && mouseState == SDL_BUTTON_LEFT)
		{
			SInfo::getMM()->click(mouseXpos, mouseYpos);
			bClick = true;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		if (mouseState == SDL_BUTTON_LEFT)
			bClick = false;
		break;
	case SDL_MOUSEWHEEL:

		if (sEvent->wheel.y == 1) // Scroll Up
		{
			SInfo::getMM()->keyPressed(0);
		}
		else if (sEvent->wheel.y == -1) // Scroll Down
		{
			SInfo::getMM()->keyPressed(1);
		}

		break;
	}
}

void SCore::PlayMouseInput()
{
	uint32_t mouseState;
	mouseState = sEvent->button.button;
	SDL_GetMouseState(&mouseXpos, &mouseYpos);

	switch (sEvent->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			if(mouseState == SDL_BUTTON_LEFT)
				if (!bClick)
				{
					bMouseLeftClick = true;
					// ����Ŭ���ϰ��
					if (sEvent->button.clicks == 2)
						bDoubleClick = true;
				}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			if (bClick)
				bClick = false;
			else
				if (mouseState == SDL_BUTTON_LEFT)
				{
					if (bDoubleClick)
							bDoubleClick = false;

					bMouseLeftClick = false;
				}		
		break;
		}
	}

	if (bMouseLeftClick)
	{
		// ����Ŭ���� ��ų ()
		if (bDoubleClick)
		{

		}
		
		// �Ϲ�Ŭ���� �Ϲ� ����(hit)
		if (oMap->getPlayer()->getHitState() == 1) // �����ϰ� ���� �ʴٸ�
		{
			oMap->getPlayer()->hit(mouseXpos, mouseYpos);
		}
	}
}


void SCore::KeyboardInput()
{
	switch (SInfo::getMM()->getStateID())
	{
	case MenuManager::gameState::eMainMenu:
	case MenuManager::gameState::ePause:
	case MenuManager::gameState::eOption:
	case MenuManager::gameState::eRanking:
	case MenuManager::gameState::eTitle:
	case MenuManager::gameState::eUpgradeUI:
		InputMenu();
		break;
	case MenuManager::gameState::eEnding:
		KeyboardInputEnding();
		break;
	case MenuManager::gameState::eGame:
		InputPlay();
		break;
	}
}

void SCore::InputMenu()
{
	if (sEvent->type == SDL_KEYDOWN)
	{
		if (!bMenuPressed)
		{
			bMenuPressed = true;
			switch (sEvent->key.keysym.sym)
			{
				// right key:0, bottom:1, left:2, up:3
			case SDLK_UP:
				SInfo::getMM()->keyPressed(0);
				break;
			case SDLK_DOWN:
				SInfo::getMM()->keyPressed(1);
				break;
			case SDLK_LEFT:
				SInfo::getMM()->keyPressed(2);
				break;
			case SDLK_RIGHT:
				SInfo::getMM()->keyPressed(3);
				break;
			case SDLK_RETURN:   case SDLK_KP_ENTER:
				SInfo::getMM()->enter();
				break;
			case SDLK_ESCAPE:
				SInfo::getMM()->escape();
				break;
			}
		}
	}

	if (sEvent->type == SDL_KEYUP)
	{
		switch (sEvent->key.keysym.sym)
		{
		case SDLK_RIGHT:  case SDLK_LEFT: case SDLK_DOWN: case SDLK_UP: case SDLK_RETURN:  case SDLK_KP_ENTER:  case SDLK_ESCAPE:
			bMenuPressed = false;
			break;
		}
	}

}

void SCore::KeyboardInputEnding()
{
	if (bTextInputActive)
	{
		switch (sEvent->type)
		{
		case SDL_KEYDOWN:
			if (sEvent->key.keysym.sym == SDLK_BACKSPACE)
			{
				SInfo::getMM()->eraseText();
			}
			break;
		case SDL_TEXTINPUT:
			SInfo::getMM()->passTextInput(sEvent->text.text);
			break;
		}
	}
	else
	{
		if (sEvent->type == SDL_KEYDOWN)
		{
			if (!bMenuPressed)
			{
				bMenuPressed = true;
				switch (sEvent->key.keysym.sym)
				{
					// right key:0, bottom:1, left:2, up:3
				case SDLK_UP:
					SInfo::getMM()->keyPressed(0);
					break;
				case SDLK_DOWN:
					SInfo::getMM()->keyPressed(1);
					break;
				case SDLK_RETURN:   case SDLK_KP_ENTER:
					SInfo::getMM()->enter();
					break;
				case SDLK_ESCAPE:
					SInfo::getMM()->escape();
					break;
				default:
					break;
				}
			}
		}

		if (sEvent->type == SDL_KEYUP)
		{
			switch (sEvent->key.keysym.sym)
			{
			case SDLK_RIGHT:  case SDLK_LEFT: case SDLK_DOWN: case SDLK_UP: case SDLK_RETURN:  case SDLK_KP_ENTER:  case SDLK_ESCAPE:
				bMenuPressed = false;
				break;
			}
		}
	}
}


void SCore::InputPlay()
{
	// â�� �������� ��� ��� ����.
	if (sEvent->type == SDL_WINDOWEVENT)
	{
		switch (sEvent->window.event)
		{
		case SDL_WINDOWEVENT_FOCUS_LOST:
		{
			/*
			SInfo::getMM()->setStateID(SInfo::getMM()->ePause);
			SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cpause);
			bMenuPressed = true;
			bRight_Key = false;
			bLeft_Key = false;
			SInfo::KeyAlt = false;
			break;
			*/
		}
		}
	}

	if (sEvent->type == SDL_KEYUP)
	{
		if (sEvent->key.keysym.sym == SInfo::KeyIDD)
		{
			bRight_Key = false;
		}

		if (sEvent->key.keysym.sym == SInfo::KeyIDA)
		{
			bLeft_Key = false;
		}

		if (sEvent->key.keysym.sym == SInfo::KeyIDSpace)
		{
			if(SInfo::KeySpace)
				SInfo::KeySpace = false;
		}

		if (sEvent->key.keysym.sym == SInfo::KeyIDShift)
		{
			if (SInfo::KeyShift)
			{
				oMap->getPlayer()->stopRun();
				SInfo::KeyShift = false;
			}
		}

		switch (sEvent->key.keysym.sym)
		{
		case SDLK_ESCAPE:   case SDLK_RETURN:  case SDLK_KP_ENTER:
			bMenuPressed = false;
			break;
		}

	}

	if (sEvent->type == SDL_KEYDOWN)
	{
		if (sEvent->key.keysym.sym == SInfo::KeyIDD)
		{
			bRight_Key = true;
		}

		if (sEvent->key.keysym.sym == SInfo::KeyIDA)
		{
			bLeft_Key = true;
		}
		
		if (sEvent->key.keysym.sym == SInfo::KeyIDSpace)
		{
			if (!SInfo::KeySpace)
			{
				SInfo::KeySpace = true;
				oMap->getPlayer()->Jump();
			}
		}

		if (sEvent->key.keysym.sym == SInfo::KeyIDShift)
		{
			if (!SInfo::KeyShift)
			{
				oMap->getPlayer()->startRun();
				SInfo::KeyShift = true;
			}
		}

		if (sEvent->key.keysym.sym == SInfo::KeyIDB)
		{
			SCore::getMap()->getPlayer()->changeWeapon();
		}

		switch (sEvent->key.keysym.sym)
		{
		case SDLK_ESCAPE:
		{
			// �޴���ư�� �ȴ����ְ� && ���� ���°� �����÷��� ������ ��
			if (!bMenuPressed && SInfo::getMM()->getStateID() == SInfo::getMM()->eGame)
			{
				SInfo::getMM()->setStateID(SInfo::getMM()->ePause);
				SInfo::getMusic()->PlayChunk(SInfo::getMusic()->cpause);
				bMenuPressed = true;
				bRight_Key = false;
				bLeft_Key = false;
				SInfo::KeySpace = false;
			}
			break;
		}
		}
	}

	// ������ Ű�� ���ȴٸ�
	if (bRight_Key)
	{
		// �����̰� ���� ���� ���¶��
		if (!oMap->getPlayer()->getMove())
			oMap->getPlayer()->startMove();

		// ������ ���� �־��� && ����Ű�� �ȴ��� ���¶��
		if (!oMap->getPlayer()->getRotate() && !bLeft_Key)
			oMap->getPlayer()->setDirectionChanged(true);
	}
	
	// ���� Ű�� ���ȴٸ�
	if (bLeft_Key)
	{
		// �����̰� ���� ���� ���¶��
		if (!oMap->getPlayer()->getMove())
			oMap->getPlayer()->startMove();

		// ������ ���� �־��� && ������Ű�� �ȴ��� ���¶��
		if (oMap->getPlayer()->getRotate() && !bRight_Key)
			oMap->getPlayer()->setDirectionChanged(true);
	}


	if (oMap->getPlayer()->getMove() && !bRight_Key && !bLeft_Key)
		oMap->getPlayer()->stopMove();

	// upgradeUI ���·� ������ �� true���¿��� keypressedȮ�� �������� false�� �������ش�.
	if (SInfo::getMM()->getUpgradeUI()->get_bResetKeypressed())
	{
		bRight_Key = false;
		bLeft_Key = false;
		SInfo::KeySpace = false;
		SInfo::KeyShift = false;
		SInfo::getMM()->getUpgradeUI()->set_bResetKeypressed(false);
	}
}

void SCore::Update()
{
	SInfo::getMM()->Update();
}

void SCore::Draw()
{
	SInfo::getMM()->Draw(sRenderer);
}

void SCore::startTextInput()
{
	bTextInputActive = true;
	SDL_StartTextInput();
}

void SCore::stopTextInput()
{
	bTextInputActive = false;
	SDL_StopTextInput();
}


Map* SCore::getMap() { return oMap; }
AssetManager* SCore::getAssetManager() { return oAssetManager; }
