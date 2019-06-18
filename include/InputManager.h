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
#define W_KEY SDLK_w
#define A_KEY SDLK_a
#define S_KEY SDLK_s
#define D_KEY SDLK_d
#define F_KEY SDLK_f
#define G_KEY SDLK_g
#define H_KEY SDLK_h
#define J_KEY SDLK_j

#define INCLUDE_SDL
#include "SDL_include.h"
#include "Vec2.h"
#include "Timer.h"

#include <unordered_map>

class InputManager {
private:
  bool mouseState[6];
  int mouseUpdate[6];
  int mouseX;
  int mouseY;
  std::unordered_map<int, bool> keyState;
  std::unordered_map<int, int> keyUpdate;
  bool quitRequested;
  int updateCounter;
  std::string lastsPressKeys;
  Timer comboTimer;

  InputManager();
  ~InputManager();

public:
  static InputManager &GetInstance();
  void Update(float dt);
  void MakeCombos(int buttonId);
  void SetLastsPressKeys(std::string lastsPressKeys);
  bool KeyPress(int key);
  bool KeyRelease(int key);
  bool IsKeyDown(int key);
  bool MousePress(int button);
  bool MouseRelease(int button);
  bool IsMouseDown(int button);
  bool QuitRequested();
  int GetMouseX();
  int GetMouseY();
  Vec2 GetMousePos();
  std::string GetLastsPressKeys();

};

#endif