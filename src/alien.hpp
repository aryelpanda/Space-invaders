#pragma once
#include <raylib.h>

class Alien
{
public:
    Alien(int type, Vector2 position);
    void Draw();
    int GetType();
    void Update(int direction);
    static void UnloadImages();
    Rectangle GetRect();
    static Texture2D alienImages[3];
    int type;
    Vector2 position;

private:
};