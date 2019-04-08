#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Component.h"
#include <string>

class Sprite : public Component {
private:
  SDL_Texture* texture;
  int width;
  int height;
  SDL_Rect clipRect;

public:
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, std::string file);
  ~Sprite();
  void Open(std::string file);
  void SetClip(int x, int y, int w, int h);
  void Render();
  void Sprite::Render(int x, int y, int w, int h);
  int GetWidth();
  int GetHeight();
  bool IsOpen();
  void Update(float dt);
  bool Is(std::string type);
};

#endif
