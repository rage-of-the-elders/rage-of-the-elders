#ifndef TEXT_H
#define TEXT_H

#define INCLUDE_SDL_TTF

#define NO_FLICK -1
#define WHITE {255, 255, 255, 255}
#define BLACK {0, 0, 0, 255}
#define DARK_BLUE {3, 50, 77, 255}
#define YELLOW {220, 245, 73, 255}

#include "SDL_include.h"
#include "Component.h"
#include "Timer.h"

#include <unordered_map>
#include <string>
#include <memory>

class Text : public Component {
public:
  enum TextStyle { SOLID, SHADED, BLENDED };
  Text(GameObject &associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float flickerTime = NO_FLICK);
  ~Text();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void SetText(std::string text);
  void SetColor(SDL_Color color);
  void SetStyle(TextStyle style);
  void SetFontFile(std::string fontFile);
  void SetFontSize(int fontSize);
  void SetPos(int x, int y, bool centerX = true, bool centerY = true);
  static std::shared_ptr<TTF_Font> LoadFont(std::string fontFile, int size);
  void LoadFont();

  private:
    std::shared_ptr<TTF_Font> font;
    SDL_Texture *texture;
    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
    float flickerTime;
    Timer flickerTimer;
    bool flicker;

    void RemakeTexture();
};

#endif
