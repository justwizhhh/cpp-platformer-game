
#include "Vector2.h"
#include "GameObject.h"

#include "Game.h"

#include <random>
#include <iostream>

// ------------
//
// The main logic code for all gameplay and UI functionality
//
// ------------

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{}

Game::~Game()
  = default;

bool Game::init()
{
  window_current_size = Vector2(
    window.getView().getSize().x,
    window.getView().getSize().y);
  middle_of_screen = Vector2(
    window.getView().getSize().x / 2,
    window.getView().getSize().y / 2);

  game_view.reset(sf::FloatRect(
    0,
    0,
    window.getView().getSize().x,
    window.getView().getSize().y));
  ui_view.reset(sf::FloatRect(
    0,
    0,
    window.getView().getSize().x,
    window.getView().getSize().y));

  cam_start_pos.set(game_view.getCenter().x, game_view.getCenter().y);

  initLevels();
  initUI();

  return true;
}

bool Game::initLevels()
{
  tilemaps[0].loadMap("Data/Levels/level1_map.txt",
                      "Data/Levels/level1_object_map.txt");
  tilemaps[0].createMap("Data/Images/New/Misc/foreground_tiles.png",
                        16, 3, 45, 15);
  tilemaps[0].setSpawn(Vector2(128, 576));

  tilemaps[1].loadMap("Data/Levels/level2_map.txt",
                      "Data/Levels/level2_object_map.txt");
  tilemaps[1].createMap("Data/Images/New/Misc/foreground_tiles.png",
                        16, 3, 68, 15);
  tilemaps[1].setSpawn(Vector2(128, 240));

  tilemaps[2].loadMap("Data/Levels/level3_map.txt",
                      "Data/Levels/level3_object_map.txt");
  tilemaps[2].createMap("Data/Images/New/Misc/foreground_tiles.png",
                        16, 3, 68, 15);
  tilemaps[2].setSpawn(Vector2(128, 384));

  for (auto & tilemap : tilemaps)
  {
    tilemap.setSolid(1);
    tilemap.setSolid(2);
    tilemap.setSolid(3);
    tilemap.setSolid(4);
  }

  return true;
}

/*
 * Take current text object, and give it a set size (scale), position, and option colour
 */
void Game::initTextObj(sf::Text* text, const Vector2& position, int scale, sf::Color color)
{
  text->setCharacterSize(scale);
  text->setPosition(position.x, position.y);
  text->setFillColor(color);
}

bool Game::initUI()
{
  if (!font.loadFromFile("Data/Images/New/Misc/Factor.ttf"))
  {
    std::cout << "Font not loaded correctly! Cannot load UI elements! \n";
    return false;
  }
  else
  {
    // Title-screen UI
    initTextObj(
      &game_text_objects[0],
      Vector2(middle_of_screen.x, middle_of_screen.y - 175), 18);
    initTextObj(
      &game_text_objects[1],
      Vector2(middle_of_screen.x, middle_of_screen.y + 70), 28);
    initTextObj(
      &game_text_objects[2],
      Vector2(middle_of_screen.x, middle_of_screen.y + 200), 14);
    initTextObj(
      &game_text_objects[3],
      Vector2(middle_of_screen.x, middle_of_screen.y + 110), 14);

    game_logo.initialiseSprite("Data/Images/New/Misc/title_logo.png");
    game_logo.sprite.setOrigin(
      game_logo.sprite.getGlobalBounds().width / 2,
      game_logo.sprite.getGlobalBounds().height / 2);
    game_logo.sprite.setScale(2, 2);
    game_logo.position = Vector2(middle_of_screen.x, middle_of_screen.y - 95);
    game_logo.updatePos();

    // Gameplay UI
    initTextObj(
      &game_text_objects[4],
      Vector2(140, 60), 18);
    initTextObj(
      &game_text_objects[5],
      Vector2(window_current_size.x - 140, 60), 18);
    hud_banner.setPosition(0, 45);
    hud_banner.setSize(sf::Vector2f(window_current_size.x, 35));
    hud_banner.setFillColor(sf::Color::Black);

    // Win-screen UI
    initTextObj(
      &game_text_objects[8],
      Vector2(middle_of_screen.x, middle_of_screen.y - 40), 28);
    initTextObj(
      &game_text_objects[9],
      Vector2(middle_of_screen.x, middle_of_screen.y + 50), 22);

    // Game-over-screen UI
    initTextObj(
      &game_text_objects[10],
      Vector2(middle_of_screen.x, middle_of_screen.y - 10), 28);

    // Game complete screen UI
    initTextObj(
      &game_text_objects[11],
      Vector2(middle_of_screen.x, middle_of_screen.y - 40), 28);
    initTextObj(
      &game_text_objects[12],
      Vector2(middle_of_screen.x, middle_of_screen.y + 50), 22);

    // Give all text objects common attributes (same font, same origin point, etc.)
    for (int i = 0; i < (std::end(game_text_objects) - std::begin(game_text_objects)); i++)
    {
      game_text_objects[i].setString(game_text_strings[i]);
      game_text_objects[i].setFont(font);
      game_text_objects[i].setOrigin(
        game_text_objects[i].getGlobalBounds().width / 2,
        game_text_objects[i].getGlobalBounds().height / 2);
    }

    return true;
  }
}

