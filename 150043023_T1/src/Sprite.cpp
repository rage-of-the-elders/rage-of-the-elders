#include "Sprite.h"

Sprite::Sprite() {
  texture = nullptr;
}

Sprite::Sprite(std::string file) {
  texture = nullptr;
  Sprite::Open(file);
}

Sprite::~Sprite() {
  SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file) {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }

  SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

  if (texture == nullptr) {
    printf("%s\n", SDL_GetError());
    exit(-1);
  }

  int queryTexture = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  // FIXME: What are theses 2 first params? (x, y)
  SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
  clipRect = SDL_Rect {x, y, w, h};
}

void Sprite::Render(int x, int y) {
  SDL_Rect dstRect = SDL_Rect {x, y, clipRect.w, clipRect.h};
  SDL_RenderCopy(Game::GetInstance().GetRenderer(),
                 texture,
                 &clipRect,
                 &dstRect);
}

bool Sprite::IsOpen() {
  return texture != nullptr;
}