#include "Text.h"
#include "Resources.h"
#include "Camera.h"
#include "Game.h"

Text::Text(GameObject &associated, std::string fontFile, int fontSize, TextStyle style,
           std::string text, SDL_Color color, float flickerTime) : Component(associated) {
  this->texture = nullptr;
  this->text = text;
  this->style = style;
  this->fontFile = fontFile;
  this->fontSize = fontSize;
  this->color = color;
  this->flickerTime = flickerTime;
  this->flickerTimer = Timer();
  this->flicker = false;
  this->LoadFont();
  this->RemakeTexture();
}

Text::~Text() {
  if (this->texture != nullptr)
    SDL_DestroyTexture(this->texture);
}

void Text::Update(float dt) {
  flickerTimer.Update(dt);
  if (this->flickerTime != NO_FLICK && flickerTimer.Get() > this->flickerTime) {
    this->flicker = not this->flicker;
    if (SDL_SetTextureAlphaMod(this->texture, flicker ? 0 : 255)) {
      printf("Could not update texture alpha channel: %s\n", SDL_GetError());
    }
    flickerTimer.Restart();
  }
}

void Text::Render() {
  if (this->texture != nullptr) {
    SDL_Rect clipRect = SDL_Rect{0,
                                 0,
                                 (int)this->associated.box.w,
                                 (int)this->associated.box.h};
    SDL_Rect dstRect = SDL_Rect{(int)(this->associated.box.x - Camera::position.x),
                                (int)(this->associated.box.y - Camera::position.y),
                                (int)this->associated.box.w,
                                (int)this->associated.box.h};

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
                     this->texture,
                     &clipRect,
                     &dstRect,
                     this->associated.angleDeg,
                     nullptr, // Rotates around the center
                     SDL_FLIP_NONE);
  }
}

bool Text::Is(std::string type) {
  return type == "Text";
}

void Text::SetText(std::string text) {
  this->text = text;
  this->LoadFont();
  this->RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
  this->color = color;
  this->LoadFont();
  this->RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
  this->style = style;
  this->LoadFont();
  this->RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
  this->fontFile = fontFile;
  this->RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
  this->fontSize = fontSize;
  this->LoadFont();
  this->RemakeTexture();
}

void Text::SetPos(int x, int y, bool centerX, bool centerY) {
  this->associated.box.SetPos((x - (centerX ? associated.box.w * 0.5 : 0)),
                              (y - (centerY ? associated.box.h * 0.5 : 0)));
}


void Text::RemakeTexture() {
  if (this->texture != nullptr) {
    SDL_DestroyTexture(this->texture);
  }

  SDL_Surface *surface = nullptr;
  if (this->style == TextStyle::SOLID)
    surface = TTF_RenderText_Solid(this->font.get(), this->text.c_str(), this->color);
  if (this->style == TextStyle::SHADED)
    surface = TTF_RenderText_Shaded(this->font.get(), this->text.c_str(), this->color, SDL_Color{});
  if (this->style == TextStyle::BLENDED)
    surface = TTF_RenderText_Blended(this->font.get(), this->text.c_str(), this->color);

  if(surface == nullptr){
		printf("%s\n", SDL_GetError());
		exit(-1);
	}

  this->texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
  void SDL_FreeSurface(SDL_Surface* surface);

  int width, height;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  this->associated.box.SetSize(width, height);
}

std::shared_ptr<TTF_Font> Text::LoadFont(std::string fontFile, int fontSize) {
	return Resources::GetFont(fontFile, fontSize);
}

void Text::LoadFont() {
	this->font = Resources::GetFont(this->fontFile, this->fontSize);
}
