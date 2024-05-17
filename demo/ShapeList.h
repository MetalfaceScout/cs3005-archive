#ifndef _SHAPELIST_H_
#define _SHAPELIST_H_

#include "Shape.h"
#include <vector>

class ShapeList {
public:
  ShapeList();
  ~ShapeList();
  void addShape(Shape *shape);
  int size() const;
  Shape* operator[](int i);
private:
  std::vector<Shape*> mShapes;
};


#endif /* _SHAPELIST_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
