
#include <iostream>

#include "Tilemap.h"

#include <SFML/Graphics.hpp>

// ------------
//
// This stores a list of all currently-loaded tiles and objects in a level
//
// ------------

// -------- Note --------
// Custom level support is available through https://asciiflow.com/#/
// ----------------------

// Load in the tile ID information from 'level_map.txt'
void Tilemap::loadMap(const std::string& tile_file_path, const std::string& object_file_path)
{
  std::ifstream map_file(tile_file_path);
  std::ifstream object_map_file(object_file_path);

  if (map_file.is_open() && object_map_file.is_open())
  {
    std::string current_tile_line;
    std::string current_object_line;

    while (std::getline(map_file, current_tile_line))
    {
      // No line breaks, so we can read the tile/object ID info much quicker
      map_string += current_tile_line;
    }
    while (std::getline(object_map_file, current_object_line))
    {
      // No line breaks, so we can read the tile/object ID info much quicker
      map_object_string += current_object_line;
    }
  }

  map_file.close();
  object_map_file.close();
}

//
// Take the tile data string and create individual sprites out of each tile
//
void Tilemap::createMap(const std::string& texture, float tile_size, float tile_scale, int width, int height)
{
  int tile_scan = 0;
  int object_scan = 0;
  for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width ; j++)
      {
        int tile_id = map_string[tile_scan] - '0';
        int object_id = map_object_string[object_scan] - '0';
        tile_scan++;
        object_scan++;

        // Tile spawning
        if (tile_id != 0)
        {
          // Each tile becomes its own sprite, for easier collision detection
          Tile new_tile = Tile();

          new_tile.initGraphics(
            texture,
            sf::IntRect(
              tile_id * 16,
              0,
              16,
              16));
          new_tile.sprite.setScale(tile_scale, tile_scale);
          new_tile.sprite.setPosition(
            (float)j * tile_size * tile_scale,
            (float)i * tile_size * tile_scale);
          new_tile.id = tile_id;

          tiles.push_back(new_tile);
        }
        if (object_id != 0)
        // Object spawning
        {
          switch(object_id)
          {
            default:
            case 1:
            {
              auto* new_collectible = new Collectible();

              new_collectible->position = Vector2(
                (float)j * tile_size * tile_scale,
                (float)i * tile_size * tile_scale);
              new_collectible->updatePos();
              collectibles.push_back(new_collectible);
              break;
            }

            case 2:
            {
              auto* new_enemy = new Enemy();

              new_enemy->position = Vector2(
                (float)j * tile_size * tile_scale,
                (float)i * tile_size * tile_scale);
              new_enemy->spawn_pos = new_enemy->position;
              new_enemy->updatePos();
              enemies.push_back(new_enemy);
              break;
            }

            case 3:
            {
              auto* new_spike = new FallingSpike();

              new_spike->position = Vector2(
                (float)j * tile_size * tile_scale,
                (float)i * tile_size * tile_scale);
              new_spike->spawn_pos = new_spike->position;
              new_spike->updatePos();
              falling_spikes.push_back(new_spike);
              break;
            }
          }
        }
        else
        {
          continue;
        }
      }
    }
}

void Tilemap::setSolid(int tile_id)
{
  for (auto & tile : tiles)
  {
      if (tile.id == tile_id)
      {
        tile.is_solid = true;
      }
  }
}

void Tilemap::setSpawn(const Vector2& pos)
{
  player_spawn_pos = pos;
}

Tilemap::~Tilemap()
{
  tiles.clear();
  collectibles.clear();
  enemies.clear();
}
