#pragma once

#include "GUIForm.h"

class KeyboardControl : public GUIForm {
 private:
 public:
  KeyboardControl(Point position) : GUIForm(position) {}
  void Navigate(Direction) override {}
  std::string GetLine() { return ""; }
};