#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "Shape.h"

class Rectangle: public Shape {
public:
  Rectangle(int x, int y, int w, int h);
  virtual ~Rectangle();
  int getWidth() const;
  int getHeight() const;

  void setWidth(int w);
  void setHeight(int h);
protected:
  int mWidth;
  int mHeight;
};

#endif /* _RECTANGLE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
