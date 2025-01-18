
#include "Vector2.h"
#include "GameObject.h"

#include <iostream>

// ------------
//
// The template class for all interactive game elements which can be moved around
//
// ------------

GameObject::GameObject() : position(0, 0)
{
  visibility = true;
}

GameObject::~GameObject() = default;

/*
 * @brief   Updates the object's current sprite
 * @details Load in a texture for the current object's sprite
 * @return  void
 */

bool GameObject::initialiseSprite(const std::string& file_path)
{
  if (!texture.loadFromFile(file_path))
  {
    std::cout << " Texture from " << file_path << "not found!" << std::endl;
    return false;
  }
  else
  {
    sprite.setTexture(texture);
    return true;
  }
}

/*
 * @brief   Updates the object's current position
 * @details Takes the Vector2 'position' value and assigns it to the sprite
 * @return  void
 */
void GameObject::updatePos()
{
  sprite.setPosition(position.x, position.y);
}


/*
 * @brief   Gets the object's mid-point
 * @details Returns the centre position of the object's current sprite
 * @return  Vector2
 */
Vector2 GameObject::getMidPoint() const
{
  float mid_point_x = position.x + (sprite.getGlobalBounds().width / 2);
  float mid_point_y = position.y + (sprite.getGlobalBounds().height / 2);

  Vector2 new_vector(mid_point_x, mid_point_y);

  return new_vector;
}


/*
 * @brief   Checks if there is a collision happening
 * @details Checks for if the current object's sprite is colliding another sprite
 * @return  Vector2
 */
Vector2 GameObject::collision(const Vector2& offset, const sf::Sprite& other_object)
{
  Vector2 side(0, 0);

  // Basic AABB collision detection
  Vector2 origin = Vector2(
    sprite.getOrigin().x * sprite_scale,
    sprite.getOrigin().y * sprite_scale);

  // Credit for the collision overlap code inspiration goes to Kevin Workman
  // https://happycoding.io/tutorials/processing/collision-detection#rectangle-rectangle-collision-detection

  // Potential horizontal overlap
  bool collision_x = (
    position.x - origin.x + sprite.getGlobalBounds().width + offset.x
      > other_object.getPosition().x &&
    position.x - origin.x + offset.x
      < other_object.getPosition().x + other_object.getGlobalBounds().width &&
    position.y - origin.y + sprite.getGlobalBounds().height
      > other_object.getPosition().y &&
    position.y - origin.y
      < other_object.getPosition().y + other_object.getGlobalBounds().height);

  // Potential vertical overlap
  bool collision_y = (
    position.x - origin.x + sprite.getGlobalBounds().width
      > other_object.getPosition().x &&
    position.x - origin.x
      < other_object.getPosition().x + other_object.getGlobalBounds().width &&
    position.y - origin.y + sprite.getGlobalBounds().height + offset.y
      > other_object.getPosition().y &&
    position.y - origin.y + offset.y
      < other_object.getPosition().y + other_object.getGlobalBounds().height);

  Vector2 bounds(
    sprite.getGlobalBounds().width,
    sprite.getGlobalBounds().height);
  Vector2 other_bounds(
    other_object.getGlobalBounds().width,
    other_object.getGlobalBounds().height);

  // Calculate position with offset considering sprite's origin
  float x = (position.x - sprite.getOrigin().x + (bounds.x / 2)) + offset.x;
  float y = (position.y - sprite.getOrigin().y + (bounds.y / 2)) + offset.y;
  float other_x = (other_object.getPosition().x + (other_bounds.x / 2));
  float other_y = (other_object.getPosition().y + (other_bounds.y / 2));

  // If there definitely is an overlap, find out exactly how much of an overlap
  if (collision_x)
  {
    // Find the position that the object would need to be moved to, to stop
    // overlapping with the other object
    side.x = std::min(
               position.x + bounds.x + offset.x,
               other_object.getPosition().x + other_bounds.x)
             - std::max(
                 position.x,
                 other_object.getPosition().x);
    if (x >= other_x)
      side.x *= -1;
  }

  if (collision_y)
  {
    side.y = std::min(
               position.y + bounds.y + offset.y,
               other_object.getPosition().y + other_bounds.y)
             - std::max(
                 position.y,
                 other_object.getPosition().y);
    if (y >= other_y)
      side.y *= -1;
  }
  return Vector2(side.x, side.y);
}

/*
 * @brief   Checks if there is a collision happening at one point (UNUSED)
 * @details Checks for if there is a collision happening at a set coordinate point with another object
 * @return  Vector2
 */
bool GameObject::collisionPoint(const Vector2& point, const sf::Sprite& other_object)
{
  bool collision_x =
    point.x > other_object.getPosition().x &&
    point.x < other_object.getPosition().x + other_object.getGlobalBounds().width;
  bool collision_y =
    point.y > other_object.getPosition().y &&
    point.y < other_object.getPosition().y + other_object.getGlobalBounds().height;

  if (collision_x && collision_y)
  {
    return true;
  }
  else
  {
    return false;
  }
}

