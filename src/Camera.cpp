#include "Game.h"
#include "Camera.h"
#include "InputManager.h"

// Static fields
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
  int screenWidth, screenHeight;
  SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &screenWidth, &screenHeight);

  if (focus != nullptr) {
    Camera::AdjustFocus(screenWidth);
  } else {
		if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
			position.x -= speed.x*dt;
		if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
			position.x += speed.x*dt;
  }

  Camera::DefineLimits(screenWidth);
  Camera::HandleFlicker(dt);
}

void Camera::DefineLimits(int screenWidth) {
  if(position.x <= Camera::initiaCameraLimit)
    position.x = Camera::initiaCameraLimit;
  if(Camera::finalCameraLimit <= screenWidth)
    Camera::finalCameraLimit = screenWidth;
  if (position.x >= Camera::finalCameraLimit - screenWidth)
    position.x = Camera::finalCameraLimit - screenWidth;
}

void Camera::AdjustFocus(int screenWidth) {
  position.x = focus->box.GetCenter().x - (screenWidth / 2);
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
      black->Desactivate();
      isFlickering = false;
    }
  }
}
