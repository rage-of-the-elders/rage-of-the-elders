#include "Vec2.h"
#include <cmath>
#include <iostream>

Vec2::Vec2() {
  this->x = 0.0;
  this->y = 0.0;
}

Vec2::Vec2(float xy) {
	this->x = xy;
	this->y = xy;
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

float Vec2::Atan2(float a, float b) {
	return Math::Degrees(atan2(a, b));
}

Vec2 Vec2::Rotate(float distance, float angle) {
	return Vec2(((x + distance) * Cos(angle)) - (y * Sin(angle)), (y * Cos(angle)) + ((x + distance) * Sin(angle)));
}

Vec2 Vec2::Rotate(float angle) {
	return Vec2((x * Cos(angle)) - (y * Sin(angle)), (y * Cos(angle)) + (x * Sin(angle)));
}

Vec2 Vec2::GetSpeed(Vec2 pos) {
	float distance = this->GetDistance(pos);
	if (distance != 0) {
		return Vec2(this->GetDeltaX(pos.x) / distance,
								this->GetDeltaY(pos.y) / distance);
	} else {
		return Vec2();
	}
}

Vec2 Vec2::GetSpeed(float angle) {
	return Vec2(Cos(angle), Sin(angle));
}

float Vec2::GetDeltaX(float targetX) {
	return targetX - this->x;
}

float Vec2::GetDeltaY(float targetY) {
	return targetY - this->y;
}

float Vec2::Module(float x, float y) {
	return std::sqrt(pow(x , 2) + pow(y, 2));
}

Vec2 Vec2::GetNormalized() {
	return (*this) * (1.f / this->GetModule());
}

float Vec2::GetModule() {
	return this->Module(this->x, this->y);
}

float Vec2::GetDistance(Vec2 target) {
	return this->Module(this->GetDeltaX(target.x), this->GetDeltaY(target.y));
}

float Vec2::GetAngle(Vec2 target) {
	return Atan2(this->GetDeltaY(target.y), this->GetDeltaX(target.x));
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