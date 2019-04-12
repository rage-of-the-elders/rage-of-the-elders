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
    puts("foco");
    if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
      focus->box.y -= speed.y * dt;
    if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
      focus->box.y += speed.y * dt;
    if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
      focus->box.x -= speed.x * dt;
    if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
      focus->box.x += speed.x * dt;

    int w, h;
    SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &w, &h);
    pos.x = focus->box.GetCenter().x - w / 2;
    pos.y = focus->box.GetCenter().y - h / 2;
  } else {
    puts("ñ foco");
    // printf("%f\n", dt);
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
