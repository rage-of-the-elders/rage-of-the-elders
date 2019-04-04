#ifndef SPRITE_H
#define SPRITE_H
#define INCLUDE_SDL_IMAGE

#include <iostream>
#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"

class Sprite : Component {
private:
  SDL_Texture* texture;
  int width;
  int height;
  SDL_Rect clipRect;

public:
  Sprite() : Component(associated) {};
  Sprite(std::string file) : Component(associated) {};
  ~Sprite();
  void Open(std::string file);
  void SetClip(int x, int y, int w, int h);
  void Render();
  int GetWidth();
  int GetHeight();
  bool IsOpen();
  void Update(float dt);
  bool Is(std::string type);
};

#endif
