#include "Game.h"
#include "Resources.h"

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable = std::unordered_map<std::string, SDL_Texture *>();
std::unordered_map<std::string, Mix_Music *> Resources::musicTable = std::unordered_map<std::string, Mix_Music *>();
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable = std::unordered_map<std::string, Mix_Chunk *>();

SDL_Texture *Resources::GetImage(std::string file) {
  if (imageTable.find(file) == imageTable.end()) {
    SDL_Texture *texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), (ASSETS_PATH + file).c_str());

    if (texture == nullptr) {
      printf("IMG Load Texture: %s\n", SDL_GetError());
      exit(-1);
    }
    imageTable.emplace(file, texture);
  }

  return imageTable[file];
}

void Resources::ClearImages() {
  for(auto texture : imageTable)
    SDL_DestroyTexture(texture.second);

  imageTable.clear();
}

Mix_Music *Resources::GetMusic(std::string file) {
  if (musicTable.find(file) == musicTable.end()) {
    Mix_Music *music = Mix_LoadMUS((ASSETS_PATH + file).c_str());

    if (music == nullptr) {
      printf("Open music: %s\n", Mix_GetError());
      exit(-1);
    }
    musicTable.emplace(file, music);
  }

  return musicTable[file];
}

void Resources::ClearMusics() {
  for (auto music : musicTable)
    Mix_FreeMusic(music.second);

  musicTable.clear();
}

Mix_Chunk *Resources::GetSound(std::string file) {
  if (soundTable.find(file) == soundTable.end()) {
    Mix_Chunk *chunk = Mix_LoadWAV((ASSETS_PATH + file).c_str());

    if (not chunk) {
      printf("Mix Load WAV: %s\n", Mix_GetError());
      exit(-1);
    }

    soundTable.emplace(file, chunk);
  }

  return soundTable[file];
}

void Resources::ClearSounds() {
  for (auto sound : soundTable)
    Mix_FreeChunk(sound.second);

  soundTable.clear();
}

void Resources::Clear() {
  ClearImages();
  ClearMusics();
  ClearSounds();
}