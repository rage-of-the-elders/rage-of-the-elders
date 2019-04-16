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
      if (event.key.keysym.sym == SDLK_ESCAPE)
        this->quitRequested = true;

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
        case SDL_JOYAXISMOTION:
          puts("JOY AXIS MOTION");
          break;
        case SDL_JOYBUTTONUP:
          puts("SDL_JOYBUTTONUP");
          break;
        case SDL_JOYBUTTONDOWN:
          puts("SDL_JOYBUTTONDOWN");
          break;
        case SDL_CONTROLLERBUTTONDOWN:
          puts("SDL_CONTROLLERBUTTONDOWN");
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

bool InputManager::QuitRequested() {
  return this->quitRequested;
}

void InputManager::ConnectJoysticks(){
	int maxJoysticks = SDL_NumJoysticks();
	if(maxJoysticks > N_PLAYERS)
    maxJoysticks = N_PLAYERS;
	int n_controller = 0;

	for(int i = 0; i < maxJoysticks; i++) {
		if(this->controllers[i] != nullptr) {
      SDL_GameControllerClose(this->controllers[i]);
      this->controllers[i] = nullptr;
    }
	}

	for(int i = 0; i < maxJoysticks; ++i) {
		char guid[64];
		SDL_JoystickGetGUIDString(SDL_JoystickGetDeviceGUID(i), guid, sizeof (guid));

		if(SDL_IsGameController(i)){
			this->controllers[i] = SDL_GameControllerOpen(i);

			SDL_Joystick *joystick = SDL_GameControllerGetJoystick(this->controllers[i]);
      int instanceId = SDL_JoystickInstanceID(joystick);
      printf("Controller %d (%d real) connected\n", i, instanceId);
			this->controllersId[instanceId] = i;
			n_controller++;
		}else{
			printf("WARNING: Joystick is not a game controller\n");
			SDL_JoystickOpen(i);
		}
	}
}

bool InputManager::JoystickButtonPress(int button, int joystick){
	return joystickState[joystick][button] && joystickUpdate[joystick][button] == this->updateCounter;
} 

bool InputManager::JoystickButtonRelease(int button, int joystick){
  return !joystickState[joystick][button] && joystickUpdate[joystick][button] == this->updateCounter;
}
bool InputManager::IsJoystickButtonDown(int button, int joystick){
	return joystickState[joystick][button];
}