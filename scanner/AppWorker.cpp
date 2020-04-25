#include "AppWorker.h"

void AppWorker::ConnectWifi(WifiController &controller) {
  SelectorControl<HotSpot> selector = SelectorControl<HotSpot>({0, 0});
  HotSpot selectedHotspot;
  do {
    for (auto &&hotSpot : controller.GetHotSpots()) {
      selector.AddItem(hotSpot, {0, 0});
    }
    selector.Render();
    selectedHotspot = selector.Select();
    if (selectedHotspot.isOpen == false) {
      KeyboardControl keyboard = KeyboardControl({0, 0});
      keyboard.Render();
      selectedHotspot.Password = keyboard.GetLine();
    }
  } while (controller.Connect(selectedHotspot) != WifiController::OK);
}