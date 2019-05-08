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

Sprite::Sprite(GameObject &associated, std::string file,  int frameCount, float frameTime) : Sprite(associated) {
  this->texture = nullptr;
  this->frameCount = frameCount;
  this->frameTime = frameTime;
  this->currentFrame = 0;
  this->timeElapsed = 0;
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
  return round((this->width/this->frameCount) * this->scale.x);
}

int Sprite::GetHeight() {
  return this->height * this->scale.y;
}

Vec2 Sprite::GetScale() {
  return this->scale;
}
  
void Sprite::SetScaleX(float scale) {
  this->SetScaleX(scale, scale);
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
  // TODO: mova a box dele de forma a manter o centro no mesmo lugar de antes da mudança de escala
  this->scale = Vec2(scaleX, scaleY);
  this->associated.box.w = GetWidth();
  this->associated.box.h = GetHeight();
}

void Sprite::SetFrame(int frame) {
  this->currentFrame = frame;
  this->UpdateFrame();
}

void Sprite::SetFrameCount(int frameCount) {
  this->frameCount = frameCount;
  this->currentFrame = 0;
  this->UpdateFrame(); // TODO: Check this
}

void Sprite::SetFrameTime(float frameTime) {
  this->frameTime = frameTime;
}

bool Sprite::IsOpen() {
  return this->texture != nullptr;
}

void Sprite::Update(float dt) {
  this->timeElapsed += dt;

  if (this->timeElapsed > this->frameTime) {
    this->currentFrame = (this->currentFrame + 1) % this->frameCount; // TODO: Check this
    this->timeElapsed -= this->frameTime; // "Restarting" the counter
    this->UpdateFrame();
  }
}

void Sprite::UpdateFrame() {
  float frameWidth = this->width / this->frameCount;
  this->SetClip(this->currentFrame * frameWidth,
                0,
                frameWidth,
                height);
}

bool Sprite::Is(std::string type) {
  return type == "Sprite";
}
