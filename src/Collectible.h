
#ifndef PLATFORMERSFML_COLLECTIBLE_H
#define PLATFORMERSFML_COLLECTIBLE_H

#include "Vector2.h"
#include "Animation.h"
#include "GameObject.h"

#include <SFML/Graphics.hpp>

// ------------
//
// The template class for all objects that the player can pick up for points
//
// ------------

class Collectible : public GameObject
{
 public:
  Collectible();

  void collect();
  void animate();

  int score_value = 500;

  // This ensures that the player doesn't need to touch the edges of the
  // collectible for a collision
  float col_margin = 0;

 private:
  Animation animation = Animation(
    "Data/Images/New/Items/coin.png",
    0.075,
    2);
};

#endif // PLATFORMERSFML_COLLECTIBLE_H