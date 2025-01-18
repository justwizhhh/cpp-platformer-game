
#include "GameObject.h"
#include "Enemy.h"

#include "random"

// ------------
//
// Main class for the spider enemy, that the player can get hurt by
//
// ------------

Enemy::Enemy()
{
  initialiseSprite("Data/Images/New/Hazards/enemy_spider.png");
  sprite.setTextureRect(sf::IntRect(
    0,
    0,
    (int)sprite.getGlobalBounds().width / 2,
    (int)sprite.getGlobalBounds().height));
  sprite.setScale(sprite_scale, sprite_scale);

  spider_web.setFillColor(sf::Color::White);

  // This will add a bit of variety to the spider's movement
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<> range(0, 10);
  move_progress = (float)range(rng);
}

//
// Updates the current enemy's velocity and position
//
void Enemy::move(float dt)
{
  move_progress += move_speed * dt;
  position.y = spawn_pos.y + std::sin(move_progress) * move_amplitude;

  // Making sure the web graphic always sticks to the spider itself
  spider_web.setPosition(
    position.x + (sprite.getGlobalBounds().width / 2) - (spider_web_width / 2),
    0);
  spider_web.setSize(sf::Vector2f (spider_web_width, position.y));
}

//
// Puts the enemy back to its original start position
//
void Enemy::respawn()
{
  position = spawn_pos;
}

// Animates the current enemy
void Enemy::animate()
{
  sprite.setTextureRect(animation.texture_rect);
  animation.updateAnim();
}