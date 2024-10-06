#include "game.hpp"
#include "spaceship.hpp"
#include <iostream>
#include "obstacle.hpp"
#include <fstream>
Game::Game()
{
    music = LoadMusicStream("Sounds/music.ogg");
    explosionSound = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game()
{
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}
void Game::InitGame()
{
    aliensDirection = 1;
    obstacles = CreateObstacles();

    aliens = CreateAliens();
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    lives = 3;
    run = true;
    win = false;
    score = 0;
    highScore = LoadHighScoreFromFile();
}
void Game::CheckForHighscore()
{
    if (score > highScore)
    {
        highScore = score;
        SaveHighScoreToFile(highScore);
    }
}
void Game::SaveHighScoreToFile(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open())
    {
        highscoreFile << highScore;
        highscoreFile.close();
    }
    else
    {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}
int Game::LoadHighScoreFromFile()
{
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open())
    {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    }
    else
    {
        std::cerr << "Failed to load highscore from file." << std::endl;
    }
    return loadedHighscore;
}
void Game::Update()
{
    if (run)
    {
        double currentTime = GetTime();
        if (currentTime - timeLastSpawn > mysteryShipSpawnInterval)
        {
            mysteryShip.Spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        for (auto &laser : spaceship.lasers)
        {
            laser.Update();
        }
        MoveAliens();

        AlienShootLaser();

        for (auto &laser : alienLasers)
        {
            laser.Update();
        }
        DeleteInactiveLasers();
        mysteryShip.Update();
        CheckForCollitions();
    }
    else
    {
        if (IsKeyDown(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
    }
}
void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}
void Game::Draw()
{
    spaceship.Draw();

    for (auto &laser : spaceship.lasers)
    {
        laser.Draw();
    }

    for (auto &obstacles : obstacles)
    {
        obstacles.Draw();
    }

    for (auto &alien : aliens)
    {
        alien.Draw();
    }
    if (aliens.empty())
    {
        run = 0;
        win = true;
    }
    for (auto &laser : alienLasers)
    {
        laser.Draw();
    }
    mysteryShip.Draw();
}
void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it->active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (!it->active)
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::MoveAliens()
{
    for (auto &alien : aliens)
    {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25)
        {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
    for (auto &alien : aliens)
    {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLarerShootInterval && !aliens.empty())
    {

        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[randomIndex]; // a reference to an alien in the aliens vector
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type].width / 2, alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
        timeLastAlienFired = GetTime();
    }
}

void Game::CheckForCollitions()
{
    // SpaceShip Lasers
    for (auto &laser : spaceship.lasers)
    {
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if (CheckCollisionRecs(it->GetRect(), laser.GetRect()))
            {
                PlaySound(explosionSound);
                if (it->type == 1)
                {
                    score += 100;
                }
                else if (it->type == 2)
                {
                    score += 200;
                }
                else if (it->type == 3)
                {
                    score += 300;
                }
                CheckForHighscore();

                it = aliens.erase(it);
                laser.active = false;
            }
            else
            {
                ++it;
            }
        } // obstacles
        for (auto &obstacle : obstacles)
        {

            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetRect(), laser.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    ++it;
                }
            }
        }
        if (CheckCollisionRecs(mysteryShip.GetRect(), laser.GetRect()))
        {
            mysteryShip.alive = false;
            laser.active = false;
            score += 500;
            CheckForHighscore();
            PlaySound(explosionSound);
        }
    }

    // Alien Lasers
    for (auto &laser : alienLasers)
    {

        if (CheckCollisionRecs(laser.GetRect(), spaceship.GetRect()))
        {
            laser.active = false;
            std::cout << "Spaceship Hit!" << std::endl;
            lives--;
            if (lives == 0)
            {
                GameOver();
            }
        }
        for (auto &obstacle : obstacles)
        {

            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetRect(), laser.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    // Alien collison with obstalce
    for (auto &alien : aliens)
    {
        for (auto &obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetRect(), alien.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
        if (CheckCollisionRecs(alien.GetRect(), spaceship.GetRect()))
        {
            std::cout << "Spaceship hit by Alien" << std::endl;
            GameOver();
        }
    }
}

void Game::GameOver()
{

    std::cout << "Game Over" << std::endl;
    run = false;
}

void Game::HandleInpt()
{
    if (run)
    {

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_KP_1))
        {
            spaceship.MoveLeft();
        }
        else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_KP_3))
        {
            spaceship.MoveRight();
        }
        else if (IsKeyDown(KEY_SPACE))
        {
            spaceship.FireLaser();
        }
    }
}
std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;
    for (int i = 0; i < 4; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }

    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{

    std::vector<Alien> aliens;
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 11; column++)
        {
            int alienType;
            if (row == 0)
            {
                alienType = 3;
            }
            else if (row == 1 || row == 2)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }
            float x = +75 + column * 55;
            float y = +110 + row * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}
