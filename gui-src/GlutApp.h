#ifndef _GLUTAPP_H_
#define _GLUTAPP_H_

#define _DEBUG_

#include "ActionData.h"
#include "MenuData.h"
#include <sstream>

class GlutApp {
public:
  GlutApp(int height, int width);

  enum InteractionMode {IM_FRACTAL, IM_COLORTABLE, IM_COLOR};
  enum FractalMode {M_MANDELBROT, M_JULIA, M_COMPLEX};

  enum GradientColorIndex {
    COLOR_1,
    COLOR_2,
    COLOR_3,
    COLOR_4,
    COLOR_5,
    COlOR_6,
    COLOR_7,
    COLOR_8,
    COLOR_9
  };

  /*
  Exam
  */
  GradientColorIndex fetchColor() const;

  /*
  EXAM!
  */
  void increaseChannel(GradientColorIndex color, const int& channel);

  /*
  EXAM!
  */
  void decreaseChannel(GradientColorIndex color, const int& channel);

  /*
  EXAM!
  */
  void increaseRed(GradientColorIndex color);

  /*
  EXAM!
  */
  void increaseGreen(GradientColorIndex color);

  /*
  EXAM!
  */
  void increaseBlue(GradientColorIndex color);

  /*
  EXAM1
  */
  void decreaseRed(GradientColorIndex color);

  /*
  EXAM
  */
  void decreaseGreen(GradientColorIndex color);

  /*
  EXAM
  */
  void decreaseBlue(GradientColorIndex color);

  /*
  EXAM EXTRA
  */
  void zoomAndMove(int x, int y);

  /*
  EXAM EXTRA
  */
  void writeImage();

  void setSize(int height, int width);

  void setPlaneSize(const double& MinX, const double& MaxX, const double& MinY, const double MaxY);

  void setColorTableSize(const unsigned int& size);

  /*
  \ Sets color 1. Does not update anything.
  */
  void setColor1(const int& red, const int& green, const int& blue);

  /*
  \ Sets color 2. Also does not update anything.
  */
  void setColor2(const int& red, const int& green, const int& blue);

  void setColor(GradientColorIndex color_selection, const int& red, const int& green, const int& blue);


  int getHeight() const;
  int getWidth() const;
  void display();

  /*
  \ Toggle showing the parameters of the app on the right.
  */
  void showParametersToggle();

  /*
  / For each column in the display, calculate index into color table with
  / i = column * color_table_size / width_of_display. Use the 'i'th color
  / from mActionData's color table. 
  /
  */
  void displayColorTable();

  /*
  \ Draws the parameters on the screen.
  */
  void displayParameters();

  /*
  / Set the interaction mode.
  */
  void setInteractionMode(InteractionMode mode);
  void setInteractionMode(InteractionMode mode, GradientColorIndex color);

  /*
  \ Gets the interaction mode.
  */
  InteractionMode getInteractionMode() {return mInteractionMode;}

  /*
  / Uses set-color-table-size and set-color-gradient to configure the color table using
  / mNumColor, mColor1, and mColor2.
  */
  void setColorTable();

  /*
  \ Sets the color table randomly.
  \ Sets color one and two to random values.
  */
  //void setColorTableRandom();

  /*
  / If the number of colors is more than 10, decrease by dividing by 1.1.
  / Uses setColorTable() and gridApplyColorTable() to update the image.
  */
  void decreaseColorTableSize();

  /*
  / If the number of colors is less than 1024, increase number of colors by multiplying
  / by 1.1. Uses setColorTable and gridApplyColorTable.
  */
  void increaseColorTableSize();

  /*
  / Randomly chooses RGB values for color 1.
  */
  void randomColor1();

  /*
  / Randomly chooses RGB values for color 2.
  */
  void randomColor2();

  /*
  \ Randomly choose RGB value for the given color.
  */
  void randomColor(GradientColorIndex index);

  /*
  
  */

  /*
  \ Calculates Dx and Dy for zoom and move functions.
  */
  inline void calculateDxAndDy(double& dx, double& dy);

  /*
  \ Calculate Dx for move functions.
  */
  inline double calculateDx();

  /*
  \ Calculate Dy for move functions.
  */  
  inline double calculateDy();


  /*
  / Decrease the size of the *view window* to 0.9 of its size.
  / dX is (1.0-0.9)*(mMaxX - mMinX) / 2.0
  */
  void zoomIn();

  /*
  / Does zoom in but backwards, only if plane is not > 2.0.
  / See zoomIn for details
  */
  void zoomOut();

