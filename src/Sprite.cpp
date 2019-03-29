#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() {
  texture = nullptr;
}

Sprite::Sprite(std::string file) {
  texture = nullptr;
  this->Open(file);
}

Sprite::~Sprite() {
  if (texture != nullptr)
    SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file) {
  if (this->texture != nullptr) {
    SDL_DestroyTexture(this->texture);
  }

  this->texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), (ASSETS_PATH + file).c_str());

  if (this->texture == nullptr) {
    printf("IMG Load Texture: %s\n", SDL_GetError());
    exit(-1);
  }

  int queryTexture = SDL_QueryTexture(this->texture, nullptr, nullptr, &width, &height);

  if (queryTexture) {
    printf("SDL Query Texture: %s\n", SDL_GetError());
    exit(-1);
  }

  SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
  clipRect = SDL_Rect {x, y, w, h};
}

void Sprite::Render(int x, int y) {
  SDL_Rect dstRect = SDL_Rect {x, y, clipRect.w, clipRect.h};
  SDL_RenderCopy(Game::GetInstance().GetRenderer(),
                 this->texture,
                 &clipRect,
                 &dstRect);
}

int Sprite::GetWidth() {
  return width;
}

int Sprite::GetHeight() {
  return height;
}

bool Sprite::IsOpen() {
  return texture != nullptr;
}