#include "TileMap.h"
#include "Game.h"

#include <fstream>

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet) : Component(associated) {
  this->tileMatrix = std::vector<int>();
  this->SetTileSet(tileSet);
  this->Load(file);
}

void TileMap::Load(std::string file) {
  std::ifstream tileMapFile("assets/map/tileMap.txt", std::ios::in);

  if (tileMapFile.good()) {
    int value;
    char comma;
  
    tileMapFile >> this->mapWidth >> comma >> this->mapHeight >> comma >> this->mapDepth >> comma;
    for (int i = 0; i < this->mapDepth; i++) {
      for (int j = 0; j < this->mapHeight; j++) {
        for (int k = 0; k < this->mapWidth; k++) {
          tileMapFile >> value >> comma;
          this->tileMatrix.emplace_back(value-1);
        }
      }
    }
  } else {
    printf("ERROR: Could not open '%s'", file.c_str());
    exit(-1);
  }
  tileMapFile.close();
}

void TileMap::SetTileSet(TileSet *tileSet) {
  this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z) {
  return this->tileMatrix[ x + (this->mapWidth * y) + (this->mapWidth * this->mapHeight * z) ];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
// TO DO
}

void TileMap::Render() {
// TO DO
}

int TileMap::GetTileWidth() {
  return this->mapWidth;
}

int TileMap::GetTileHeight() {
  return this->mapHeight;
}

int TileMap::GetTileDepth() {
  return this->mapDepth;
}
