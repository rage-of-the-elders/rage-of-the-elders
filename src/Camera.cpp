#include "Game.h"
#include "Camera.h"
#include "InputManager.h"

GameObject *Camera::focus = nullptr;
Vec2 Camera::position = Vec2();
Vec2 Camera::speed = Vec2(100, 100);
bool Camera::isBlack = false;
bool Camera::isFlickering = false;
float Camera::flickerDuration = 0;
float Camera::flickerFrequency = 0;
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
		if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
			position.x -= speed.x*dt;
    }
		if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
			position.x += speed.x*dt;
  }


  // FIXME
  Camera::DefineLimits(0, 12120, screenWidth);
  Camera::HandleFlicker(dt);
}


void Camera::DefineLimits(int initiaLimit, int finalLimit, int screenWidth) {
  if (position.x <= initiaLimit)
    position.x = initiaLimit;
  if (position.x >= finalLimit - screenWidth)
    position.x = finalLimit - screenWidth;
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
