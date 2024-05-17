#ifndef _SHAPE_H_
#define _SHAPE_H_

class Shape {
public:
  Shape(int x, int y);
  virtual ~Shape();  // force VTable construction
  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
private:
  int mX;
  int mY;
};

#endif /* _SHAPE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
