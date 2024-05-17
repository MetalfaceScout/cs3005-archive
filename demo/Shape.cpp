#include "Shape.h"

Shape::Shape(int x, int y) 
  : mX(x), mY(y) {
}
Shape::~Shape() {
}
int Shape::getX() const {
  return mX;
}
int Shape::getY() const {
  return mY;
}
void Shape::setX(int x) {
  mX = x;
}
void Shape::setY(int y) {
  mY = y;
}
