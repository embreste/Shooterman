#include "SpriteManager.h"

SpriteManager::SpriteManager() { mName = "CLIENT: SPRITE_MANAGER"; }

SpriteManager::~SpriteManager() { }

void SpriteManager::loadSprites() {
  std::shared_ptr<sf::Texture> texture = loadTexture("Player.png");
  sf::Sprite sprite;
  sprite.setTexture(*texture);
  //mSpriteMap[33] = std::make_pair(sprite, texture);
  mSpriteMap[0] = std::make_pair(sprite, texture);
  
  std::shared_ptr<sf::Texture> wall1Texture = loadTexture("wall1.png");
  sf::Sprite wall1Sprite;
  wall1Sprite.setTexture(*wall1Texture);
  mSpriteMap[1] = std::make_pair(wall1Sprite, wall1Texture);
  
  std::shared_ptr<sf::Texture> wall2Texture = loadTexture("verticalWall1.png");
  sf::Sprite wall2Sprite;
  wall2Sprite.setTexture(*wall2Texture);
  mSpriteMap[2] = std::make_pair(wall2Sprite, wall2Texture);
}

std::shared_ptr<sf::Texture> SpriteManager::loadTexture(std::string fileName) {
  std::shared_ptr<sf::Texture> playerTexture = std::make_shared<sf::Texture>();
  if (!playerTexture->loadFromFile(SPRITE_FILE_PATH + fileName)) {
    TRACE_ERROR("could not load file " << SPRITE_FILE_PATH << fileName);
  }
  return playerTexture;
}