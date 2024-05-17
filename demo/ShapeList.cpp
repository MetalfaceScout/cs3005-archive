#include "ShapeList.h"

ShapeList::ShapeList() {
}
ShapeList::~ShapeList() {
  unsigned int i;
  for(i = 0; i < mShapes.size(); i++) {
    delete mShapes[i];
  }
}
void ShapeList::addShape(Shape *shape) {
  mShapes.push_back(shape);
}
int ShapeList::size() const {
  return static_cast<int>(mShapes.size());
}
Shape* ShapeList::operator[](int i) {
  Shape *ptr;
  if(i >= 0 && i < size()) {
    ptr = mShapes[i];
  } else {
    ptr =0;
  }
  return ptr;
}