void Game::keyPressed(sf::Event event)
{
  switch(current_game_state)
  {
    case GameState::TITLE_SCREEN:
      if (event.key.code == sf::Keyboard::Enter)
      {
        startGame();
        changeState(GameState::GAMEPLAY);
      }
      break;

    case GameState::WIN_SCREEN:
      if (event.key.code == sf::Keyboard::Enter)
      {
        changeState(GameState::GAMEPLAY);
      }
      break;

    case GameState::LOSE_SCREEN:
    case GameState::GAME_COMPLETE:
      if (event.key.code == sf::Keyboard::Enter)
      {
        changeState(GameState::TITLE_SCREEN);
      }
      break;

    case GameState::GAMEPLAY:
    default:
      // Player inputs
      if (event.key.code == sf::Keyboard::A)
      {
        player.input_left = true;
      }
      if (event.key.code == sf::Keyboard::D)
      {
        player.input_right = true;
      }

      if (event.key.code == sf::Keyboard::Space)
      {
        player.input_jump = true;
      }

      if (event.key.code == sf::Keyboard::Enter)
      {
        is_playing = !is_playing;
      }
      break;
  }
}

void Game::keyReleased(sf::Event event)
{
  switch(current_game_state)
  {
    case GameState::TITLE_SCREEN:
    case GameState::WIN_SCREEN:
    case GameState::LOSE_SCREEN:
      break;

    case GameState::GAMEPLAY:
    default:
      if (event.key.code == sf::Keyboard::A)
      {
        player.input_left = false;
      }

      if (event.key.code == sf::Keyboard::D)
      {
        player.input_right = false;
      }

      if (event.key.code == sf::Keyboard::Space)
      {
        player.input_jump = false;
      }

      break;
  }
}

void Game::startGame()
{
  player.current_tilemap = &tilemaps[current_tilemap];
  respawn();

  setScore(0);
  setLives(max_lives);

  // Respawning all coin objects in the level
  for (auto & tilemap : tilemaps)
  {
    for (auto & collectible : tilemap.collectibles)
    {
      if (!collectible->visibility)
      {
        collectible->visibility = true;
      }
    }
  }
}

void Game::levelWin()
{
  coins_collected = 0;
  current_tilemap += 1;
  if (current_tilemap < 3)
  {
    changeState(GameState::WIN_SCREEN);
  }
  else
  {
    current_tilemap = 0;
    startGame();
    changeState(GameState::GAME_COMPLETE);
  }

  respawn();
}

void Game::levelLost()
{
  coins_collected = 0;
  current_tilemap = 0;
  changeState(GameState::LOSE_SCREEN);
  respawn();
}

