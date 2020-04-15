#pragma once

#include <vector>

#include "HotSpot.h"

class WifiController {
 private:
  bool connectionStatus;
  std::vector<HotSpot> availableHotSpots;
  std::vector<HotSpot> savedHotSpots;

  void UpdateHotSpotsList() {}
  void GetSavedHotSpots() {}
  void SaveHotSpots() {}

 public:
  enum WifiConnectStatus { OK, WrongHotspot, Error };
  WifiController() {}
  ~WifiController() {}

  std::vector<HotSpot> GetHotSpots() {}
  WifiConnectStatus Connect(HotSpot hotSpot, std::string password = "") {
    return WifiConnectStatus::OK;
  }
  bool Disconnect() { return true; }
};
