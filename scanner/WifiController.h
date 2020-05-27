#pragma once

extern "C" {
#include "SDK/MS3690Lib/SysCallLib.h"
#include "SDK/MS3690Lib/ms3690_lib.h"
}

#include <vector>

#include "HotSpot.h"

class WifiController {
 private:
  bool connectionStatus;
  std::vector<HotSpot> availableHotSpots;
  std::vector<HotSpot> savedHotSpots;

  void UpdateHotSpotsList();
  void GetSavedHotSpots() {}
  void SaveHotSpots() {}

 public:
  enum WifiConnectStatus { OK, WrongHotspot, Error };
  WifiController() {}
  ~WifiController() {}

  std::vector<HotSpot> GetHotSpots() {
    UpdateHotSpotsList();
    return availableHotSpots;
  }
  WifiConnectStatus Connect(HotSpot& hotSpot,
                            const std::string& password = "") {
    return WifiConnectStatus::OK;
  }
  bool Disconnect() { return true; }
};
