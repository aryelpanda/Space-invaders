#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
class Game
{

public:
    Game();
    ~Game();
    void Draw();
    void HandleInpt();
    void Update();
    bool win;
    bool run;
    int lives;
    int score;
    int highScore;
    Music music;

private:
    void DeleteInactiveLasers();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootLaser();
    void CheckForCollitions();
    void GameOver();
    void Reset();
    void InitGame();
    void CheckForHighscore();
    void SaveHighScoreToFile(int highscore);
    int LoadHighScoreFromFile();
    float mysteryShipSpawnInterval;
    float timeLastSpawn;
    constexpr static float alienLarerShootInterval = 0.35;
    float timeLastAlienFired;
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    std::vector<Laser> alienLasers;
    int aliensDirection;
    MysteryShip mysteryShip;
    Sound explosionSound;
};
