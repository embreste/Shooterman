#include "SpriteManager.h"
#include <iostream>

SpriteManager::SpriteManager() {

}

SpriteManager::~SpriteManager() {
  for (auto it = mSpriteMap.begin(); it != mSpriteMap.end(); it++) {
    delete it->second.second;
  }
}

void SpriteManager::loadSprites() {
  sf::Texture* playerTexture = new sf::Texture();
  if (!playerTexture->loadFromFile("Client/Resources/Sprites/Player.png")) {
    std::cout << "ERROR could not load file Client/Resources/Sprites/Player.png" << std::endl;
  }
  sf::Sprite sprite;
  sprite.setTexture(*playerTexture);
  mSpriteMap[33] = std::make_pair(sprite, playerTexture);
}