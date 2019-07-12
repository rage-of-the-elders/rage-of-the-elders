#define INCLUDE_SDL
#include "SDL_include.h"

#include "InputManager.h"
#include "Camera.h"

#include <cstring>
#include <iostream>

InputManager::InputManager() {
  memset(this->mouseState, false, sizeof this->mouseState);
  memset(this->mouseUpdate, 0, sizeof this->mouseUpdate);
  this->updateCounter = 0;
  this->quitRequested = false;
  this->mouseX = 0;
  this->mouseY = 0;
  this->lastsPressKeys = "";
  this->comboTimer = Timer();
}

InputManager::~InputManager() {
}

InputManager &InputManager::GetInstance() {
  static InputManager inputManager;
  return inputManager;
}

void InputManager::Update(float dt) {
  SDL_Event event;
  this->updateCounter++;
  this->quitRequested = false;
  this->comboTimer.Update(dt);

  SDL_GetMouseState(&this->mouseX, &this->mouseY);
  this->mouseX += Camera::position.x;
  this->mouseY += Camera::position.y;

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
          MakeCombos(keyId);
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

void InputManager::SetLastsPressKeys(std::string lastsPressKeys) {
  this->lastsPressKeys = lastsPressKeys;
}

void InputManager::MakeCombos(int buttonId) {
  if(this->comboTimer.Get() > 0.4 ) {
      this->lastsPressKeys = "";
      this->comboTimer.Restart();
  }

  switch (buttonId)
  {
    case SDLK_a:
      this->lastsPressKeys += "A";
      break;
    case SDLK_s:
      this->lastsPressKeys += "S";    
      break;
    case SDLK_d:
      this->lastsPressKeys += "D";  
      break;
    case SDLK_f:
      this->lastsPressKeys += "F";  
      break;
    case SDLK_g:
      this->lastsPressKeys += "G";  
      break;
    case SDLK_h:
      this->lastsPressKeys += "H";  
      break;
    case SDLK_j:
      this->lastsPressKeys += "J";  
      break;
    case SDLK_w:
      this->lastsPressKeys += "W";  
      break;

    default:
      this->lastsPressKeys += "0";
      break;
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

Vec2 InputManager::GetMousePosition() {
  return Vec2(this->mouseX, this->mouseY);
}

bool InputManager::QuitRequested() {
  return this->quitRequested;
}

std::string InputManager::GetLastsPressKeys() {
  return this->lastsPressKeys;
}
