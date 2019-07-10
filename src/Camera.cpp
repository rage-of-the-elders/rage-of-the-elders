#define FOCUS_ADJUSTMENT -6

#include "Game.h"
#include "Camera.h"
#include "InputManager.h"

int Camera::finalCameraLimit = 0;
int Camera::initiaCameraLimit = 0;

bool Camera::isBlack = false;
bool Camera::isFlickering = false;

float Camera::flickerDuration = 0;
float Camera::flickerFrequency = 0;

Vec2 Camera::position = Vec2();
Vec2 Camera::speed = Vec2(100, 100);

GameObject *Camera::focus = nullptr;

Timer Camera::flickerTimer = Timer();
Timer Camera::flickerFrequencyTimer = Timer();

Sprite *Camera::black = nullptr;

CameraFollower *Camera::blackFollower = nullptr;

void Camera::Follow(GameObject *newFocus) {
  focus = newFocus;
}

void Camera::Unfollow() {
  focus = nullptr;
}

void Camera::Update(float dt) {
  if (focus != nullptr) {
    Camera::AdjustFocus();
  } else {
		if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
			position.x -= speed.x*dt;
		if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
			position.x += speed.x*dt;
  }

  Camera::DefineLimits();
  Camera::HandleFlicker(dt);
}

void Camera::DefineLimits() {
  if(position.x <= Camera::initiaCameraLimit)
    position.x = Camera::initiaCameraLimit;
  if(Camera::finalCameraLimit <= Game::screenWidth)
    Camera::finalCameraLimit = Game::screenWidth;
  if (position.x >= Camera::finalCameraLimit - Game::screenWidth)
    position.x = Camera::finalCameraLimit - Game::screenWidth;
}

void Camera::AdjustFocus() {
  float diference = position.x - focus->box.GetCenter().x + (Game::screenWidth / 2);
  position.x += diference / FOCUS_ADJUSTMENT;
}

GameObject *Camera::GetFocus() {
  return focus;
}

void Camera::AddBlack() {
  GameObject *blackGO = new GameObject();
  black = new Sprite(*blackGO, "img/orange.png");
  blackGO->AddComponent(black);
  blackFollower = new CameraFollower(*blackGO);
  black->Desactivate();
}

void Camera::RenderBlack() {
  if (black == nullptr)
      AddBlack();

  if (black->IsActive()) {
    black->Render();
  }
}

void Camera::Flicker(float duration, float frequency) {
  if (not isFlickering) {
    flickerTimer = Timer();
    flickerFrequencyTimer = Timer();
    flickerDuration = duration;
    flickerFrequency = frequency;
    isFlickering = true;
  }
}

void Camera::HandleFlicker(float dt) {
  if (isFlickering) {
    flickerTimer.Update(dt);
    flickerFrequencyTimer.Update(dt);
    blackFollower->Update(dt);

    if (flickerTimer.Get() < flickerDuration) {
      if (flickerFrequencyTimer.Get() > flickerFrequency) {
        black->ToggleActive();
        flickerFrequencyTimer = Timer();
      }
    } else {
      // black->Desactivate();
      // isFlickering = false;
      StopFlicker();
    }
  }
}

void Camera::StopFlicker() {
  black->Desactivate();
  isFlickering = false;
}
