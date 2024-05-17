#include "GlutApp.h"
#include "ColorTable.h"
#include "ComplexFractal.h"
#include "MenuData.h"
#include "glut_app.h"
#include "image_menu.h"
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <GL/gl.h>

#include <iostream>

GlutApp::GlutApp(int height, int width)
  : //Startup initilzation
    mHeight(height), mWidth(width),
    mActionData(mInputStream, mOutputStream),
    mMinX(-2.0), mMaxX(2.0), mMinY(-2.0), mMaxY(2.0),
    mA(1.99), mB(-1.2),
    mInteractionMode(IM_FRACTAL),
    mColorModeSelector(COLOR_1),
    mFractalMode(M_MANDELBROT),
    mMaxNumber(200),
    mColors(),
    mNumGradientColors(2),
    mHSVColor(false),
    mNumColor(32),
    mImageNumber(1),
    mShowParameters(false)
  {

  configureMenu(mMenuData);
  mActionData.setGrid(new MandelbrotSet);

  mColors.resize(9);

  mColors[COLOR_1].setRed(254);
  mColors[COLOR_1].setGreen(12);
  mColors[COLOR_1].setBlue(50);

  mColors[COLOR_2].setRed(30);
  mColors[COLOR_2].setGreen(15);
  mColors[COLOR_2].setBlue(45);

  setColorTable();
  recalculateGrid(true);


  // // read1
  // mOutputStream.clear();
  // mInputStream.clear();
  // mInputStream.str("pretty-mandel-1.ppm");
  // takeAction("read1", mMenuData, mActionData);
  
  // // copy
  // mOutputStream.clear();
  // mInputStream.clear();
  // mInputStream.str("");
  // takeAction("copy", mMenuData, mActionData);
}

void GlutApp::showParametersToggle() {
  if (mShowParameters) {
    mShowParameters = false;
  } else {
    mShowParameters = true;
  }
  #ifdef _DEBUG_
  std::cout << "mShowParameters: " << mShowParameters << std::endl;
  #endif
}

void GlutApp::toggleHSVColor() {
  if (mHSVColor) {
    mHSVColor = false;
  } else {
    mHSVColor = true;
  }
  setColorTable();
  recalculateGrid(true);
  #ifdef _DEBUG_
  std::cout << "mHSVColor: " << mHSVColor << std::endl;
  #endif
}


void GlutApp::setSize(int height, int width) {
  mHeight = height;
  mWidth = width;
}


/*
==========
Set methods intended for presets
==========
*/

void GlutApp::setPlaneSize(const double &MinX, const double &MaxX, const double &MinY, const double MaxY) {
  mMinX = MinX;
  mMinY = MinY;
  mMaxX = MaxX;
  mMaxY = MaxY;
}

void GlutApp::setColorTableSize(const unsigned int& size) {
  mNumColor = size;
}

void GlutApp::setColor1(const int &red, const int &green, const int &blue) {
  mColors[COLOR_1].setRed(red);
  mColors[COLOR_1].setGreen(green);
  mColors[COLOR_1].setBlue(blue);
}

void GlutApp::setColor2(const int& red, const int& green, const int& blue) {
  mColors[COLOR_2].setRed(red);
  mColors[COLOR_2].setGreen(green);
  mColors[COLOR_2].setBlue(blue);
}

void GlutApp::setColor(GradientColorIndex color_selection, const int& red, const int& green, const int& blue) {
  mColors[color_selection].setRed(red);
  mColors[color_selection].setGreen(green);
  mColors[color_selection].setBlue(blue);
}

void GlutApp::setAB(const double& a, const double& b) {
  mA = a;
  mB = b;
}

void GlutApp::setABFromMouseCoords(const int &x, const int &y) {
  ComplexFractal* grid_ptr = dynamic_cast<ComplexFractal*>(&mActionData.getGrid());
  mA = mMinX + (x * grid_ptr->getDeltaX());
  mB = mMinY + (y * grid_ptr->getDeltaY());
}

/*
==========
*/

