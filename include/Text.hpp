#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL_include.h>
#include "Component.hpp"
#include "Sprite.hpp"

class Text: public Component{//implementar update, is e render da classe mãe (component)

  public:

    enum TextStyle {SOLID, SHADED, BLENDED};

    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float screenTime = 0, SDL_Color bgcolor = {0, 0, 0, 255});
    ~Text();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetBGColor(SDL_Color bgcolor);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);
    void SetScreenTime(float screenTime);
    void RemakeTexture();


private:

    std::shared_ptr<TTF_Font> font;
    SDL_Texture* texture;
    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
    SDL_Color bgcolor;

    float screenTime;
    int onScreen = 0;
};
