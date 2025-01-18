
#ifndef PLATFORMERSFML_FALLINGSPIKE_H
#define PLATFORMERSFML_FALLINGSPIKE_H

#include "GameObject.h"

// ------------
//
// A spike object that falls down and hurts the player if they are found to be
// positioned below the spike
//
// ------------

class FallingSpike : public GameObject
{
 public:
  FallingSpike();

  void startFalling();
  void fall();
  void respawn();

  Vector2 spawn_pos = Vector2(0, 0);
  bool is_falling = false;

  float fall_delay = 0.2;
  float fall_speed = 0.38;
  float col_margin = 12;

 private:
  float current_fall_speed = 0;
  sf::Clock fall_timer;
};

#endif // PLATFORMERSFML_FALLINGSPIKE_H
