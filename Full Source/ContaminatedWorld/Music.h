#pragma once

#ifndef MUSIC_H
#define MUSIC_H

#include <SDL_mixer.h>
#include <vector>

class Music
{
private:
	std::vector<Mix_Music*> vMusic;
	std::vector<Mix_Chunk*> vChunk;

	int iVolume;
	int attackindex;
public:

	bool musicStopped;

	Music();
	~Music();

	enum eMusic
	{
		mNOTHING,
		mTitle,
		mGame,
		mDead
	};

	eMusic currentMusic;

	enum eChunk
	{
		cfireburn,
		cdead,
		cpause,
		cattackmouth,
		cpunch,
		cVolumeControl,
		cswipeUnmute,
		ccoindrop,
		ccoinacquire,
		cstagestart,
		cstageend,
		cBonusSpawn
	};

	void changeMusic();
	void PlayMusic();
	void PlayMusic(eMusic musicID);
	void StopMusic();
	void PauseMusic();

	void PlayChunk(eChunk chunkID);
	void increaseAttackindex();

	Mix_Music* loadMusic(std::string fileName);
	Mix_Chunk* loadChunk(std::string fileName);

	int getVolume();
	void setVolume(int volume);

	void setMusicStopped(bool b);
};

#endif 
