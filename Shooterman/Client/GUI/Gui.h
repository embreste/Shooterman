#pragma once

#include <thread>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "SpriteManager.h"
#include "Resources/MenuBase.h"
#include "MainMenu/MainMenu.h"
#include "LobbyMenu/LobbyMenu.h"
#include "JoinMenu/JoinMenu.h"
#include "../MessageHandler/MessageHandler.h"
#include "../../Common/Subscriber.h"
#include "../../Common/MessageId.h"
#include "../../Common/Trace.h"
#include "../../Common/Constants.h"
#include "../../Common/Messages/SpriteMessage.h"
#include "../../Common/Messages/GameStateMessage.h"
#include "../../Common/Messages/MouseMessage.h"

class Gui : Trace {
public:
  Gui();

  void shutDown();

private:
  bool mDebugEnabled = true;
  bool mWindowOpen;
  std::unique_ptr<std::thread> mGuiThread;
  std::shared_ptr<sf::RenderWindow> mWindow;
  Subscriber mSystemMessageSubscriber;
  Subscriber mGameStateMessageSubscriber;
  Subscriber mSpriteListSubscriber;
  SpriteManager* mSpriteManager;
  GAME_STATE mCurrentGameState;
  bool mRenderNeeded;
  bool mLeftButtonAlreadyPressed;
  std::map<GAME_STATE, MenuBase*> mMenuMap;

  void init();
  void render();
  void handleWindowEvents();
  void renderGameState(GAME_STATE gameState);
  void handleSystemMessages();
  void handleGameStateMessages();
  void playing();
};