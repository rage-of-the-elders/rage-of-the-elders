#include "Timer.h"

Timer::Timer() {
  this->timer = 0;
}

void Timer::Update(float dt) {
  this->timer += dt;
}

void Timer::Restart() {
  this->timer = 0;
}

float Timer::Get() {
  return this->timer;
}

