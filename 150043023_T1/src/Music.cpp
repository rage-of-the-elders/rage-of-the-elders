#include "Music.h"

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

void Music::Play(int times = -1) {
  int mixPlayMusic = Mix_PlayMusic(music, times);
  if (mixPlayMusic) {
    printf("Play music: %s\n", Mix_GetError());
    exit(-1);
  }
};

void Music::Stop(int msToStop = 1500) {
  int mixFadeOutMusic = Mix_FadeOutMusic(msToStop);
  if (!mixFadeOutMusic) {
    printf("Stop music: %s\n", Mix_GetError());
    exit(-1);
  }
};

void Music::Open(std::string file) {
  Mix_Music *mixMusic = Mix_LoadMUS((RES_PATH + file).c_str());
  if (mixMusic == nullptr) {
    printf("%s: %s\n", Mix_GetError());
    exit(-1);
  }
};

bool Music::IsOpen() {
  return music != nullptr;
};