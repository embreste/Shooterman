#include "Input.h"

#include <cstdint>

#include "../../Common/Trace.h"

Input::Input() {
  mName = "CLIENT: INPUT";
  TRACE_INFO("Starting module...");
  mInputThread = std::make_unique<std::thread>(&Input::readInput, this);
  TRACE_INFO("Starting module done");
}

void Input::readInput() {
  MessageHandler::get().subscribeToSystemMessages(&mSystemMessageSubscriber);
  MessageHandler::get().subscribeToGameStateMessages(&mGameStateMessageSubscriber);
  MessageHandler::get().subscribeToMouseMessages(&mMouseMessageSubscriber);
  //Subscriber s;
  //MessageHandler::get().subscribeTo("ClientMain", &s);
  PrivateCommunication* pc = new PrivateCommunication();
  MessageHandler::get().publishInterface("ClientInputList", pc);
  mCurrentGameState = GAME_STATE::MAIN_MENU;

  std::uint32_t keyboardBitmask;
  while (mRunning) {
    switch (mCurrentGameState) {
      case GAME_STATE::MAIN_MENU:
        // Do nothing
        break;
      case GAME_STATE::LOBBY:
        // Do nothing
        break;
      case GAME_STATE::JOIN:
        // Do nothing
        break;
      case GAME_STATE::PLAYING:
        keyboardBitmask = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          keyboardBitmask += A_KEY;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          keyboardBitmask += D_KEY;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          keyboardBitmask += W_KEY;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          keyboardBitmask += S_KEY;
        }

        getLatestMousePosition();
        {
        //if (keyboardBitmask != 0 && mLastMousePosition.) {
          InputMessage im(keyboardBitmask, mLastMousePosition.x, mLastMousePosition.y);
          pc->pushMessage(im.pack());
          //MessageHandler::get().pushInputMessage(inputKeyPacket);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
          GameStateMessage gsm(GAME_STATE::MAIN_MENU);
          MessageHandler::get().pushGameStateMessage(gsm.pack());
        }

        //TRACE_INFO("Received data: " << s.getMessageQueue().size());

        break;
      case GAME_STATE::OPTIONS:
        break;
      default:
        TRACE_ERROR("Unknown game state: " << mCurrentGameState);
    }

    sf::sleep(sf::milliseconds(FRAME_LENGTH_IN_MS));
    handleGameStateMessages();
    handleSystemMessages();
  }

  MessageHandler::get().unpublishInterface("ClientInputList");
  delete pc;
  MessageHandler::get().unsubscribeAll(&mSystemMessageSubscriber);
}

void Input::handleSystemMessages() {
  std::queue<sf::Packet> systemMessageQueue = mSystemMessageSubscriber.getMessageQueue();
  sf::Packet systemMessage;
  while (!systemMessageQueue.empty()) {
    systemMessage = systemMessageQueue.front();
    systemMessageQueue.pop();

    int messageId = 0;
    systemMessage >> messageId;
    switch (messageId) {
    case SHUT_DOWN:
      mRunning = false;
      TRACE_INFO("Preparing to shut down");
      break;
    default:
      TRACE_WARNING("Unknown system message : " << messageId);
    }
  }
}

void Input::handleGameStateMessages() {
  std::queue<sf::Packet> gameStateMessageQueue = mGameStateMessageSubscriber.getMessageQueue();
  sf::Packet gameStateMessage;
  while (!gameStateMessageQueue.empty()) {
    gameStateMessage = gameStateMessageQueue.front();
    gameStateMessageQueue.pop();

    GameStateMessage gsm;
    gsm.unpack(gameStateMessage);
    mCurrentGameState = gsm.getGameState();
  }
}

void Input::getLatestMousePosition() {
  std::queue<sf::Packet> mouseMessageQueue = mMouseMessageSubscriber.getMessageQueue();
  sf::Packet mouseMessage;

  while (!mouseMessageQueue.empty()) {
    mouseMessage = mouseMessageQueue.front();
    mouseMessageQueue.pop();

    MouseMessage mm;
    mm.unpack(mouseMessage);
    if (mm.getPosition() != sf::Vector2i()) {
      mLastMousePosition = mm.getPosition();
    }
  }  
}

void Input::shutDown() {
  TRACE_INFO("Shutdown of module requested...");
  mRunning = false;
  mInputThread->join();
  TRACE_INFO("Shutdown of module done");
}