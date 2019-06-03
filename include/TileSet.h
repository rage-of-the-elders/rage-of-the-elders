#ifndef TILESET_H
#define TILESET_H

#include "Sprite.h"
#include <string>

class TileSet {
private:
  Sprite tileSet;

  int rows;
  int columns;
  int tileWidth;
  int tileHeight;
  int initialTileWidth;

public:
  TileSet(int initialTileWidth, int tileWidth, int tileHeight, std::string file);
  // ~TileSet();

  void RenderInitialTile(int cameraX = 0 , int cameraY = 0);
  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();
  int GetInitialTileWidth();
};

#endif
