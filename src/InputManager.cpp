#define INCLUDE_SDL
#include "SDL_include.h"

#include "InputManager.h"
#include "Camera.h"

#include <cstring>

InputManager::InputManager() {
  memset(this->mouseState, false, sizeof this->mouseState);
  memset(this->mouseUpdate, 0, sizeof this->mouseUpdate);
  this->updateCounter = 0;
  this->quitRequested = false;
  this->mouseX = 0;
  this->mouseY = 0;
}

InputManager::~InputManager() {
}

InputManager &InputManager::GetInstance() {
  static InputManager inputManager;
  return inputManager;
}

void InputManager::Update() {
  SDL_Event event;
  this->updateCounter++;
  this->quitRequested = false;

  SDL_GetMouseState(&this->mouseX, &this->mouseY);
  this->mouseX += Camera::pos.x;
  this->mouseY += Camera::pos.y;

  while (SDL_PollEvent(&event)) {
    int keyId, buttonId;

    if (not event.key.repeat) {
      switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
          buttonId = event.button.button;
          this->mouseState[buttonId] = true;
          this->mouseUpdate[buttonId] = this->updateCounter;
          break;
        case SDL_MOUSEBUTTONUP:
          buttonId = event.button.button;
          this->mouseState[buttonId] = false;
          this->mouseUpdate[buttonId] = this->updateCounter;
          break;
        case SDL_KEYDOWN:
          keyId = event.key.keysym.sym;
          this->keyState[keyId] = true;
          this->keyUpdate[keyId] = this->updateCounter;
          break;
        case SDL_KEYUP:
          keyId = event.key.keysym.sym;
          this->keyState[keyId] = false;
          this->keyUpdate[keyId] = this->updateCounter;
          break;
        case SDL_QUIT:
          this->quitRequested = true;
          break;
        default:
          break;
      }
    }
	}
}

bool InputManager::KeyPress(int key) {
  return (this->keyState[key] && (this->keyUpdate[key] == this->updateCounter));
}

bool InputManager::KeyRelease(int key) {
  return (not this->keyState[key] && (this->keyUpdate[key] == this->updateCounter));
}

bool InputManager::IsKeyDown(int key) {
  return this->keyState[key];
}

bool InputManager::MousePress(int button) {
  return (this->mouseState[button] && (this->mouseUpdate[button] == this->updateCounter));
}

bool InputManager::MouseRelease(int button) {
  return (not this->mouseState[button] && (this->mouseUpdate[button] == this->updateCounter));
}

bool InputManager::IsMouseDown(int button) {
  return this->mouseState[button];
}

int InputManager::GetMouseX() {
  return this->mouseX;
}

int InputManager::GetMouseY() {
  return this->mouseY;
}

Vec2 InputManager::GetMousePos() {
  return Vec2(this->mouseX, this->mouseY);
}

bool InputManager::QuitRequested() {
  return this->quitRequested;
}
