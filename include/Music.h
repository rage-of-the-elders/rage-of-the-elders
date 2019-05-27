#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <string>
#include <memory>

class Music {
private:
  std::shared_ptr<Mix_Music> music;

public:
  Music();
  Music(std::string file);
  ~Music();
  void Play(int times = -1);
  void Stop(int msToStop = 500);
  void Open(std::string file);
  bool IsOpen();
};

#endif