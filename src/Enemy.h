
#ifndef PLATFORMERSFML_ENEMY_H
#define PLATFORMERSFML_ENEMY_H

#include "Vector2.h"
#include "Animation.h"
#include "GameObject.h"

#include <SFML/Graphics.hpp>

// ------------
//
// Main class for the spider enemy, that the player can get hurt by
//
// ------------

class Enemy : public GameObject
{
 public:
  Enemy();

  void move(float dt);
  void respawn();
  void animate();

  // Movement toggles
  float move_amplitude = 50;
  float move_speed = 3.5;
  float spider_web_width = 4;

  // Margin value allows for easier bouncing for the player
  // (to make sure they don't touch the side of the enemy)
  float col_margin = 40;

  Vector2 spawn_pos = Vector2(0, 0);

  sf::RectangleShape spider_web;

 private:
  float move_progress = 0;

  Animation animation = Animation(
    "Data/Images/New/Hazards/enemy_spider.png",
    0.075,
    2);
};

#endif // PLATFORMERSFML_ENEMY_H
