#pragma once

#include <string>

#include "GUIItem.h"

struct HotSpot : GUIItem {
  std::string SSID;
  bool isOpen;
  std::string Password;
  void Show(const Point &position) override {
    mGUI_Printf(position.x, position.y, SSID.c_str(), FontSize6X12);
  }
};
