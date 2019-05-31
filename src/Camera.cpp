#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

GameObject *Camera::focus = nullptr;
Vec2 Camera::pos = Vec2();
Vec2 Camera::speed = Vec2(1000, 100);

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
    pos.x = focus->box.GetCenter().x;
  } else {
    // if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
		// 	pos.y -= speed.y*dt;
		// if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
		// 	pos.y += speed.y*dt;
		if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
			pos.x -= speed.x*dt;
    }
		if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
			pos.x += speed.x*dt;

    // FIXME
    if (pos.x <= 0)
      pos.x = 0;
    if (pos.x >= 12120 - 1280)
      pos.x = 12120 - 1280;
  }
}

GameObject *Camera::GetFocus() {
  return focus;
}
