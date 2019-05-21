#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Component.h"
#include "Timer.h"
#include <string>

class Sprite : public Component {
private:
  std::shared_ptr<SDL_Texture> texture;
  int width;
  int height;
  bool repeat;
  SDL_Rect clipRect;
  Vec2 scale;
  int frameCount;
  int currentFrame;
  float timeElapsed;
  float frameTime;
  Timer selfDestructCount;
  float secondsToSelfDestruct;
  bool finished;

public:
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, std::string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0, bool repeat = true);
  ~Sprite();
  void Open(std::string file);
  void SetClip(int x, int y, int w, int h);
  void Render();
  void Render(int x, int y);
  int GetWidth();
  int GetHeight();
  Vec2 GetScale();
  bool IsFinished();
  void SetScaleX(float scale);
  void SetScaleX(float scaleX, float scaleY);
  void SetFrame (int frame);
  void SetFrameCount (int frameCount);
  void SetFrameTime (float frameTime);
  void UpdateFrame();
  bool IsOpen();
  void Update(float dt);
  void SetFinished(bool finished);
  bool Is(std::string type);
  void SetRepeat(bool repeat);
  bool GetRepeat();
};

#endif
