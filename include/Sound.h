#ifndef SOUND_H
#define SOUND_H

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"
#include <string>

class Sound : public Component {
private:
  std::shared_ptr<Mix_Chunk> chunk;
  int channel;
  int loops;

public:
  Sound(GameObject &associated);
  Sound(GameObject &associated, std::string file);
  ~Sound();
  void Play(int times = -1);
  void PlayIfNotPlaying(int times = -1);
  void Stop();
  void ForceStop();
  void Open(std::string file);
  bool IsOpen();

  void Update(float dt);
  void Render();
  bool IsPlaying();
  bool Is(std::string type);
};

#endif