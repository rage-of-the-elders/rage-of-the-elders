#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject &associated) : Component(associated) {
  this->texture = nullptr;
  this->width = 0;
  this->height = 0;
  this->scale = Vec2(1);
}

Sprite::Sprite(GameObject &associated, std::string file) : Sprite(associated) {
  this->texture = nullptr;
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
  this->clipRect = SDL_Rect{x, y, w, h};
}

void Sprite::Render() {
  Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

void Sprite::Render(int x, int y) {
  SDL_Rect dstRect = SDL_Rect{x,
                              y,
                              int(clipRect.w * this->scale.x),
                              int(clipRect.h * this->scale.y)};
  SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
                   this->texture,
                   &clipRect,
                   &dstRect,
                   this->associated.angleDeg,
                   nullptr, // Rotates around the center
                   SDL_FLIP_NONE);
}

int Sprite::GetWidth() {
  return this->width * this->scale.x;
}

int Sprite::GetHeight() {
  return this->height * this->scale.y;
}

Vec2 Sprite::GetScale() {
  
}
  
void Sprite::SetScaleX(float scaleX, float scaleY) {
  // TODO: mova a box dele de forma a manter o centro no mesmo lugar de antes da mudança de escala
  this->scale = Vec2(scaleX, scaleY);
  this->associated.box.w = GetWidth();
  this->associated.box.h = GetHeight();
} 

bool Sprite::IsOpen() {
  return this->texture != nullptr;
}

void Sprite::Update(float dt) {
}

bool Sprite::Is(std::string type) {
  return type == "Sprite";
}
