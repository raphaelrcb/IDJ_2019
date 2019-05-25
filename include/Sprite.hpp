#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_include.h>
#include "GameObject.hpp"
#include "Timer.hpp"

class Sprite: public Component{//implementar update, is e render da classe mãe (component)

  private:
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect clipRect;
    Vec2 scale;

    int width;
    int height;

    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;

    Timer selfDestructCount;
    float secondsToSelfDestruct;

  public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, std::string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    bool Is(std::string type);
    void Update(float dt);
    void SetScaleX(float scaleX, float scaleY);
    Vec2 GetScale();

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
};
