#ifndef TILESET_H
#define TILESET_H

// #define INCLUDE_SDL_IMAGE
// #include "SDL_include.h"

#include "Sprite.h"
#include <string>

class TileSet {
private:
  Sprite *tileSet;
  int rows;
  int columns;
  int tileWidth;
  int tileHeight;

public:
  TileSet(int tileWidth, int tileHeight, std::string file);
  // ~TileSet();

  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();
};

#endif