void Game::respawn()
{
  player.position = tilemaps[current_tilemap].player_spawn_pos;
  player.current_tilemap = &tilemaps[current_tilemap];
  player.resetVelocity();

  // Respawning only the obstacle objects
  for (auto & tilemap : tilemaps)
  {
    for (auto& enemy : tilemap.enemies)
    {
      if (!enemy->visibility)
      {
        enemy->visibility = true;
      }
      enemy->respawn();
    }

    for (auto& spike : tilemap.falling_spikes)
    {
      if (!spike->visibility)
      {
        spike->visibility = true;
      }
      spike->respawn();
    }
  }

  game_view.setCenter(cam_start_pos.x, cam_start_pos.y);
}

void Game::changeState(GameState new_state)
{
  game_view.setCenter(cam_start_pos.x, cam_start_pos.y);

  // Making sure inputs don't get instantly processed at the start of a new state/level
  player.resetVelocity();
  player.input_left = player.input_right = false;
  player.input_jump = false;

  current_game_state = new_state;
}

void Game::setScore(int new_score)
{
  score = new_score;
  game_text_objects[4].setString(game_text_strings[4] + std::to_string(score));
}
void Game::setLives(int new_lives)
{
  lives = new_lives;
  game_text_objects[5].setString(game_text_strings[5] + std::to_string(lives));

  if (lives > 0)
  {
    respawn();
  }
  else
  {
    levelLost();
  }
}

void Game::update(float dt)
{
  if (current_game_state == GameState::GAMEPLAY)
  {
    // Main gameplay object logic
    if (is_playing)
    {
      if (player.is_active)
      {
        player.move(dt);
      }
      player.updatePos();
      player.animate();

      // Collecting coins and treasure
      for (auto & collectible : tilemaps[current_tilemap].collectibles)
      {
        collectible->animate();

        Vector2 collectible_col = player.collision(
          Vector2(0, 0),
          collectible->sprite);
        if (!(collectible_col.x == 0 && collectible_col.y == 0))
        {
          if (std::abs(collectible_col.x) >= collectible->col_margin
              && std::abs(collectible_col.y) >= collectible->col_margin)
          {
            if (collectible->visibility)
            {
              coins_collected++;
              setScore(score + collectible->score_value);
              collectible->collect();
            }

            // Check if all collectibles in the current scene have been loaded or not
            if (coins_collected >= tilemaps[current_tilemap].collectibles.size())
            {
              levelWin();
            }
          }
        }
      }
      // Getting hit by enemies
      for (auto & enemy : tilemaps[current_tilemap].enemies)
      {
        enemy->move(dt);
        enemy->updatePos();
        enemy->animate();

        if (enemy->visibility)
        {
          Vector2 enemy_col = player.collision(
            Vector2(0, 0),
            enemy->sprite);
          if (!(enemy_col.x == 0 && enemy_col.y == 0))
          {
            // Check if the player is above the spider AND if the player is
            // inside the spider's horizontal area
            if (player.getMidPoint().x >=
                  enemy->position.x - enemy->col_margin
                && player.getMidPoint().x <=
                     enemy->position.x + enemy->sprite.getGlobalBounds().width + enemy->col_margin
                && player.getMidPoint().y <= enemy->position.y)
            {
              enemy->visibility = false;
              player.bounce();
            }
            else
            {
              setLives(lives -= 1);
            }
          }
        }
      }

      if (player.position.y > window_current_size.y)
      {
        setLives(lives -= 1);
      }

      // Misc. harmful obstacles
      for (auto & spike : tilemaps[current_tilemap].falling_spikes)
      {
        if (spike->visibility)
        {
          // Starting the falling sequence
          if (!spike->is_falling)
          {
            // Check if the player is positioned below the spike
            float check_pos = player.getMidPoint().x;
            if (check_pos >
                  spike->position.x + spike->col_margin &&
                check_pos <
                  spike->position.x + spike->sprite.getGlobalBounds().width - spike->col_margin)
            {
              if (player.getMidPoint().y > spike->getMidPoint().y)
              {
                spike->startFalling();
              }
            }
          }
          else
          {
            if (spike->position.y < window_current_size.y)
            {
              spike->fall();
            }
          }

          // Checking for player collision
          Vector2 spike_col = player.collision(
            Vector2(0, 0),
            spike->sprite);
          if (!(spike_col.x == 0 && spike_col.y == 0))
          {
            if (std::abs(spike_col.x) >= spike->col_margin
                && std::abs(spike_col.y) >= spike->col_margin)
            {
              setLives(lives -= 1);
            }
          }
        }
      }

      // Camera movement
      if (cam_move_dir == 0)
      {
        if (player.getMidPoint().x + (player.sprite.getGlobalBounds().width / 2)
            > game_view.getCenter().x + game_view.getSize().x / 2)
        {
          player.is_active = false;
          cam_move_start.set(
            game_view.getCenter().x,
            game_view.getCenter().y);

          // Camera transitions towards right side
          cam_move_dir = 1;
          cam_move_target.set(
            game_view.getCenter().x + game_view.getSize().x,
            game_view.getCenter().y);
        }
        else if (player.getMidPoint().x - (player.sprite.getGlobalBounds().width / 2)
                 < game_view.getCenter().x - game_view.getSize().x / 2)
        {
          player.is_active = false;
          cam_move_start.set(
            game_view.getCenter().x,
            game_view.getCenter().y);

          // Camera transition towards left side
          cam_move_dir = -1;
          cam_move_target.set(
            game_view.getCenter().x - game_view.getSize().x,
            game_view.getCenter().y);
        }
      }
      else
      {
        // Move the camera, but also the player, so they don't get stuck
        // inside the transition trigger
        game_view.move(cam_move_speed * (float)cam_move_dir, 0);
        if (cam_move_dir > 0)
        {
          player.position.x += cam_move_target.x / cam_move_start.x;
        }
        else
        {
          player.position.x -= cam_move_start.x / cam_move_target.x;
        }

        // Stop camera movement if destination position has been reached
        if ((cam_move_dir > 0 && game_view.getCenter().x >= cam_move_target.x)
            || (cam_move_dir < 0 && game_view.getCenter().x <= cam_move_target.x))
        {
          game_view.setCenter(cam_move_target.x, game_view.getCenter().y);
          cam_move_dir = 0;
          player.is_active = true;
        }
      }
    }
  }
}

