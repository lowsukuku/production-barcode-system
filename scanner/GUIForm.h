#pragma once

#include <map>

#include "GUIItem.h"

class GUIForm {
 private:
 protected:
  Point position;
  // std::map<GUIItem &, Point> items;
  std::vector<GUIItem*> items;

 public:
  enum Direction { Up, Down, Left, Right };

  GUIForm(Point position) : position(position) {}
  ~GUIForm() {}

  bool AddItem(GUIItem *item, Point point) {
    items.push_back(item);
    return true;
  }
  bool RemoveItem(GUIItem &) { return true; }
  virtual void Render() {}
  virtual void Navigate(Direction) {}
};
