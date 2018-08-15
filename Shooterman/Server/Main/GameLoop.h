#pragma once
#include <thread>
#include "../../Client/MessageHandler/MessageHandler.h"
#include "../../Common/KeyBindings.h"

class GameLoop {
public:
  GameLoop();
  void start();
  void stop();

private: 
  bool mRunning;
  std::thread* mGameLoopThread;
  void gameLoop();
  void moveCircle(sf::CircleShape &circle, float velocityX, float velocityY);
};

enum class GameLoopState { 
  LOBBY, 
  SETUP_GAME, 
  PLAYING, 
  GAME_OVER,
  EXIT
};