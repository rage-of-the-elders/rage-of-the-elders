#define INCLUDE_SDL
#include "SDL_include.h"

#include "InputManager.h"

#include <cstring>

InputManager::InputManager() {
  memset(this->mouseState, false, sizeof this->mouseState);
  memset(this->mouseUpdate, 0, sizeof this->mouseUpdate);
  this->updateCounter = 0;
  this->quitRequested = false;
  this->mouseX = 0;
  this->mouseY = 0;
}

InputManager &InputManager::GetInstance() {
  static InputManager inputManager;
  return inputManager;
}

void InputManager::Update() {
  SDL_Event event;
	int mouseX, mouseY;
  this->updateCounter++;
  this->quitRequested = false;

  SDL_GetMouseState(&mouseX, &mouseY);

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
          keyId = event.button.button;
          this->keyState[keyId] = true;
          this->keyUpdate[keyId] = this->updateCounter;
          break;
        case SDL_KEYUP:
          keyId = event.button.button;
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
		
      // Traveling the array backwards to always click on the object from above
			// for (int i = objectArray.size() - 1; i >= 0; i--) {
			// 	GameObject* go = (GameObject*) objectArray[i].get();

      //   if (go->box.Contains( (float)mouseX, (float)mouseY ) ) {
			// 		Face* face = (Face*)go->GetComponent("Face");
			// 		if (face != nullptr) {
			// 			face->Damage(std::rand() % 10 + 10);
      //       break; // Exits the loop to hit only one face
      //     }
			// 	}
			// }

		// if (event.type == SDL_KEYDOWN) {
		// 	if( event.key.keysym.sym == SDLK_ESCAPE ) {
		// 		quitRequested = true;
		// 	} else {
		// 		Vec2 objPos = Vec2(mouseX, mouseY).Rotate(200, rand() % 360);
		// 		this->AddObject((int)objPos.x, (int)objPos.y);
		// 	}
		// }
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

bool InputManager::QuitRequested() {
  return this->quitRequested;
}
