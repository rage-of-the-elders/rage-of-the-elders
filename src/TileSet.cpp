#include "TileSet.h"
#include <math.h>

TileSet::TileSet(int initialTileWidth, int tileWidth, int tileHeight, std::string file) : tileSet(*new GameObject(), file) {
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;
  this->initialTileWidth = initialTileWidth;
  this->rows = this->tileSet.GetHeight() / this->GetTileHeight();
  this->columns = this->tileSet.GetWidth() / this->GetTileWidth();
}

void TileSet::RenderTile(unsigned index, float x, float y) {
  if (index < (unsigned)(this->rows * this->columns)) {
    tileSet.SetClip((this->tileWidth * (index % this->columns)) + this->initialTileWidth,
                    this->tileHeight * (index / this->columns),
                    this->tileWidth,
                    this->tileHeight);
    this->tileSet.Render(round(x), round(y));
  }
}

void TileSet::RenderInitialTile(int cameraX, int cameraY) {
  tileSet.SetClip(0, 0, this->initialTileWidth, this->tileHeight);
  this->tileSet.Render(-cameraX, -cameraY);
}

int TileSet::GetTileWidth() {
  return this->tileWidth;
}

int TileSet::GetTileHeight() {
  return this->tileHeight;
}

int TileSet::GetInitialTileWidth() {
  return this->initialTileWidth;
}
