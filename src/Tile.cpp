
#include "Tile.h"

#include <SFML/Graphics.hpp>
#include <iostream>

// ------------
//
// This represents a single tile that an object could potentially interact with
//
// ------------

Tile::Tile()
{
  is_solid = false;
}

void Tile::initGraphics(const std::string& texture_path, sf::IntRect area)
{
  auto* tile_texture = new sf::Texture;
  if (!tile_texture->loadFromFile(texture_path, area))
  {
    std::cout << " Texture for " << texture_path << " cannot be loaded in!" << std::endl;
  }
  else
  {
    sprite.setTexture(*tile_texture);
  }
}