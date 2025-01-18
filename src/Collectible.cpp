
#include "GameObject.h"
#include "Collectible.h"

// ------------
//
// The template class for all objects that the player can pick up for points
//
// ------------

Collectible::Collectible()
{
  initialiseSprite("Data/Images/New/Items/coin.png");
  sprite.setTextureRect(sf::IntRect(
    0,
    0,
    (int)sprite.getGlobalBounds().width / 2,
    (int)sprite.getGlobalBounds().height));

  sprite.setScale(sprite_scale, sprite_scale);
}

//
// Deactivates the collectible, and stops it from getting collected again
//
void Collectible::collect()
{
  visibility = false;
  sprite.setTexture(animation.texture);
}

//
// Animates the current collectible
//
void Collectible::animate()
{
  sprite.setTextureRect(animation.texture_rect);
  animation.updateAnim();
}