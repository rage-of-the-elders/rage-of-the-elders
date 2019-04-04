#include "Sound.h"

Sound::Sound(GameObject &associated) {
  this->associated = associated;
  this->chunk = nullptr;
}

Sound::Sound(GameObject &associated, std::string file) : Sound(associated) {
  this->Open(file);
}

Sound::~Sound() {
  if (this->chunk != nullptr) {
    this->Stop();
    Mix_FreeChunk(this->chunk);
    this->chunk = nullptr;
  }
}

void Sound::Play(int times) {
  int loops = times - (times > 0 ? 1 : 0);

  this->channel = Mix_PlayChannel(-1, this->chunk, loops);

  if (this->channel == -1) {
		printf("Mix Play Channel: %s\n", Mix_GetError());
		exit(-1);
	}
}

void Sound::Stop() {
  if (this->chunk != nullptr)
    Mix_HaltChannel(this->channel);
}

void Sound::Open(std::string file) {
  this->chunk = Mix_LoadWAV(file.c_str());

  if (not chunk) {
    printf("Mix Load WAV: %s\n", Mix_GetError());
    exit(-1);
  }
}

bool IsOpen();
void Update(float dt);
void Render();
bool Is(std::string type);

