#include "Music.h"
#include "SDL2/SDL_mixer.h"
#include "Game.h"

Music::Music() {
  music = nullptr;
};

Music::Music(std::string file) {
  this->Open(file);
};

Music::~Music() {
  Stop();
  Mix_FreeMusic(music);
};

void Music::Play(int times) {
  int mixPlayMusic = Mix_PlayMusic(music, times);
  if (mixPlayMusic) {
    printf("Play music: %s\n", Mix_GetError());
    exit(-1);
  }
};

void Music::Stop(int msToStop) {
  int mixFadeOutMusic = Mix_FadeOutMusic(msToStop);
  if (not mixFadeOutMusic) {
    printf("Stop music: %s\n", Mix_GetError());
    exit(-1);
  }
};

void Music::Open(std::string file) {
  Mix_Music *mixMusic = Mix_LoadMUS((RES_PATH + file).c_str());
  if (mixMusic == nullptr) {
    printf("Open music: %s\n", Mix_GetError());
    exit(-1);
  }
};

bool Music::IsOpen() {
  return music != nullptr;
};