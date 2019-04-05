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