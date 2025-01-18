
#ifndef PLATFORMERSFML_TILE_H
#define PLATFORMERSFML_TILE_H

#include "Vector2.h"
#include <SFML/Graphics.hpp>

// ------------
//
// This represents a single tile that an object could potentially interact with
//
// ------------

class Tile
{
 public:
  Tile();

  void initGraphics(const std::string& texture_path, sf::IntRect area);

  int id = 0;
  bool is_solid = false;
  sf::Sprite sprite;
};

#endif // PLATFORMERSFML_TILE_H
