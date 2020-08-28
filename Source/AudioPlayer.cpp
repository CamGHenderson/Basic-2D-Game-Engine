#include "AudioPlayer.h"

#include<SDL2/SDL.h>

AudioPlayer::AudioPlayer()
{
	error = "";
	if (SDL_Init(SDL_INIT_AUDIO) != -1)
	{
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			error = "Failed To Initialize Audio Device.";
		}
	}
	else
	{
		error = "Failed To Initialize SDL Audio.";
	}
	state = MusicState::stopped;
}

Mix_Music* AudioPlayer::loadMusic(const char* file)
{
	Mix_Music* m = Mix_LoadMUS(file);
	music.push_back(m);
	return m;
}

void AudioPlayer::playMusic(Mix_Music* music, bool loop)
{
	if (state == MusicState::playing)
	{
		pauseMusic();
	}
	else
	{
		state = MusicState::playing;
	}
	if(loop)
		Mix_PlayMusic(music, -1);
	else
		Mix_PlayMusic(music, 0);

}

void AudioPlayer::resumeMusic()
{
	state = MusicState::playing;
	Mix_ResumeMusic();
}

void AudioPlayer::pauseMusic()
{
	state = MusicState::paused;
	Mix_PauseMusic();
}

void AudioPlayer::stopMusic()
{
	state = MusicState::stopped;
	Mix_HaltMusic();
}

void AudioPlayer::setMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

Mix_Chunk* AudioPlayer::loadSound(const char* file)
{
	Mix_Chunk* s = Mix_LoadWAV(file);
	sounds.push_back(s);
	return s;
}

void AudioPlayer::playSound(Mix_Chunk* music)
{
	Mix_PlayChannel(-1 , music, 0);
}

void AudioPlayer::setSoundVolume(Mix_Chunk* sound, int volume)
{
	Mix_VolumeChunk(sound, volume);
}

void AudioPlayer::cleanUp()
{
	stopMusic();
	for (Mix_Music* m : music)
		Mix_FreeMusic(m);
	for (Mix_Chunk* s : sounds)
		Mix_FreeChunk(s);
}