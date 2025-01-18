
#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include "Tilemap.h"
#include "GameObject.h"
#include "Animation.h"
#include "Vector2.h"

// ------------
//
// The actual character object that the player controls, including its inputs
// and physics
//
// ------------

class Player : public GameObject
{
 public:
  Player();

  void tile_col_check(const Vector2& velocity_offset);
  void move(float dt);
  void bounce();
  void resetVelocity();
  void animate();

  // Core gameplay toggles
  float max_move_speed = 260;
  float max_acceleration = 11.5;
  float max_deceleration = 3;
  float max_jump_speed = 10.5;
  float max_gravity = 18;
  float max_bounce_speed = 10;

  float sprite_scale = 3;
  Animation animations[4] =
    {
      Animation(
        "Data/Images/New/Characters/player_idle.png",
        0,
        1),
      Animation(
        "Data/Images/New/Characters/player_walk.png",
        0.3,
        3),
      Animation(
        "Data/Images/New/Characters/player_jump.png",
        0.4,
        2),
      Animation(
        "Data/Images/New/Characters/player_hurt.png",
        0,
        1),
    };

  bool is_active = true;

  Tilemap* current_tilemap = nullptr;
  bool input_left = false;
  bool input_right = false;
  bool input_jump = false;

 private:
  Vector2 col_side = Vector2(0, 0);
  Vector2 velocity;

  float current_decel = 0;
  int current_input = 0;

  Animation* current_anim = nullptr;
};

#endif // PLATFORMERSFML_PLAYER_H
