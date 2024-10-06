#include <raylib.h>
#include "globals.hpp"
#include "game.hpp"
#include <string>
std::string FormatWithLeadingZeros(int number, int width)
{
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}
int main()
{

    InitWindow(windowWidth + offSet, windowHeight + 2 * offSet, "Space Invaders");
    InitAudioDevice();

    Font font = LoadFontEx("Font/monogarm.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(60);
    Game game;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleInpt();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        if (game.run)
        {
            DrawTextEx(font, "Level 01", {570, 740}, 34, 2, yellow);
        }
        else if (game.win)
        {
            DrawTextEx(font, "You Win!!", {570, 740}, 34, 2, yellow);
            DrawTextEx(font, "Press ENTER to Continue.", {200, 740}, 20, 2, yellow);
        }
        else
        {
            DrawTextEx(font, "Game Over!", {570, 740}, 34, 2, yellow);
            DrawTextEx(font, "Press ENTER to Continue.", {200, 740}, 20, 2, yellow);
        }
        float x = 50.0;
        for (int i = 0; i < game.lives; i++)
        {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50;
        }
        // Score
        DrawTextEx(font, "Score", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 27, 2, yellow);
        std::string highscoreText = FormatWithLeadingZeros(game.highScore, 5);
        DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 1, yellow);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}