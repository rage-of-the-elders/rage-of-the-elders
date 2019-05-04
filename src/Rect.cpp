#include "Rect.h"

Rect::Rect() {
  this->x = 0.0;
  this->y = 0.0;
  this->w = 0.0;
  this->h = 0.0;
}

Rect::Rect(float x, float y, float w, float h) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

bool Rect::Contains(float pX, float pY) {
  return ((pX > x) && (pX < (x + w)) && (pY > y) && (pY < (y + h)));
}

Vec2 Rect::GetCenter() {
  return Vec2((x + w/2.0), (y + h/2.0));
}

Vec2 Rect::GetPos() {
  return Vec2(x, y);
}

void Rect::SetPos(float x, float y) {
	this->x = x;
	this->y = y;
}

void Rect::SetPos(Vec2 pos) {
	x = pos.x;
	y = pos.y;
}

void Rect::SetCenterPos(float centerX, float centerY) {
  this->SetPos((centerX - w / 2), (centerY - h / 2));
}

void Rect::SetCenterPos(Vec2 center) {
  this->SetPos((center.x - w / 2), (center.y - h / 2));
}
