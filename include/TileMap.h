#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.h"
#include "TileSet.h"
#include <string>
#include <vector>

class TileMap : public Component {
private:
  std::vector<int> tileMatrix;
  TileSet* tileSet;
  int mapWidth;
  int mapHeight;
  int mapDepth;

public:
  TileMap(GameObject &associated, std::string file, TileSet *tileSet);
  void Load(std::string file);
  void SetTileSet(TileSet *tileSet);
  int& At (int x, int y, int z = 0);
  void RenderLayer (int layer, int cameraX = 0 , int cameraY = 0);
  void Render ();
  int GetTileWidth();
  int GetTileHeight();
  int GetTileDepth();
};

#endif