int GlutApp::getHeight() const {
  return mHeight;
}
int GlutApp::getWidth() const {
  return mWidth;
}

void GlutApp::increaseMaxNumber() {
  if (mMaxNumber < 2048) {
    mMaxNumber *= 1.1;
  }
}

void GlutApp::decreaseMaxNumber() {
  if (mMaxNumber > 11) {
    mMaxNumber /= 1.1;
  }
}

void GlutApp::increaseGradientAmount() {
  if (mNumGradientColors < 9) {
    mNumGradientColors += 1;
  }
  setColorTable();
}

void GlutApp::decreaseGradientAmount() {
  if (mNumGradientColors > 2) {
    mNumGradientColors -= 1;
  }
  setColorTable();
}


/*
==========
Delta Calculations
==========
*/

inline void GlutApp::calculateDxAndDy(double& dx, double& dy) {
  dx = calculateDx();
  dy = calculateDy();
}

inline double GlutApp::calculateDx() {
  return (1.0-0.9)*(mMaxX-mMinX)/2.0;
}

inline double GlutApp::calculateDy() {
  return (1.0-0.9)*(mMaxY-mMinY)/2.0;
}

bool GlutApp::checkBound(const ViewBoundDirection direction, const double& delta) const {
  //Up and right are positive, left and down are negative

  unsigned long long deltabits;
  std::memcpy(&deltabits, &delta, sizeof(deltabits));

  if ((deltabits >> 63) & 1) {
    return false; // a negative delta means we've zoomed in too much
  }
  
  switch (direction) {
    case UP: //Check MaxY
      if ((mMaxY + delta) <= VIEW_BOUNDARY) {
        #ifdef _DEBUG_
        std::cout << "Checkbound returning true on check up with a m + delta of: " << mMaxY+delta << std::endl;
        #endif
        return true;
      }
      return false;

    case DOWN: //Check MinY
      if ((mMinY - delta) >= 0-VIEW_BOUNDARY) {
        #ifdef _DEBUG_
        std::cout << "Checkbound returning true on check down with a m - delta of: " << mMinY-delta << std::endl;
        #endif
        return true;
      }
      return false;

    case LEFT: // check mMinx
      if ((mMinX - delta) >= 0-VIEW_BOUNDARY) {
        #ifdef _DEBUG_
        std::cout << "Checkbound returning true on check left with a m + delta of: " << mMaxX+delta << std::endl;
        #endif
        return true;
      }
      return false;
    
    case RIGHT: //check mMaxx
      if ((mMaxX + delta) < VIEW_BOUNDARY) {
        #ifdef _DEBUG_
        std::cout << "Checkbound returning true on check right with a m - delta of: " << mMinX-delta << std::endl;
        #endif
        return true;
      }
      return false;

    default: //Silence, dumb compiler
      return false;
  }
}


/*
==========
Zoom Functions
==========
*/

void GlutApp::zoomAndMove(int x, int y) {
  double dX = std::abs(x-mWidth/2);
  double dY = std::abs(y-mHeight/2);

  if (dX < dY) {
    zoomIn();
    if (y < mHeight/2) {
      moveUp();
    } else {
      moveDown();
    }
    
  } else if (dX > dY) {
    zoomIn();
    if (x < mWidth/2) {
      moveLeft();
    } else {
      moveRight();
    }
  }
}

void GlutApp::zoomIn() {
  double dX, dY;
  calculateDxAndDy(dX, dY);

  mMinX += dX;
  mMaxX -= dX;
  mMinY += dY;
  mMaxY -= dY;
  #ifdef _DEBUG_

  std::cout << "Dx: " << dX << std::endl;
  std::cout << "Dy: " << dY << std::endl;
  std::cout << "Plane Coords x X y Y : " << mMinX << " " << mMaxX << " " << mMinY << " " << mMaxY << std::endl;

  #endif
}

