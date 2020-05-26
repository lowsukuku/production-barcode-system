#pragma once

struct Point {
  uint8_t x;
  uint8_t y;
};
class GUIItem {
 private:
 public:
  virtual void Show(const Point &position){};
};