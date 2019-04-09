#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite(GameObject &associated) : Component(associated) {
  this->texture = nullptr;
  this->width = 0;
  this->height = 0;
}

Sprite::Sprite(GameObject &associated, std::string file) : Sprite(associated) {
  texture = nullptr;
  this->Open(file);
}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {
  this->texture = Resources::GetImage(file);

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
  Render(associated.box.x, associated.box.y);
}

void Sprite::Render(int x, int y) {
  SDL_Rect dstRect = SDL_Rect{x, y, clipRect.w, clipRect.h};
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
