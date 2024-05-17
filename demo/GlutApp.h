#ifndef _GLUTAPP_H_
#define _GLUTAPP_H_

#include "ShapeList.h"

class GlutApp {
public:
  GlutApp(int height, int width);
  void setSize(int height, int width);
  int getHeight() const;
  int getWidth() const;
  void display();

protected:
  int mHeight, mWidth;
  ShapeList mShapes;
};

#endif /* _GLUTAPP_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
