#pragma once

#include <string>

#include "GUIItem.h"

struct HotSpot : GUIItem {
  std::string SSID;
  bool isOpen;
  std::string Password;
  void Show() override {}
};
