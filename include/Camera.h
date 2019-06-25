#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Timer.h"
#include "CameraFollower.h"

class Camera {
private:
  static GameObject *focus;
  static Sprite *black;
  static bool isBlack;
  static bool isFlickering;
  static float flickerDuration;
  static float flickerFrequency;
  static Timer flickerTimer;
  static Timer flickerFrequencyTimer;
  static CameraFollower* blackFollower;

  static void AddBlack();
  static void HandleFlicker(float dt);
  static void AdjustFocus(int screenWidth);

public:
  static Vec2 position;
  static Vec2 speed;

  static void Follow(GameObject *newFocus);
  static void Unfollow();
  static void Update(float dt);
  static GameObject *GetFocus();
  static void RenderBlack();
  static void Flicker(float duration, float frequency = 0.5);
};

#endif
