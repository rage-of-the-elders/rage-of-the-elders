#include "TileSet.h"
#include <math.h>

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file) {
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;

  this->tileSet = new Sprite(associated, file);
  this->rows = this->tileSet->GetHeight() / this->GetTileHeight();
  this->columns = this->tileSet->GetWidth() / this->GetTileWidth();
}

void TileSet::RenderTile(unsigned index, float x, float y) {
  if (index >= 0 and index < (this->rows * this->columns)) {
    // FIXME: Check this
    this->tileSet->Render(int(x), int(y));
  }
}
int TileSet::GetTileWidth() {
  return this->tileWidth;
}
int TileSet::GetTileHeight() {
  return this->tileHeight;
}