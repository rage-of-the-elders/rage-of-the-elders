#include "Collider.h"
#include "MathHelper.h"

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h> // Shouldn't it be INCLUDE_SDL?
#endif // DEBUG

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated) {
  this->scale = scale;
  this->offset = offset;
  this->active = true;
}

void Collider::Update(float) {
  this->box.SetSize(this->associated.box.w * this->scale.x,
                    this->associated.box.h * this->scale.y);
  this->box.SetCenterPos(Vec2().Rotate(this->associated.angleDeg));
  this->box.SetCenterPos(this->associated.box.GetCenter() + this->offset);
}

void Collider::Render() {
#ifdef DEBUG
  Vec2 center(this->box.GetCenter());
  SDL_Point points[5];

  Vec2 point = (Vec2(this->box.x, this->box.y) - center).Rotate(associated.angleDeg) + center - Camera::position;
  points[0] = {(int)point.x, (int)point.y};
  points[4] = {(int)point.x, (int)point.y};

  point = (Vec2(this->box.x + this->box.w, this->box.y) - center).Rotate(associated.angleDeg) + center - Camera::position;
  points[1] = {(int)point.x, (int)point.y};

  point = (Vec2(this->box.x + this->box.w, this->box.y + this->box.h) - center).Rotate(associated.angleDeg) + center - Camera::position;
  points[2] = {(int)point.x, (int)point.y};

  point = (Vec2(this->box.x, this->box.y + this->box.h) - center).Rotate(associated.angleDeg) + center - Camera::position;
  points[3] = {(int)point.x, (int)point.y};

  SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type) {
  return type == "Collider";
}

void Collider::SetScale(Vec2 scale) {
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
  this->offset = offset;
}
