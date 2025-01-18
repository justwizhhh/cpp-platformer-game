
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "Vector2.h"
#include "GameObject.h"
#include "Player.h"
#include "Tilemap.h"

#include <SFML/Graphics.hpp>

// ------------
//
// The different game screens that the player will be able to access
//
// ------------

enum class GameState
{
  TITLE_SCREEN,
  GAMEPLAY,
  WIN_SCREEN,
  LOSE_SCREEN,
  GAME_COMPLETE
};

// ------------
//
// The main logic code for all gameplay and UI functionality
//
// ------------

class Game
{
 public:

  // Core functions
  explicit Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  bool initLevels();
  static void initTextObj(sf::Text* text, const Vector2& position, int scale, sf::Color color = sf::Color::White);
  bool initUI();

  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  void startGame();
  void levelWin();
  void levelLost();
  void respawn();
  void changeState(GameState new_state);

  void setScore(int new_score);
  void setLives(int new_lives);

  void update(float dt);
  void render();

  // Core toggles
  int max_lives = 3;
  float cam_move_speed = 32.5;

  Tilemap tilemaps[3];

 private:
  sf::RenderWindow& window;
  sf::View game_view;
  sf::View ui_view;

  Vector2 window_current_size = Vector2(0, 0);
  Vector2 middle_of_screen = Vector2(0, 0);

  // Gameplay assets
  bool is_playing = true;
  GameState current_game_state = GameState::TITLE_SCREEN;

  Player player;
  int current_tilemap = 0;
  int score = 0;
  int lives = 0;

  int coins_collected = 0;

  int cam_move_dir = 0;
  Vector2 cam_start_pos = Vector2(0, 0);
  Vector2 cam_move_start = Vector2(0, 0);
  Vector2 cam_move_target = Vector2(0, 0);

  // UI assets
  GameObject game_logo;
  sf::RectangleShape hud_banner;
  sf::Font font;
  std::string game_text_strings[13] =
    {
      "Welcome to the",
      "Press Enter to Start",
      "Games in C++",
      "Collect all of the coins to progress to the next level!",
      "Score - ",
      "Lives - ",
      "High Score - ",
      "Game Paused",
      "Level Complete!",
      "Onto the next stage...",
      "Game Over!",
      "Game Complete!",
      "Thank you for playing! Press Enter."
    };

  sf::Text game_text_objects[13];
};

#endif // PLATFORMER_GAME_H