void GlutApp::zoomOut() {
  double dX, dY;
  calculateDxAndDy(dX, dY);

  if (checkBound(UP, dY) &&
      checkBound(DOWN, dY) &&
      checkBound(LEFT, dX) &&
      checkBound(RIGHT, dX)) 
    {
    mMinX -= dX;
    mMaxX += dX;
    mMinY -= dY;
    mMaxY += dY;

    #ifdef _DEBUG_

    std::cout << "Dx: " << dX << std::endl;
    std::cout << "Dy: " << dY << std::endl;
    std::cout << "Plane Coords x X y Y : " << mMinX << " " << mMaxX << " " << mMinY << " " << mMaxY << std::endl;

    #endif
  }
}

/*
==========
Move and scale functions
==========
*/

void GlutApp::moveLeft() {
  double dX = calculateDx();
  if (checkBound(LEFT, dX)) {
    mMinX -= dX;
    mMaxX -= dX;
  }
}

void GlutApp::moveRight() {
  double dX = calculateDx();
  if (checkBound(RIGHT, dX)) {
    mMinX += dX;
    mMaxX += dX;
  }
}

void GlutApp::moveUp() {
  double dY = calculateDy();
  if (checkBound(UP, dY)) {
    mMinY += dY;
    mMaxY += dY;
  }
}

void GlutApp::moveDown() {
  double dY = calculateDy();
  if (checkBound(DOWN, dY)) {
    mMinY -= dY;
    mMaxY -= dY;
  }
}

void GlutApp::scaleUpVertical() {
  double dY = calculateDy();
  if (checkBound(UP, dY) && checkBound(DOWN, dY)) {
    mMinY -= dY;
    mMaxY += dY;
  }
}

void GlutApp::scaleDownVertical() {
  double dY = calculateDy();
  mMinY += dY;
  mMaxY -= dY;
}

void GlutApp::scaleUpHorizontal() {
  double dX = calculateDx();
  if (checkBound(LEFT, dX) && checkBound(RIGHT, dX)) {
    mMinX -= dX;
    mMaxX += dX;
  }
}

void GlutApp::scaleDownHorizontal() {
  double dX = calculateDx();
  mMinX += dX;
  mMaxX -= dX;
}

/*
==========
Display methods
==========
*/

void GlutApp::display() {
  
  if (mInteractionMode == IM_COLORTABLE ||
      mInteractionMode == IM_COLOR) {
    displayColorTable();
    return;
  }

  PPM& p = mActionData.getOutputImage();
  double max = static_cast<double>(p.getMaxColorValue());
  double r, g, b;
  int row, column;
  glBegin( GL_POINTS );
  
  for(row = 0; row < p.getHeight(); row++) {
    for(column = 0; column < p.getWidth(); column++) {
      r = p.getChannel(row, column, 0) / max;
      g = p.getChannel(row, column, 1) / max;
      b = p.getChannel(row, column, 2) / max;
      glColor3d(r, g, b);
      glVertex2i(column, p.getHeight()-row-1);
    }
  }

  glEnd( );
  if (mShowParameters) {
    displayParameters();
  }
}

void GlutApp::displayColorTable() {
  int col;
  int colorTableIndex;
  double r, g, b;
  ColorTable table = mActionData.getTable();
  double max = table.getMaxChannelValue();
  glBegin(GL_POINTS);
  for (col = 0; col < mWidth; col++) {
    for (int row = 0; row < mHeight; row++) {

      colorTableIndex = (col * table.getNumberOfColors()-1) / mWidth;
      Color color = table[colorTableIndex]; 
      r = color.getRed() / max;
      g = color.getGreen() / max;
      b = color.getBlue() / max;
      glColor3d(r, g, b);
      glVertex2i(col, row);

    }
  }
  glEnd();
  if (mShowParameters) {
    displayParameters();
  }
}

