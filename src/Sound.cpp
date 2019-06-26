#include "Sound.h"
#include "Game.h"
#include "Resources.h"

Sound::Sound(GameObject &associated) : Component (associated) {
  this->chunk = nullptr;
  this->channel = -1;
  this->active = true;
}

Sound::Sound(GameObject &associated, std::string file) : Sound (associated) {
  this->Open(file);
}

Sound::~Sound() {
  this->Stop();
  this->chunk = nullptr;
}

void Sound::Play(int times) {
  int loops = times - (times > 0 ? 1 : 0);
  
  this->channel = Mix_PlayChannel(channel, this->chunk.get(), loops);

  if (this->channel == -1) {
		printf("Mix Play Channel: %s\n", Mix_GetError());
		exit(-1);
	}
}

void Sound::Stop() {
  // TODO: Check that part after
  // if (not IsPlaying()) {
    Mix_HaltChannel(this->channel);
  // }
  this->channel = -1;
  
  // if(IsPlaying())
  //   Mix_HaltChannel(-1);
}

void Sound::Open(std::string file) {
  this->chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() {
  return this->chunk != nullptr;
}

void Sound::Update(float) {}
void Sound::Render() {}

bool Sound::IsPlaying() {
  return (Mix_Playing(this->channel));
}

bool Sound::Is(std::string type) {
  return (type == "Sound");
}

