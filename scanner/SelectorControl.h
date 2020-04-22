#pragma once

#include "GUIForm.h"

template <class SelectableElement>
class SelectorControl : public GUIForm {
 private:
 public:
  SelectorControl(Point position) : GUIForm(position) {}
  void Navigate(Direction) override {}
  SelectableElement &Select() {}
};