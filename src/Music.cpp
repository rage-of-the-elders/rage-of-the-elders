#define INCLUDE_SDL_MIXER

#include "Music.h"
#include "Resources.h"

Music::Music() {
  music = nullptr;
}

Music::Music(std::string file) {
  this->Open(file);
}

Music::~Music() {
  // Stop();
}

void Music::Play(int times) {
  // Mix_VolumeMusic(70);
  int mixPlayMusic = Mix_PlayMusic(music.get(), times);
  if (mixPlayMusic) {
    printf("Play music: %s\n", Mix_GetError());
    exit(-1);
  }
}

void Music::Stop(int msToStop) {
  int mixFadeOutMusic = Mix_FadeOutMusic(msToStop);
  if (not mixFadeOutMusic) {
    printf("Stop music: %s\n", Mix_GetError());
    exit(-1);
  }
}

void Music::Open(std::string file) {
  this->music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
  return music != nullptr;
}