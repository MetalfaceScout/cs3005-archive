#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int w, int h)
  : Shape(x,y), mWidth(w), mHeight(h) {
}
Rectangle::~Rectangle() {
}
int Rectangle::getWidth() const {
  return mWidth;
}
int Rectangle::getHeight() const {
  return mHeight;
}

void Rectangle::setWidth(int w) {
  mWidth = w;
}
void Rectangle::setHeight(int h) {
  mHeight = h;
}
