#ifndef TIMER_H
#define TIMER_H

class Timer {
private:
  float timer;

public:
  Timer();
  void Update(float dt);
  void Restart();
  float Get();
};

#endif