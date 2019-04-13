#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

GameObject *Camera::focus = nullptr;
Vec2 Camera::pos = Vec2();
Vec2 Camera::speed = Vec2(200, 200);

void Camera::Follow(GameObject *newFocus) {
  focus = newFocus;
}

void Camera::Unfollow() {
  focus = nullptr;
}

void Camera::Update(float dt) {
  if (focus != nullptr) {
    if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
      focus->box.y -= speed.y;
    if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
      focus->box.y += speed.y;
    if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
      focus->box.x -= speed.x;
    if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
      focus->box.x += speed.x;

    int screenWidth, screenHeight;
    SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &screenWidth, &screenHeight);
    pos.x = focus->box.GetCenter().x;
    pos.y = focus->box.GetCenter().y;
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
}

GameObject *Camera::GetFocus() {
  return focus;
}
