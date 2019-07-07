#ifndef PLAYABLE_H
#define PLAYABLE_H

#define PLAYABLE_MAX_HP 100
#define PLAYABLE_SPEED 200
#define POINTS_TO_ULTIMATE 100
#define ICONS_INITIAL_X_POS 20.0 // px
#define ICONS_Y_POS 15.0 // px
#define ICON_SPACING 0 // px
#define HEARTS_COUNTER 4 // px

#include "Fighter.h"

class Playable : public Fighter {
protected:
  GameObject *infoBar;
  GameObject *picture;
  GameObject *hearts[HEARTS_COUNTER];
  GameObject *ultimateBar;
  Sprite *ultimateBarSprite;
  int ultimateBarSpriteNumber;
  bool UltimateReady();
  void ManageInput(float dt);
  void HandleMovement(float dt);
  void UpdateUltimateBarSprite(int spriteNumber);
  void UpdateLifeBar();
  void CreateInfoBar();
  virtual void HandleUltimateBegin(float dt);
  virtual void HandleUltimateMidle(float dt);
  virtual void HandleUltimateFinal(float dt);
  virtual float GetHPPercentage() = 0;
  // void UpdateStateMachine(float dt);

public:
  static Playable *player;
  Playable(GameObject &associated);
  ~Playable();
  void Start();
  bool Is(std::string type);
  bool IsOpponent(GameObject &other);
  void NotifyCollision(GameObject &other);
  void Update(float dt);
};

#endif
