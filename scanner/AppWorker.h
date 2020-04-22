#pragma once

#include "HTTPClient.h"
#include "KeyboardControl.h"
#include "SelectorControl.h"
#include "TCPSocket.h"
#include "WifiController.h"

class AppWorker {
 private:
  /* data */
 public:
  AppWorker(/* args */) {}
  ~AppWorker() {}

  void Run() {
    WifiController controller;
    SelectorControl<HotSpot> selector = SelectorControl<HotSpot>({0, 0});
    for (auto &&hotSpot : controller.GetHotSpots()) {
      selector.AddItem(hotSpot, {0, 0});
    }
    selector.Render();
    auto selectedHotspot = selector.Select();
    if (selectedHotspot.isOpen == false) {
      KeyboardControl keyboard;
      selectedHotspot.Password =
    }
    controller.Connect(selector.Select());
    selector.Select();
  }
};