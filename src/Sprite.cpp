#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

#include <iostream>

Sprite::Sprite(GameObject &associated) : Component(associated) {
  this->texture = nullptr;
  this->width = 0;
  this->height = 0;
  this->scale = Vec2(1);
}

Sprite::Sprite(GameObject &associated, std::string file, int frameCount,
               float frameTime, float secondsToSelfDestruct, bool repeat) : Sprite(associated) {
  this->texture = nullptr;
  this->frameCount = frameCount;
  this->frameTime = frameTime;
  this->currentFrame = 0;
  this->timeElapsed = 0;
  this->secondsToSelfDestruct = secondsToSelfDestruct;
  this->selfDestructCount = Timer();
  this->Open(file);
  this->repeat = repeat;
  this->finished = false;
}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {
  this->texture = Resources::GetImage(file);

  int queryTexture = SDL_QueryTexture(this->texture.get(), nullptr, nullptr, &width, &height);

  if (queryTexture) {
    printf("SDL Query Texture: %s\n", SDL_GetError());
    exit(-1);
  }

  SetClip(0, 0, (this->width / this->frameCount), this->height);
  this->associated.box.w = GetWidth();
  this->associated.box.h = GetHeight();
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
                   this->texture.get(),
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
  if (this->secondsToSelfDestruct > 0) {
    this->selfDestructCount.Update(dt);
    if (this->selfDestructCount.Get() > this->secondsToSelfDestruct)
      this->associated.RequestDelete();
  }
  this->timeElapsed += dt;

  if (this->timeElapsed > this->frameTime) {
    this->timeElapsed -= this->frameTime; // "Restarting" the counter
    if(this->currentFrame < this->frameCount -1)
      this->currentFrame++;
    else if(this->repeat)
      this->currentFrame = 0;
    
    this->UpdateFrame();
  
    if(not this->repeat && this->currentFrame == this->frameCount-1){
      this->finished = true;
    }
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

void Sprite::SetFinished(bool finished){
  this->finished = finished;
}

bool Sprite::IsFinished(){
  return this->finished;
}

void Sprite::SetRepeat(bool repeat){
  this->repeat = repeat;
}

bool Sprite::GetRepeat(){
  return this->repeat;
}

void Sprite::Desactivate() {
  this->active = false;
  this->SetFrame(0);
}