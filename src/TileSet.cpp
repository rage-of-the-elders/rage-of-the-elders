#include "TileSet.h"
#include <math.h>

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file) : tileSet(associated, file) {
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;
  this->rows = this->tileSet.GetHeight() / this->GetTileHeight();
  this->columns = this->tileSet.GetWidth() / this->GetTileWidth();
}

void TileSet::RenderTile(unsigned index, float x, float y) {
  if (index < (this->rows * this->columns)) {
    // FIXME: Check this
    tileSet.SetClip(this->tileWidth * (index % this->columns),
                    this->tileHeight * (index / this->columns),
                    this->tileWidth,
                    this->tileHeight);
    this->tileSet.Render(int(x), int(y));
  }
}
int TileSet::GetTileWidth() {
  return this->tileWidth;
}
int TileSet::GetTileHeight() {
  return this->tileHeight;
}