void GlutApp::displayParameters() {

  glColor3d(0, 0, 0);
  const unsigned int textXPos = 10;
  const unsigned int textGap = 30;

  const char* FractalModeStr;
  switch (mFractalMode) {
    case M_COMPLEX:
      FractalModeStr = "Complex";
      break;
    case M_JULIA:
      FractalModeStr = "Julia Set";
      break;
    case M_MANDELBROT:
      FractalModeStr = "Mandelbrot";
      break;
    default:
      FractalModeStr = "UNKNOWN FRACTAL MODE";
  }

  DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_0)), "Fractal Mode: ");
  DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_1)), FractalModeStr);

  const char* InteractionModeStr;
  switch (mInteractionMode) {
    case IM_COLORTABLE:
      InteractionModeStr = "Color Table Mode";
      break;
    case IM_FRACTAL:
      InteractionModeStr = "Fractal Mode";
      break;
    case IM_COLOR:
      {
        std::stringstream str;
        str << "Color " << mColorModeSelector+1 << " Mode";
        InteractionModeStr = str.str().c_str();
      }
      break;
    default:
      InteractionModeStr = "UNKNOWN INTERACTION MODE";
  }
  DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_2)), "Interaction Mode: ");
  DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_3)), InteractionModeStr);

  if (mInteractionMode == IM_FRACTAL) {
    {
      std::stringstream str;
      str << "mMinX: " << mMinX;
      DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_4)), str.str().c_str());
    }

    {
      std::stringstream str;
      str << "mMaxX: " << mMaxX;
      DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_5)), str.str().c_str());
    }

    {
      std::stringstream str;
      str << "mMinY: " << mMinY;
      DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_6)), str.str().c_str());
    }

    {
      std::stringstream str;
      str << "mMaxY: " << mMaxY;
      DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_7)), str.str().c_str());
    }

    {
      std::stringstream str;
      str << "Escape Count: " << mMaxNumber;
      DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_8)), str.str().c_str());
    }
    if (mFractalMode == M_JULIA) {
      {
        std::stringstream str;
        str << "Julia Set Parameter A: " << mA;
        DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_9)), str.str().c_str());
      }

      {
        std::stringstream str;
        str << "Julia Set Parameter B: " << mA;
        DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_10)), str.str().c_str());
      }
    } 
    
  } else if (mInteractionMode == IM_COLORTABLE) {
    {
      std::stringstream str;
      str << "Gradient Colors: " << mNumGradientColors;
      DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_4)), str.str().c_str());
    }

    {
      std::stringstream str;
      str << "Color Table Size: " << mNumColor;
      DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_5)), str.str().c_str());
    }
  } else if (mInteractionMode == IM_COLOR) {
    {
      std::stringstream str;
      if (mHSVColor) {
        str << "Hue: " << mColors[fetchColor()].getRed();
      } else {
        str << "Red: " << mColors[fetchColor()].getRed();
      }
      DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_4)), str.str().c_str());
    }

    {
      std::stringstream str;
      if (mHSVColor) {
        str << "Saturation: " << mColors[fetchColor()].getGreen();
      } else {
        str << "Green: " << mColors[fetchColor()].getGreen();
      }
      DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_5)), str.str().c_str());
    }

    {
      std::stringstream str;
      if (mHSVColor) {
        str << "Value: "  << mColors[fetchColor()].getBlue();
      } else {
        str << "Blue: "  << mColors[fetchColor()].getBlue();
      }
      DrawText(textXPos, (mHeight-(textGap*PARAM_DRAW_POS_6)), str.str().c_str());
    }
  }
}

/*
==========
Color Table
==========
*/
GlutApp::GradientColorIndex GlutApp::fetchColor() const {
  return mColorModeSelector;
}

void GlutApp::increaseChannel(GradientColorIndex color, const int& channel) {
  mColors[color].setChannel(channel, (mColors[color].getChannel(channel)+10));
  setColorTable();
}

void GlutApp::decreaseChannel(GradientColorIndex color, const int& channel) {
  mColors[color].setChannel(channel, (mColors[color].getChannel(channel)-10));
  setColorTable();
}

void GlutApp::increaseRed(GradientColorIndex color) {
  increaseChannel(color, 0);
}

void GlutApp::increaseGreen(GradientColorIndex color) {
  increaseChannel(color, 1);
}

void GlutApp::increaseBlue(GradientColorIndex color) {
  increaseChannel(color, 2); 
}

void GlutApp::decreaseRed(GradientColorIndex color) {
  decreaseChannel(color, 0);
}

