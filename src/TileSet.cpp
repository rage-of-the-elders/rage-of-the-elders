#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) {
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;

  // FIXME: check this
  GameObject *go = new GameObject();
  this->tileSet = new Sprite(*go, file);
  this->rows = this->tileSet->GetHeight() / this->GetTileHeight();
  this->columns = this->tileSet->GetWidth() / this->GetTileWidth();
}

void TileSet::RenderTile(unsigned index, float x, float y) {
  // FIXME: Check this
  if (index >= 0 and index < (this->rows * this->columns)) {
    this->tileSet->Render(x, y);
  }
}
int TileSet::GetTileWidth() {
  return this->tileWidth;
}
int TileSet::GetTileHeight() {
  return this->tileHeight;
}