  /*
  \ Scales the view up vertically.
  */
  void scaleUpVertical();

  /*
  \ Scales the view down vertically.
  */
  void scaleDownVertical();

  /*
  \ Scales the view up horizontally.
  */
  void scaleUpHorizontal();

  /*
  \ Scales the view down horizontally.
  */
  void scaleDownHorizontal();

  /*
  / Move the viewport to the left by 0.05. dX is same detailed in zoomIn().
  / If mMinX - dx < 2.0, then subtract dX from mMinx and mMaxx.
  */
  void moveLeft();

  /*
  / Same as moveLeft, but moves right (plot twist)
  / See moveLeft for details
  */
  void moveRight();

  /*
  / Same as moveLeft, but up!
  */
  void moveUp();

  /*
  / Same as moveLeft, but down :(
  */
  void moveDown();

  /*
  \ Get the current fractal mode.
  \ 
  */
  FractalMode getFractalMode() {return mFractalMode;}

  /*
  \ Change the value of mFractalMode.
  \ Automatically calculates the fractal.
  */
  void setFractalMode(FractalMode mode);

  /*
  / Increases the max number by mutliplying it by 1.1.
  */
  void increaseMaxNumber();

  /*
  / Decreases the max number by dividing it by 1.1/
  */
  void decreaseMaxNumber();

  /*
  / Sets the A and B parameters of the Julia set.
  / If mFractalMode == M_MANDELBROT, mA = mMinX + x * delta_x
  / and mB = mMinY + y * delta_y
  */
  void setABFromMouseCoords(const int& x, const int& y);

  /*
  \ Sets AB.
  */
  void setAB(const double& a, const double& b);

  /*
  | Reset Juila A,B values to default.
  */
  void resetAB();

  /*
  / Sets plane dimensions to the default square.
  */
  void resetPlane();

  /*
  \ Reset the color table to the default values.
  \ 
  */
  void resetColorTable();

  /*
  \ Reset the color table, plane, and Julia AB to default values.
  */
  void resetAll();

  /*
  / Uses mFractalMode to choose which fractal is set.
  / If Julia is selected, calls juliaParameters().
  / Calculates the output image using existing data members.
  */
  void createFractal();


  /*
  \ Increases the amount of colors in the gradient. Max of 9.
  */
  void increaseGradientAmount();

  /*
  \ Decreases the amount of colors in the gradient. Min of 2.
  */
  void decreaseGradientAmount();

  /*
  /FINAL!!!!
  */
  void toggleHSVColor();



  void createJulia();
  void createJulia(const double& paramA, const double& paramB);

  void createMandelbrot();

  void createComplexFractal();

  void recalculateGrid(bool force_recalc);
  void clearStreams();

  void doAction(std::string action, std::stringstream &ss);
  void doAction(std::string action);

protected:
  int mHeight, mWidth;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  ActionData mActionData;
  MenuData mMenuData;

  double mMinX;
  double mMaxX;
  double mMinY;
  double mMaxY;

  //First parameter for julia set
  double mA;
  //Second parameter for julia set
  double mB;

  InteractionMode mInteractionMode;
  GradientColorIndex mColorModeSelector;
  FractalMode mFractalMode;

  int mMaxNumber;

  std::vector<Color> mColors;
  unsigned int mNumGradientColors;
  bool mHSVColor;

  int mNumColor;

  int mImageNumber;

private:

  bool mShowParameters;

  const double VIEW_BOUNDARY = 2.0; //I don't know if there's any reason to change this but yeah

  enum ViewBoundDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  enum DrawPositions {
    PARAM_DRAW_PLACEHOLDER,
    PARAM_DRAW_POS_0,
    PARAM_DRAW_POS_1,
    PARAM_DRAW_POS_2,
    PARAM_DRAW_POS_3,
    PARAM_DRAW_POS_4,
    PARAM_DRAW_POS_5,
    PARAM_DRAW_POS_6,
    PARAM_DRAW_POS_7,
    PARAM_DRAW_POS_8,
    PARAM_DRAW_POS_9,
    PARAM_DRAW_POS_10,
    PARAM_DRAW_POS_11,
    PARAM_DRAW_POS_12,
    PARAM_DRAW_POS_13
  };

  
  /*
  \ Checks the bounds for up, left, right, and down. Returns false if
  \ selected bound is past 2.0.
  */
  bool checkBound(const ViewBoundDirection direction, const double& delta) const;

};

#endif /* _GLUTAPP_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
