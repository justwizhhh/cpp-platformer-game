#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H

#include "Vector2.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

// ------------
//
// The template class for all interactive game elements which can be moved around
//
// ------------

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(const std::string& file_path);

  Vector2 getMidPoint() const;
  Vector2 collision(const Vector2& offset, const sf::Sprite& other_object);
  static bool collisionPoint(const Vector2& point, const sf::Sprite& other_object);

  void updatePos();

  // Core toggles
  float sprite_scale = 3;

  Vector2 position;

  bool visibility = true;
  sf::Sprite sprite;
  sf::Texture texture;
};

#endif // BREAKOUT_GAMEOBJECT_H