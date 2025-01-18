#ifndef VECTOR2_H
#define VECTOR2_H

// ------------
//
// Basic struct code for all 2-dimensional coordinates in the game
//
// Initial version of code taken from the 'Space Invaders' worksheet project (Games in C++)
// Partially modified by myself
//
// ------------

struct Vector2
{
  // Construction
  explicit Vector2(float x_ = 0.0, float y_ = 0.0);
  Vector2(const Vector2& rhs);

  // Basic operations
  Vector2& operator=(const Vector2& rhs);
  void set(float new_x, float new_y);

  Vector2 operator*(float scalar);
  Vector2& operator+=(const Vector2& rhs);

  float getMagnitude() const;
  void normalise();

  // data
  float x = 0;
  float y = 0;
};

#endif // VECTOR2_H
