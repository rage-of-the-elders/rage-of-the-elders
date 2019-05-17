#include "Game.h"
#include "Resources.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable = std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>();
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable = std::unordered_map<std::string, std::shared_ptr<Mix_Music>>();
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable = std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>();
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable = std::unordered_map<std::string, std::shared_ptr<TTF_Font>>();

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
  if (imageTable.find(file) == imageTable.end()) {
    SDL_Texture *t = IMG_LoadTexture(Game::GetInstance().GetRenderer(), (ASSETS_PATH + file).c_str());

    if (t == nullptr) {
      printf("IMG Load Texture: %s\n", SDL_GetError());
      exit(-1);
    }

    std::shared_ptr<SDL_Texture> texture(t, [](SDL_Texture *pTexture) { SDL_DestroyTexture(pTexture); });

    imageTable.emplace(file, texture);
  }

  return imageTable[file];
}

void Resources::ClearImages() {
  for(auto texture : imageTable)
    if (texture.second.unique())
      imageTable.erase(texture.first);
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
  if (musicTable.find(file) == musicTable.end()) {
    Mix_Music *m = Mix_LoadMUS((ASSETS_PATH + file).c_str());

    if (m == nullptr) {
      printf("Open music: %s\n", Mix_GetError());
      exit(-1);
    }

    std::shared_ptr<Mix_Music> music(m, [](Mix_Music *pMus) { Mix_FreeMusic(pMus); });

    musicTable.emplace(file, music);
  }

  return musicTable[file];
}

void Resources::ClearMusics() {
  for (auto music : musicTable)
    if (music.second.unique())
      imageTable.erase(music.first);
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
  if (soundTable.find(file) == soundTable.end()) {
    Mix_Chunk *c = Mix_LoadWAV((ASSETS_PATH + file).c_str());

    if (not c) {
      printf("Mix Load WAV: %s\n", Mix_GetError());
      exit(-1);
    }

    std::shared_ptr<Mix_Chunk> chunk(c, [](Mix_Chunk *pChunk) { Mix_FreeChunk(pChunk); });

    soundTable.emplace(file, chunk);
  }

  return soundTable[file];
}

void Resources::ClearSounds() {
  for (auto sound : soundTable)
    if (sound.second.unique())
      imageTable.erase(sound.first);
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int size) {
  std::string sizeStr = std::to_string(size);

  if (fontTable.find(file + sizeStr) == fontTable.end()) {
    TTF_Font *f = TTF_OpenFont(file.c_str(), size);

    if(f == nullptr){
      printf("TTF_OpenFont: %s\n", SDL_GetError());
      exit(-1);
		}

		std::shared_ptr<TTF_Font> font(f, [](TTF_Font * fnt) { TTF_CloseFont(fnt); });

		fontTable.emplace(file + sizeStr, font);
  }

  return fontTable[file + sizeStr];
}

void Resources::ClearFonts() {
  for (auto font : fontTable)
    if (font.second.unique())
      imageTable.erase(font.first);
}

void Resources::Clear() {
  ClearImages();
  ClearMusics();
  ClearSounds();
  ClearFonts();
}