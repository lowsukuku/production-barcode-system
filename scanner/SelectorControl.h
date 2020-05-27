#pragma once

#include "GUIForm.h"

class SelectorControl : public GUIForm {
 private:
 public:
  SelectorControl(Point position) : GUIForm(position) {}
  void Navigate(Direction) override {}
  GUIItem &Select() {
    uint8_t selectedItem = 0;
    mGUI_InverseRegionPixels(0, selectedItem * 12, OLED_W, 12);

    while (mKey_GetTirgKeyStatus() != IS_PRESSED) {
      if (mKey_GetUpKeyStatus() == IS_PRESSED) {
        mGUI_InverseRegionPixels(0, selectedItem * 12, OLED_W, 12);
        selectedItem--;
        selectedItem %= 5;
        mGUI_InverseRegionPixels(0, selectedItem * 12, OLED_W, 12);

        while (mKey_GetUpKeyStatus() != IS_RELEASED) {
        }
      }
      if (mKey_GetDownKeyStatus() == IS_PRESSED) {
        mGUI_InverseRegionPixels(0, selectedItem * 12, OLED_W, 12);
        selectedItem++;
        selectedItem %= 5;
        mGUI_InverseRegionPixels(0, selectedItem * 12, OLED_W, 12);

        while (mKey_GetDownKeyStatus() != IS_RELEASED) {
        }
      }
    }
    while (mKey_GetTirgKeyStatus() == IS_PRESSED){}
    mGUI_InverseRegionPixels(0, selectedItem * 12, OLED_W, 12);
    return *(items.at(selectedItem));
  }

  void Render() override {
    uint8_t i = 0;
    for (auto &&item : items) {
      item->Show({0, i});
      i += 12;
      if (i > 64 - 12) i = 0;
    }
  }
};