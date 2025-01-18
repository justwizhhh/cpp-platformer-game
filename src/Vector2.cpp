
#include "Vector2.h"
#include <cmath>

// ------------
//
// Basic struct code for all 2-dimensional coordinates in the game
//
// Initial version of code taken from the 'Space Invaders' worksheet project (Games in C++)
// Partially modified by myself
//
// ------------

/**
 *   @brief   Constructor.
 *   @details Requires values for it's x and y magnitudes.
 *   @return  void
 */
Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}

/**
 *   @brief   Copies a vector.
 *   @details Constructs a new Vector2 from an existing.
 *   @return  void
 */
Vector2::Vector2(const Vector2& rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;
}

/**
 *   @brief   Copies a vector.
 *   @details Updates Vector2 from an existing.
 *   @return  void
 */
Vector2& Vector2::operator=(const Vector2& rhs)
= default;


/**
 *   @brief   Sets vector.
 *   @details Allows for manual x and y toggling of the vector.
 *   @return  void
 */
void Vector2::set(float new_x, float new_y)
{
  x = new_x;
  y = new_y;
}

/**
 *   @brief   Returns magnitude.
 *   @details Returns the magnitude scale of the current vector.
 *   @return  float
 */
float Vector2::getMagnitude() const
{
  float magnitude = sqrtf((x * x) + (y * y));
  return magnitude;
}

/**
 *   @brief   Normalises vector.
 *   @details Turns the vector into a unit vector.
 *   @return  void
 */
void Vector2::normalise()
{
  float magnitude = getMagnitude();

  if (magnitude != 0)
  {
    return;
  }

  x /= magnitude;
  y /= magnitude;
}

/**
 *   @brief   Adds to the vector.
 *   @details Adds anothera vector's x and y values to the current vector.
 *   @return  void
 */
Vector2& Vector2::operator+=(const Vector2& rhs)
{
  this->x += rhs.x;
  this->y += rhs.y;

  return *this;
}

/**
 *   @brief   Scales the vector.
 *   @details Uses a single scalar value to adjust the vector.
 *   @return  void
 */
Vector2 Vector2::operator*(float scalar)
{
  Vector2 vec(*this);
  vec.x *= scalar;
  vec.y *= scalar;
  return vec;
}