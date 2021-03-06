#pragma once

#include "../Resources/MenuBase.h"
#include "../../../Common/MessageHandler/Interface.h"
#include "../../../Common/Trace.h"
#include "../../../Common/Messages/ClientInternal/IpMessage.h"

class JoinMenu : public MenuBase {
public:
  JoinMenu();
  ~JoinMenu();

  void init() override;
  void uninit() override;

  void handleNewText(sf::Uint32 newChar) override;

private:
  std::string mIpString;
  std::shared_ptr<GUIComponent> mIPInputText;
  Interface mPc;
};