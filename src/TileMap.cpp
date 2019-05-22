#define GAP 328

#include "TileMap.h"
#include "Game.h"
#include "Camera.h"

#include <fstream>

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet) : Component(associated) {
  this->tileMatrix = std::vector<int>();
  this->SetTileSet(tileSet);
  this->Load(file);
}

TileMap::~TileMap() {
  delete tileSet;
  this->tileMatrix.clear();
}

void TileMap::Load(std::string file) {
  std::ifstream tileMapFile(("assets/" + file).c_str(), std::ios::in);

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
  for (int j = 0; j < this->mapHeight; j++)
    for (int i = 0; i < this->mapWidth; i++)
      this->tileSet->RenderTile(At(i, j, layer),
                                (i * this->tileSet->GetTileWidth()) - (i * GAP) - cameraX,
                                j * this->tileSet->GetTileHeight());
}

void TileMap::Render() {
  for (int layer = 0; layer < this->mapDepth; layer++)
    RenderLayer(layer, Camera::pos.x *(1+layer*1), Camera::pos.y *(1+layer*1));
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

bool TileMap::Is(std::string type) {
  return type == "TileMap";
}

void TileMap::Update(float dt) {

}
