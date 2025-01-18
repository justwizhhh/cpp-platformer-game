
#include "FallingSpike.h"

// ------------
//
// A spike object that falls down and hurts the player if they are found to be
// positioned below the spike
//
// ------------

FallingSpike::FallingSpike()
{
  initialiseSprite("Data/Images/New/Hazards/spike.png");
  sprite.setScale(sprite_scale, sprite_scale);
}

//
// Allows the spike to start updating its position
//
void FallingSpike::startFalling()
{
  is_falling = true;
  fall_timer.restart();
}

//
// Updates the spike's speed and position as it falls down
//
void FallingSpike::fall()
{
  if (fall_timer.getElapsedTime().asSeconds() >= fall_delay)
  {
    current_fall_speed += fall_speed;
    position.y += current_fall_speed;
    updatePos();
  }
}

//
// Puts the spike back to its original start position
//
void FallingSpike::respawn()
{
  is_falling = false;
  current_fall_speed = 0;
  fall_timer.restart();

  position = spawn_pos;
  updatePos();
}
