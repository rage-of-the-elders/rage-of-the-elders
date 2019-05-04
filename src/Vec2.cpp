#include "Vec2.h"
#include <cmath>
#include <iostream>

Vec2::Vec2() {
  this->x = 0.0;
  this->y = 0.0;
}

Vec2::Vec2(float x, float y) {
  this->x = x;
  this->y = y;
}

float Vec2::Cos(float angle) {
	return cos(Math::Radians(angle));
}

float Vec2::Sin(float angle) {
	return sin(Math::Radians(angle));
}

float Vec2::Acos(float angle) {
	return (acos(Math::Radians(angle)));
}

Vec2 Vec2::Rotate(float distance, float angle) {
	return Vec2((x + distance) * Cos(angle), (y + distance) * Sin(angle));
}

// Vec2 Vec2::Rotate(float angle) {
// 	return Vec2(x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle));
// }

Vec2 Vec2::GetSpeed(Vec2 pos) {
	float distance = this->GetDistance(pos);
	if (distance != 0) {
		return Vec2(this->GetDeltaX(pos.x) / distance,
								this->GetDeltaY(pos.y) / distance);
	} else {
		return Vec2();
	}
}

float Vec2::GetDeltaX(float targetX) {
	return targetX - this->x;
}

float Vec2::GetDeltaY(float targetY) {
	return targetY - this->y;
}

float Vec2::Module(float x, float y) {
	return sqrt(pow(x , 2) + pow(y, 2));
}

float Vec2::GetDistance(Vec2 target) {
	return this->Module(this->GetDeltaX(target.x), this->GetDeltaY(target.y));
}

float Vec2::GetModule() {
	return this->Module(this->x, this->y);
}

float Vec2::GetAngle(Vec2 target) {
	float angle = ((*this) * target) / (this->GetModule() * target.GetModule());
	return Acos(angle);
}

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
float Vec2::operator*(const Vec2& other) const {
	return (x * other.x) + (y * other.y);
}