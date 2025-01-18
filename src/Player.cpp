
#include "GameObject.h"
#include "Player.h"

#include <cmath>

// ------------
//
// The actual character object that the player controls, including its inputs
// and physics
//
// ------------

Player::Player()
{
  initialiseSprite("Data/Images/New/Characters/player_idle.png");
  sprite.setScale(sprite_scale, sprite_scale);
  sprite.setOrigin((float)sprite.getTexture()->getSize().x / 2, 0);
}

//
// Checks all the tiles in the current level, and sees if the player is
// overlapping with any of them
//
void Player::tile_col_check(const Vector2& velocity_offset)
{
  Vector2 all_collisions = Vector2(0, 0);
  for (auto & tile : current_tilemap->tiles)
  {
    if (tile.is_solid)
    {
      Vector2 current_col_side = collision(
        velocity_offset,
        tile.sprite);

      if (!(current_col_side.x == 0 && current_col_side.y == 0))
      {
        all_collisions = current_col_side;
      }
    }
  }

  col_side = all_collisions;
}

//
// Updates the player's velocity and current position
//
void Player::move(float dt)
{
  // Horizontal movement, controlled by manual input
  current_input = input_right - input_left;

  // Clamping the player's horizontal speed
  if (velocity.x < max_move_speed * dt && velocity.x > -max_move_speed * dt)
  {
    velocity.x = ((velocity.x + (max_acceleration * (float)current_input) * dt)) * current_decel;
  }
  else
  {
    velocity.x *= current_decel;
  }

  // Acceleration
  if (current_input != 0 && std::signbit(current_input) == std::signbit(velocity.x))
  {
    current_decel = 1;
  }
  // Deceleration
  else
  {
    if (current_decel >= 0)
    {
      current_decel -= max_deceleration * dt;
    }
    else
    {
      current_decel = 0;
    }
  }

  for (int i = 0; i < (int)std::ceil(std::abs(velocity.x)); i++)
  {
    tile_col_check(Vector2(velocity.x, 0));
    if (std::abs(col_side.x) > 1)
    {
      velocity.x = 0;
      break;
    }
    position.x += (float)current_input;
  }


  // Vertical movement, with gravity automatically applied
  velocity.y += max_gravity * dt;

  for (int i = 0; i < (int)std::ceil(std::abs(velocity.y)); i++)
  {
    if (velocity.y < 0)
    {
      tile_col_check(Vector2(0, velocity.y));
      if (std::abs(col_side.y) > 0)
      {
        velocity.y = 0;
        break;
      }
      else
      {
        position.y -= 1;
        continue;
      }
    }
    else
    {
      tile_col_check(Vector2(0, 1));
      if (std::abs(col_side.y) > 0)
      {
        if (input_jump)
        {
          velocity.y = -max_jump_speed;
          position.y += velocity.y;
          break;
        }
        else
        {
          velocity.y = 0;
        }
      }
      else
      {
        position.y += 1;
        continue;
      }
    }
  }
}

//
// Adds an extra bounce effect to the player's vertical velocity (when jumping
// on an enemy)
//
void Player::bounce()
{
  velocity.y = -max_bounce_speed;
}

//
// Sets velocity back to 0, 0
//
void Player::resetVelocity()
{
  velocity = Vector2(0, 0);
}

//
// Updates the player's animations depending on the current collision status
//
void Player::animate()
{
  if (col_side.y == 0)
  {
    current_anim = &animations[2];
  }
  else
  {
    if (current_input == 0)
    {
      current_anim = &animations[0];
    }
    else
    {
      current_anim = &animations[1];
    }
  }

  if (current_input != 0)
  {
    sprite.setScale(sprite_scale * (float)current_input, sprite_scale);
  }
  sprite.setTexture(current_anim->texture);
  sprite.setTextureRect(current_anim->texture_rect);
  current_anim->updateAnim();
}



