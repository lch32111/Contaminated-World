#include "Music.h"
#include "StaticInfo.h"
#include "Core.h"
#include <SDL_mixer.h>

Music::Music()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	vMusic.push_back(loadMusic("mtitle"));
	vMusic.push_back(loadMusic("mforest"));
	vMusic.push_back(loadMusic("mdeath"));
	vMusic.push_back(loadMusic("mGame")); // 3

	vChunk.push_back(loadChunk("cfireburn"));  // 0
	vChunk.push_back(loadChunk("cdeath"));
	vChunk.push_back(loadChunk("cpause"));
	vChunk.push_back(loadChunk("cattackmouth1")); // 3
	vChunk.push_back(loadChunk("cattackmouth2"));
	vChunk.push_back(loadChunk("cattackmouth3"));
	vChunk.push_back(loadChunk("cattackmouth4"));
	vChunk.push_back(loadChunk("cattackmouth5")); // 7
	vChunk.push_back(loadChunk("cpunch1"));       // 8
	vChunk.push_back(loadChunk("cpunch2"));
	vChunk.push_back(loadChunk("cpunch3"));
	vChunk.push_back(loadChunk("cpunch4"));
	vChunk.push_back(loadChunk("cpunch5"));       // 12

	vChunk.push_back(loadChunk("volCtrl"));       // 13
	vChunk.push_back(loadChunk("swipeUnmute"));   

	vChunk.push_back(loadChunk("ccoindrop"));      // 15
	vChunk.push_back(loadChunk("ccoinacquire"));  

	vChunk.push_back(loadChunk("cstagestart"));   // 17
	vChunk.push_back(loadChunk("cstageend")); 
	 
	vChunk.push_back(loadChunk("cbonusspawn")); // 19

	setVolume(100);

	musicStopped = true;
	currentMusic = mTitle;
	attackindex = 0;
}

Music::~Music()
{
	for (unsigned int i = 0; i < vMusic.size(); ++i)
		Mix_FreeMusic(vMusic[i]);
	vMusic.clear();

	for (unsigned int i = 0; i < vMusic.size(); ++i)
		Mix_FreeChunk(vChunk[i]);
	vChunk.clear();
}

void Music::changeMusic()
{
	// Title 또는 메인 메뉴
	if (SInfo::getMM()->getStateID() == 0 || SInfo::getMM()->getStateID() == 1)
	{
		currentMusic = mTitle;
	}
	// 게임중이라면
	else if (SInfo::getMM()->getStateID() == 2)
	{
		currentMusic = mGame;
	}
	// 캐릭터가 죽었고, ending으로 넘어갈 때
	else if (SCore::getMap()->getPlayer()->getCharacterState() == 1 && SInfo::getMM()->getStateID() == 6)
	{
		currentMusic = mDead;
	}
	else
		currentMusic = mNOTHING;
}

void Music::PlayMusic()
{
	if (currentMusic != mNOTHING && musicStopped)
	{
		Mix_PlayMusic(vMusic[currentMusic - 1], -1);
		musicStopped = false;
	}
	else if (currentMusic == mGame)
	{
		Mix_PlayMusic(vMusic[3], -1);
		musicStopped = false;
	}
	else if (currentMusic == mNOTHING)
		StopMusic();
}

void Music::PlayMusic(eMusic musicID)
{
	if (musicID != mNOTHING)
	{
		Mix_PlayMusic(vMusic[musicID - 1], -1);
		musicStopped = false;
		currentMusic = musicID;
	}
	else if (musicID == mGame)
	{
		Mix_PlayMusic(vMusic[musicID + 1], -1);
		musicStopped = false;
	}
	else {
		StopMusic();
		currentMusic = mNOTHING;
	}
}

void Music::StopMusic()
{
	if (!musicStopped)
	{
		Mix_HaltMusic();
		musicStopped = true;
	}
}

void Music::PauseMusic()
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
		musicStopped = false;
	}
	else
	{
		Mix_PauseMusic();
		musicStopped = true;
	}
}

void Music::PlayChunk(eChunk chunkID)
{
	// 공격시 공격 입소리
	if (chunkID == cattackmouth)
	{
		Mix_VolumeChunk(vChunk[chunkID + attackindex], iVolume);
		Mix_PlayChannel(-1, vChunk[chunkID + attackindex], 0);
	}
	// 공격시 펀치 소리
	else if (chunkID == cpunch)
	{
		Mix_VolumeChunk(vChunk[chunkID + 4 + attackindex], iVolume);
		Mix_PlayChannel(-1, vChunk[chunkID + 4 + attackindex], 0);
	}
	// enum chunk volum control부터
	else if ((int)chunkID >= 5)
	{
		Mix_VolumeChunk(vChunk[chunkID + 8], iVolume);
		Mix_PlayChannel(-1, vChunk[chunkID + 8], 0);
	}
	// 그 외
	else
	{
		Mix_VolumeChunk(vChunk[chunkID], iVolume);
		Mix_PlayChannel(-1, vChunk[chunkID], 0);
	}

}

void Music::increaseAttackindex()
{
	if (attackindex >= 4)
		attackindex = 0;
	else
		++attackindex;
}

Mix_Music* Music::loadMusic(std::string fileName)
{
	fileName = "files/sounds/" + fileName + ".wav";
	return Mix_LoadMUS(fileName.c_str());
}

Mix_Chunk* Music::loadChunk(std::string fileName)
{
	fileName = "files/sounds/" + fileName + ".wav";
	return Mix_LoadWAV(fileName.c_str());
}

void Music::setVolume(int volume)
{
	this->iVolume = volume;
	Mix_VolumeMusic(iVolume);
}

int Music::getVolume()
{
	return iVolume;
}

void Music::setMusicStopped(bool b) { this->musicStopped = b; }