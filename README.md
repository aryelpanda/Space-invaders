
# Space Invaders Game

## Overview

This is a classic **Space Invaders** game, built using **C++** and **Raylib** for graphics rendering. The project demonstrates the use of **Object-Oriented Programming (OOP)** principles to structure the game logic and design. The game also features **high score saving**, ensuring players can track their best performance.

[Watch the Demo Video on YouTube](https://www.youtube.com/watch?v=hqaTOWEMSd4)

## Features

- Player-controlled spaceship that can move horizontally and shoot bullets
- Waves of alien invaders that gradually increase in difficulty
- Collisions between bullets and invaders
- Lives and score tracking system
- **High score saving** that keeps track of the best performance across game sessions
- Simple and intuitive control system
- Retro-style graphics

## Object-Oriented Design

The project is organized around core OOP principles, such as:

- **Encapsulation**: Game entities like the player, enemies, and bullets are represented by classes, encapsulating their data and behaviors.
- **Inheritance**: Common properties and functions between game objects are shared using inheritance, reducing code duplication.
- **Polymorphism**: Implemented in how different game objects react to collision detection or game events.
  
### Main Classes

- **Player**: Controls the spaceship, movement, and shooting actions.
- **Invader**: Represents the enemy entities with behaviors like movement and reaction to being hit by bullets.
- **Bullet**: Represents the player's shots and their movement logic.
- **Game**: Manages the game loop, event handling, and rendering of all objects.

## High Score System

The game saves the **highest score** achieved during gameplay. Every time the player beats their previous high score, the new high score is saved, allowing the player to compete against their best performance.

## Libraries and Tools Used

- **Raylib**: A simple and easy-to-use library for rendering graphics, handling input, and managing game audio.
- **C++**: Core programming language used to develop the game.

## How to Play

- **Move**: Use the arrow keys to move the spaceship left or right.
- **Shoot**: Press the spacebar to shoot bullets at the incoming invaders.
- **Objective**: Destroy all invaders while avoiding being hit to score as high as possible.
- **High Score**: The game will automatically save your highest score.

## Installation and Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/space-invaders.git
