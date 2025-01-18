
#ifndef PLATFORMERSFML_ANIMATION_H
#define PLATFORMERSFML_ANIMATION_H

#include <SFML/Graphics.hpp>

// ------------
//
// Code for storing all texture data for playing and stopping object animations
//
// ------------

class Animation
{
 public:
  Animation(const std::string& texture_path, float max_speed, int max_frames);

  void play();
  void updateAnim();
  void stop();

  sf::Texture texture;
  sf::IntRect texture_rect;

 private:
  bool is_playing = true;
  sf::Clock anim_timer;

  int anim_frames = 0;
  float anim_speed = 0;
  float anim_progress = 0;
};

#endif // PLATFORMERSFML_ANIMATION_H
