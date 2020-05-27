#include "WifiController.h"

void WifiController::UpdateHotSpotsList() {
  unsigned char name[33] = {0};
  unsigned char encryptionStatus = 0;
  unsigned char hotspotsCount = mWiFi_StationModeSearchHotSpot();
  availableHotSpots.clear();
  for (size_t i = 0; i < hotspotsCount; i++)
  {
    HotSpot hotspot;
    mWiFi_StationModeGetHotSpotInfo(name, &encryptionStatus, i);
    hotspot.SSID = (const char*)name;
    if (encryptionStatus == ENCRYPTED) {
      hotspot.isOpen = false;
    }
    availableHotSpots.push_back(hotspot);
  }
}