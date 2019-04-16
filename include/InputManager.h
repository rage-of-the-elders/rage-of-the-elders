#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define SPACE_KEY SDLK_SPACE
#define ESCAPE_KEY SDLK_ESCAPE

#define UP SDL_CONTROLLER_BUTTON_DPAD_UP
#define RIGHT SDL_CONTROLLER_BUTTON_DPAD_RIGHT
#define DOWN SDL_CONTROLLER_BUTTON_DPAD_DOWN
#define LEFT SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define A SDL_CONTROLLER_BUTTON_A
#define B SDL_CONTROLLER_BUTTON_B
#define X SDL_CONTROLLER_BUTTON_X
#define Y SDL_CONTROLLER_BUTTON_Y
#define LB SDL_CONTROLLER_BUTTON_LEFTSHOULDER
#define RB SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
#define LT 0x20
#define RT 0x21 //Valor arbitrário, mas tá cert
#define SELECT SDL_CONTROLLER_BUTTON_BACK
#define START SDL_CONTROLLER_BUTTON_START
#define L3 SDL_CONTROLLER_BUTTON_LEFTSTICK
#define R3 SDL_CONTROLLER_BUTTON_RIGHTSTICK

#define N_PLAYERS 2

#define INCLUDE_SDL
#include "SDL_include.h"

#include <unordered_map>

class InputManager {
private:
  bool mouseState[6];
  int mouseUpdate[6];
  int mouseX;
  int mouseY;
  std::unordered_map<int, bool> keyState;
  std::unordered_map<int, int> keyUpdate;
  std::unordered_map<int, int> controllersId;
  std::unordered_map<int, bool> joystickState[10];
  std::unordered_map<int, int> joystickUpdate[10];
  bool quitRequested;
  int updateCounter;
  SDL_GameController *controllers[N_PLAYERS];

  InputManager();
  ~InputManager();

public:
  static InputManager &GetInstance();
  void Update();
  bool KeyPress(int key);
  bool KeyRelease(int key);
  bool IsKeyDown(int key);
  bool MousePress(int button);
  bool MouseRelease(int button);
  bool IsMouseDown(int button);
  int GetMouseX();
  int GetMouseY();
  bool JoystickButtonPress(int button, int joystick);
  bool JoystickButtonRelease(int button, int joystick);
  bool IsJoystickButtonDown(int button, int joystick);
  bool QuitRequested();
  void ConnectJoysticks();
};

#endif