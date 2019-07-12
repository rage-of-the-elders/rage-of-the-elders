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
	this->x = pos.x;
	this->y = pos.y;
}

void Rect::UpdatePos(Vec2 pos) {
	this->x += pos.x;
	this->y += pos.y;
}

void Rect::UpdatePosY(float y) {
	this->y += y;
}

void Rect::SetXCenter(float centerX) {
  this->x = (centerX - w / 2);
}

void Rect::SetYCenter(float centerY) {
  this->y = (centerY - h / 2);
}

void Rect::SetCenterPos(float centerX, float centerY) {
  this->SetPos((centerX - w / 2), (centerY - h / 2));
}

void Rect::SetCenterPos(Vec2 center) {
  this->SetPos((center.x - w / 2), (center.y - h / 2));
}

Vec2 Rect::GetSize() {
  return Vec2(this->w, this->h);
}

void Rect::SetSize(float w, float h) {
	this->w = w;
	this->h = h;
}

void Rect::SetSize(Vec2 size) {
	SetSize(size.x, size.y);
}