void GlutApp::decreaseGreen(GradientColorIndex color) {
  decreaseChannel(color, 1);
}

void GlutApp::decreaseBlue(GradientColorIndex color) {
  decreaseChannel(color, 2); 
}

void GlutApp::setColorTable() {
  {
    std::stringstream tmp;
    tmp << mNumColor;
    mInputStream.str(tmp.str());
    doAction("set-color-table-size", tmp);
  }

  if (!mHSVColor) {
    double stepSize = (double) mNumColor / (mNumGradientColors - 1);
    unsigned int color = 0;

    for (double step = 0; color < mNumGradientColors-1; step += stepSize, color += 1) {
      std::stringstream tmp;
      tmp << (int) step << " " //start point
      << mColors[color].getRed() << " " 
      << mColors[color].getGreen() << " " 
      << mColors[color].getBlue() << " "
      << (int) std::ceil((step+stepSize))-1 <<  " " // end point
      << mColors[color+1].getRed() << " "
      << mColors[color+1].getGreen() << " "
      << mColors[color+1].getBlue() << " ";
      mInputStream.str(tmp.str());
      doAction("set-color-gradient", tmp);

      #ifdef _DEBUG_
      std::cout << "Inserting color " << color+1 << " at color table slot " << (int) step << std::endl;
      std::cout << "Inserting color " << color+2 << " at color table slot " << (int) std::ceil((step+stepSize))-1 << std::endl;
      #endif
    }
  } else {
    double stepSize = (double) mNumColor / (mNumGradientColors - 1);
    unsigned int color = 0;

    for (double step = 0; color < mNumGradientColors-1; step += stepSize, color += 1) {
      std::stringstream tmp;

      double h1, v1, s1; //I hope this bugs someone
      double h2, s2, v2;
      mColors[color].getHSV(h1, s1, v1);
      mColors[color+1].getHSV(h2, s2, v2);

      tmp << (int) step << " " //start point
      << h1 << " " 
      << s1 << " " 
      << v1 << " "
      << (int) std::ceil((step+stepSize))-1 <<  " " // end point
      << h2 << " "
      << s2 << " "
      << v2 << " ";
      mInputStream.str(tmp.str());
      doAction("set-hsv-gradient", tmp);

      #ifdef _DEBUG_
      std::cout << "Inserting color " << color+1 << " at color table slot " << (int) step << std::endl;
      std::cout << "Inserting color " << color+2 << " at color table slot " << (int) std::ceil((step+stepSize))-1 << std::endl;
      #endif
    }
  }
}

void GlutApp::decreaseColorTableSize() {
  if (mNumColor > 10) {
    mNumColor /= 1.1;
    setColorTable();
    recalculateGrid(true);
  }
}

void GlutApp::increaseColorTableSize() {
  if (mNumColor < 1024) {
    mNumColor *= 1.1;
    setColorTable();
    recalculateGrid(true);
  }
}

void GlutApp::randomColor1() {
  randomColor(COLOR_1);
}

void GlutApp::randomColor2() {
  randomColor(COLOR_2);
}

void GlutApp::randomColor(GradientColorIndex index) {
  for (int i=0; i<3; i++) {
    mColors[index].setChannel(i, rand() % 255);
  }
  setColorTable();
}

/*
==========
Program modes
==========
*/

void GlutApp::setInteractionMode(InteractionMode mode) {
  mInteractionMode = mode;
}

void GlutApp::setInteractionMode(InteractionMode mode, GradientColorIndex color) {
  mInteractionMode = mode;
  if (mode == IM_COLOR) {
    mColorModeSelector = color;
  }
}

void GlutApp::setFractalMode(FractalMode mode) {
  mFractalMode = mode;
  createFractal();
}

/*
==========
Reset Methods
==========
*/

void GlutApp::resetPlane() {
  mMinX = mMinY = -2.0;
  mMaxX = mMaxY = 2.0;

  {
    std::stringstream tmp;
    tmp << mMinX << " " << mMaxX << " "<< mMinY << " " << mMaxY;
    mInputStream.str(tmp.str());
    doAction("fractal-plane-size", tmp);
  }
}