void Game::render()
{
  switch(current_game_state)
  {
    case GameState::TITLE_SCREEN:
      window.draw(game_logo.sprite);
      window.draw(game_text_objects[0]);
      window.draw(game_text_objects[1]);
      window.draw(game_text_objects[2]);
      window.draw(game_text_objects[3]);
      break;

    case GameState::GAMEPLAY:
    default:
      // Gameplay objects
      window.setView(game_view);
      for (auto & tile : tilemaps[current_tilemap].tiles)
      {
        window.draw(tile.sprite);
      }
      for (auto & object : tilemaps[current_tilemap].collectibles)
      {
        if (object->visibility)
        {
          window.draw(object->sprite);
        }
      }

      for (auto & object : tilemaps[current_tilemap].enemies)
      {
        if (object->visibility)
        {
          window.draw(object->sprite);
          window.draw(object->spider_web);
        }
      }

      for (auto & object : tilemaps[current_tilemap].falling_spikes)
      {
        if (object->visibility)
        {
          window.draw(object->sprite);
        }
      }

      window.draw(player.sprite);

      // Gameplay UI
      window.setView(ui_view);
      window.draw(hud_banner);
      window.draw(game_text_objects[4]);
      window.draw(game_text_objects[5]);

      break;

    case GameState::WIN_SCREEN:
      window.draw(game_text_objects[8]);
      window.draw(game_text_objects[9]);
      break;

    case GameState::LOSE_SCREEN:
      window.draw(game_text_objects[10]);
      break;

    case GameState::GAME_COMPLETE:
      window.draw(game_text_objects[11]);
      window.draw(game_text_objects[12]);
      break;
  }
}
