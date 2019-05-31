#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

GameObject *Camera::focus = nullptr;
Vec2 Camera::pos = Vec2();
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
  if (focus != nullptr) {
    int screenWidth, screenHeight; // TODO: Maybe save on Game
    SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &screenWidth, &screenHeight);
    pos.x = focus->box.GetCenter().x - screenWidth / 2.0;
    pos.y = focus->box.GetCenter().y - screenHeight / 2.0;
  } else {
    if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
			pos.y -= speed.y*dt;
		if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
			pos.y += speed.y*dt;
		if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
			pos.x -= speed.x*dt;
		if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
			pos.x += speed.x*dt;
  }

  HandleFlicker(dt);
}

GameObject *Camera::GetFocus() {
  return focus;
}

void Camera::AddBlack() {
  GameObject *blackGO = new GameObject();
  black = new Sprite(*blackGO, "img/black.png");
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
      if (flickerFrequencyTimer.Get() < flickerFrequency) {
        black->Activate();
      } else {
        black->Desactivate();
        flickerFrequencyTimer = Timer();
      }
    } else {
      black->Desactivate();
      isFlickering = false;
    }
  }
}