#include "AppWorker.h"

void AppWorker::ConnectWifi(WifiController &controller) {
  SelectorControl selector = SelectorControl({0, 0});
  HotSpot selectedHotspot;

  mGUI_Printf(0, 0, "nibba", FontSize6X12);
  do {
    mGUI_Clear();
    for (auto &&hotSpot : controller.GetHotSpots()) {
      selector.AddItem((GUIItem *)&hotSpot, {0, 0});
    }
    selector.Render();
    selectedHotspot = (HotSpot &)selector.Select();
    // if (selectedHotspot.isOpen == false) {
    //   KeyboardControl keyboard = KeyboardControl({0, 0});
    //   keyboard.Render();
    //   selectedHotspot.Password = keyboard.GetLine();
    // }
  } while (/*controller.Connect(selectedHotspot) != WifiController::OK*/ true);
}