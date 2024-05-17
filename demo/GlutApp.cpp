#include "GlutApp.h"
#include "Rectangle.h"
#include "glut_app.h"

GlutApp::GlutApp(int height, int width)
  : mHeight(height), mWidth(width) {
  Rectangle *ptr = new Rectangle(width/4, height/3, width/2, height/2);
  mShapes.addShape(ptr);
}

void GlutApp::setSize(int height, int width) {
  mHeight = height;
  mWidth = width;
}

int GlutApp::getHeight() const {
  return mHeight;
}
int GlutApp::getWidth() const {
  return mWidth;
}

void GlutApp::display() {
  int i;
  for(i = 0; i < mShapes.size(); i++) {
    Shape *ptr = mShapes[i];
    Rectangle *rptr = dynamic_cast<Rectangle*>(ptr);
    if(rptr != 0) {
      int x = rptr->getX();
      int y = rptr->getY();
      int w = rptr->getWidth();
      int h = rptr->getHeight();
      DrawRectangle(x, y, x+w, y+h);
    }
  }
}

