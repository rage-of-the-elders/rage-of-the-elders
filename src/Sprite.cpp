#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(GameObject &associated) : Component(associated) {
  texture = nullptr;
}

Sprite::Sprite(GameObject &associated, std::string file) : Sprite(associated) {
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
  associated.box.w = GetWidth();
  associated.box.h = GetHeight();
}

void Sprite::SetClip(int x, int y, int w, int h) {
  clipRect = SDL_Rect {x, y, w, h};
}

void Sprite::Render() {
  Render(associated.box.x, associated.box.y, clipRect.w, clipRect.h);
}

void Sprite::Render(int x, int y, int w, int h) {
  SDL_Rect dstRect = SDL_Rect{ x, y, w, h };
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

void Sprite::Update(float dt) {
}

bool Sprite::Is(std::string type) {
  return type == "Sprite";
}
