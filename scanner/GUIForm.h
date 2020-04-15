#pragma once

#include <map>

#include "GUIItem.h"

struct Point {
  uint8_t x;
  uint8_t y;
};

class GUIForm {
 private:
  std::map<GUIItem &, Point> items;

 public:
  enum Direction { Up, Down, Left, Right };

  GUIForm(Point position) {}
  ~GUIForm() {}

  bool AddItem(GUIItem &, Point) { return true; }
  bool RemoveItem(GUIItem &) { return true; }
  void Render() {}
  virtual void Navigate(Direction) {}
};
