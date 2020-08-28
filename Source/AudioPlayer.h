#pragma once

#include<SDL2/SDL_mixer.h>

#include<vector>

class AudioPlayer
{
private:
	enum class MusicState
	{
		stopped,
		paused,
		playing
	};
	MusicState state;
	std::vector<Mix_Chunk*> sounds;
	std::vector<Mix_Music*> music;
	const char* error;
public:
	AudioPlayer();
	Mix_Music* loadMusic(const char* file);
	void playMusic(Mix_Music* music, bool loop);
	void resumeMusic();
	void pauseMusic();
	void stopMusic();
	void setMusicVolume(int volume);
	Mix_Chunk* loadSound(const char* file);
	void playSound(Mix_Chunk* music);
	void setSoundVolume(Mix_Chunk* sound, int volume);
	void cleanUp();
	const char* getError() { return error; }
};