void GlutApp::resetAB() {
  mA = 1.99;
  mB = -1.2;
}

void GlutApp::resetColorTable() {
  mColors[COLOR_1] = Color(243, 15, 35),
  mColors[COLOR_2] = Color(45, 45, 45),
  mNumColor = 32;
}

void GlutApp::resetAll() {
  resetPlane();
  resetAB();
  resetColorTable();
}

/*
==========
Fractal methods
==========
*/

void GlutApp::createFractal() {
  switch (mFractalMode) {
    case M_COMPLEX:
      createComplexFractal();
      break;

    case M_JULIA:
      createJulia();
      break;

    case M_MANDELBROT:
      createMandelbrot();
      break;
  }
  setColorTable();
  recalculateGrid(true);
}

void GlutApp::createJulia() {
  createJulia(mA, mB);
}

void GlutApp::createJulia(const double& paramA, const double& paramB) {

  // julia
  doAction("julia");

  // julia-parameters
  {
    std::stringstream tmp;
    tmp << paramA << " " << paramB;
    mInputStream.str(tmp.str());
    doAction("julia-parameters", tmp);
  }
}

void GlutApp::createMandelbrot() {

  // mandelbrot
  doAction("mandelbrot");

}

void GlutApp::createComplexFractal() {

  // complex fractal
  doAction("complex-fractal");

}


/*
==========
RecalculateGrid!
==========
*/

void GlutApp::recalculateGrid(bool force_recalc) {

  static int oldHeight;
  static int oldWidth;
  static int oldMaxNumber;
  static double oldMinX;
  static double oldMinY;
  static double oldMaxX;
  static double oldMaxY;
  static double oldA;
  static double oldB;

  bool changed = false;
  
  //Must we update the grid height/width/maxNumber?
  if (
    oldHeight != mHeight ||
    oldWidth != mWidth ||
    oldMaxNumber != mMaxNumber ||
    force_recalc
  ) {
    std::stringstream tmp;
    tmp << mHeight << " " << mWidth << " " << mMaxNumber;
    mInputStream.str(tmp.str());
    doAction("grid", tmp);
    changed = true;
  }

  //Must we update a and b?
  if (
    oldA != mA ||
    oldB != mB ||
    force_recalc
  ) {
    changed = true;
    {
    std::stringstream tmp;
    tmp << mA << " " << mB;
    mInputStream.str(tmp.str());
    doAction("julia-parameters", tmp);
    }
  }

  //Must we update the plane?
  if (
    oldMinX != mMinX ||
    oldMinY != mMinY ||
    oldMaxX != mMaxX ||
    oldMaxY != mMaxY ||
    force_recalc
  ) {
    std::stringstream tmp;
    tmp << mMinX << " " << mMaxX << " " << mMinY << " " << mMaxY;
    mInputStream.str(tmp.str());
    doAction("fractal-plane-size", tmp);
    changed = true;
  }

  if (force_recalc || changed) {
    // fractal-calculate
    doAction("fractal-calculate");

    // grid-apply-color-table
    doAction("grid-apply-color-table");
  }


  oldHeight = mHeight;
  oldWidth = mWidth;
  oldMaxNumber = mMaxNumber;
  oldMinX = mMinX;
  oldMinY = mMinY;
  oldMaxX = mMaxX;
  oldMaxY = mMaxY;
  oldA = mA;
  oldB = mB;
}

void GlutApp::writeImage() {

{
  std::stringstream tmp;
  tmp << "image-" << mImageNumber << ".ppm";
  doAction("write", tmp);
}
mImageNumber++;
}

/*
==========
Action Methods (Helpers)
==========
*/

void GlutApp::doAction(std::string action, std::stringstream &ss) {
  clearStreams();
  mInputStream.str(ss.str());
  takeAction(action, mMenuData, mActionData);
}

void GlutApp::doAction(std::string action) {
  clearStreams();
  takeAction(action, mMenuData, mActionData);
}

void GlutApp::clearStreams() {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
}
