#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_include.h>

#include "Component.hpp"
#include "Sprite.hpp"

class Text: public Component{//implementar update, is e render da classe mãe (component)

  public:

    enum TextStyle {SOLID, SHADED, BLENDED};

    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
    ~Text();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);
    void RemakeTexture();


private:

    std::shared_ptr<TTF_Font> font;
    std::shared_ptr<SDL_Texture> texture;
    std::string text;
    TextStyle style;
    int fontSize;
    SDL_Color color;

};
