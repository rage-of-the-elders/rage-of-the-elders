#ifndef STATE_H
#define STATE_H

#include "GameObject.h"

#include <vector>
#include <memory>

class State {
protected:
  bool popRequested;
  bool quitRequested;
  bool started;
  std::vector <std::shared_ptr<GameObject>> objectArray;

  void StartArray();
  virtual void UpdateArray(float dt);
  virtual void RenderArray();

public:
  State();
  virtual ~State();
  virtual void LoadAssets() = 0;
  virtual void Update(float dt) = 0;
  virtual void Render() = 0;
  virtual void Start();
  virtual void Pause();
  virtual void Resume();
  virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
  virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject *object);
  bool PopRequested();
  bool QuitRequested();
};

#endif