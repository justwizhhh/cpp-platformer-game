#ifndef PLATFORMERSFML_TILEMAP_H
#define PLATFORMERSFML_TILEMAP_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Collectible.h"
#include "Enemy.h"
#include "FallingSpike.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

// ------------
//
// This stores a list of all currently-loaded tiles and objects in a level
//
// ------------

class Tilemap
{
 public:
  ~Tilemap();

  void loadMap(const std::string& tile_file_path, const std::string& object_file_path);
  void createMap(const std::string& texture, float tile_size, float tile_scale, int width, int height);
  void setSolid(int tile_id);
  void setSpawn(const Vector2& pos);

  Vector2 player_spawn_pos;
  std::vector<Tile> tiles;
  std::vector<Collectible*> collectibles;
  std::vector<Enemy*> enemies;
  std::vector<FallingSpike*> falling_spikes;

 private:
  std::string map_string;
  std::string map_object_string;
};

#endif // PLATFORMERSFML_TILEMAP_H
