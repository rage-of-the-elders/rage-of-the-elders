#include "Vec2.h"
#include <cmath>

Vec2::Vec2() {
  this->x = 0.0;
  this->y = 0.0;
}

Vec2::Vec2(float x, float y) {
  this->x = x;
  this->y = y;
}

float Vec2::Cos(float angle) {
	return cos(angle * (PI / 180.0));
}

float Vec2::Sin(float angle) {
	return sin(angle * (PI/180.0));
}

Vec2 Vec2::Rotate(float angle){
	return Vec2(x + 200 * cos(angle), y + 200 * sin(angle));
}

// Vec2 Vec2::Rotate(float angle) {
// 	return Vec2(x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle));
// }

Vec2 Vec2::operator+(const Vec2& other) const {
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator+(const float other) const {
	return Vec2(x + other, y + other);
}

Vec2 Vec2::operator-(const Vec2& other) const {
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator-(const float other) const {
	return Vec2(x - other, y - other);
}

Vec2 Vec2::operator*(const float other) const {
	return Vec2(x * other, y * other);
}