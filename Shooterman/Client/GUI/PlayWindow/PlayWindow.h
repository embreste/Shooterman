#pragma once

#include "../Resources/MenuBase.h"
#include "../SpriteManager.h"
#include "../../../Common/Messages/SpriteMessage.h"

class PlayWindow : public MenuBase {
public:
  PlayWindow();
  ~PlayWindow();

  bool render(std::shared_ptr<sf::RenderWindow> window, sf::Vector2f mousePosition) override;

private:
  SpriteManager* mSpriteManager;
  Subscriber mSpriteListSubscriber;
};