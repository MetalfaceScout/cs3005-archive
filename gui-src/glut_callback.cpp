#include "GlutApp.h"
#include "glut_app.h"
#include <GL/freeglut_std.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display_cb(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  g_app_data->display();
  glutSwapBuffers();
}

// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard_cb(unsigned char c, int x, int y) {
  (void)x;
  (void)y;
  // just for demonstration purposes
  std::cout << "key: " << (int)c << std::endl;
  switch (c) {

  case 'b': //Set mandelbrot
    g_app_data->setFractalMode(GlutApp::M_MANDELBROT);
    break;

  case 'c': //Complex fractal preset 1
    g_app_data->resetAll();
    g_app_data->setPlaneSize(-0.3, -0.1, -0.3, 0.3);
    g_app_data->setFractalMode(GlutApp::M_COMPLEX);
    break;

  case 'C': //Complex fractal preset 2
    g_app_data->setColor1(15, 15, 15);
    g_app_data->setColor2(245, 245, 255);
    g_app_data->setColorTableSize(512);
    g_app_data->setPlaneSize(-0.5, 0.4, -0.4, 0.5);
    g_app_data->setFractalMode(GlutApp::M_COMPLEX);
    break;

  case 'F': //Set complex fractal //Hopefully fixed for assignment?
    g_app_data->setFractalMode(GlutApp::M_COMPLEX);
    break;

  case 'h':
    g_app_data->toggleHSVColor();
    break;

  case 'm': //Mandelbrot preset 1
    g_app_data->resetAll();
    g_app_data->setPlaneSize(-1.3, 1.3, 1.5, -1.5);
    g_app_data->setFractalMode(GlutApp::M_MANDELBROT);
    break;

  case 'M': //Mandelbrot preset 2
    g_app_data->setColor1(50, 50, 245);
    g_app_data->setColor2(245, 15, 255);
    g_app_data->setPlaneSize(-0.65, 0.5, 1.0, 2.0);
    g_app_data->setFractalMode(GlutApp::M_MANDELBROT);
    break;


  case 'J': //Julia preset 2
    g_app_data->resetAll();
    g_app_data->setColor1(15, 255, 45);
    g_app_data->setColor2(0, 20, 2);
    g_app_data->setColorTableSize(256);
    g_app_data->setPlaneSize(-0.45, 0.45, 1.5, 2.0);
    g_app_data->setFractalMode(GlutApp::M_JULIA);
    break;

  case 'j': //Julia preset 1
    g_app_data->resetAll();
    g_app_data->setAB(1.33, 0.32);
    g_app_data->setFractalMode(GlutApp::M_JULIA);
    break;
  
  case 'n': //Set julia
    g_app_data->setFractalMode(GlutApp::M_JULIA);
    break;

  case 'p': //display info
    g_app_data->showParametersToggle();
    break;

  case 'q':
  case 27: // escape character means to quit the program
    exit(0);
    break;

  case 'r': //Random color 1
    if (g_app_data->getInteractionMode() == GlutApp::IM_COLORTABLE) {
      g_app_data->randomColor1();
    }
    break;
  case 'R': //Random Color 2 && reset plane if in fractal mode
    if (g_app_data->getInteractionMode() == GlutApp::IM_COLORTABLE) {
      g_app_data->randomColor2();
    } else if (g_app_data->getInteractionMode() == GlutApp::IM_FRACTAL) {
      g_app_data->resetPlane();
    }
    break;

  case 'T': // Switch display mode to color table
    g_app_data->setInteractionMode(GlutApp::IM_COLORTABLE);
    break;
  case 't': // Display mode fractal
    g_app_data->setInteractionMode(GlutApp::IM_FRACTAL);
    g_app_data->recalculateGrid(true);
    break;

  case 'Y':
    g_app_data->increaseRed(g_app_data->fetchColor());
    break;

  case 'y':
    g_app_data->decreaseRed(g_app_data->fetchColor());
    break;

  case 'U':
    g_app_data->increaseGreen(g_app_data->fetchColor());
    break;

  case 'u':
    g_app_data->decreaseGreen(g_app_data->fetchColor());
    break;

  case 'I':
    g_app_data->increaseBlue(g_app_data->fetchColor());
    break;

  case 'i':
    g_app_data->decreaseBlue(g_app_data->fetchColor());
    break;

  case 'w':
    g_app_data->writeImage();
    break;

  case 'z':
    g_app_data->zoomIn();
    break;
  case 'Z':
    g_app_data->zoomOut();
    break;

  case 49: //number 1
    g_app_data->setInteractionMode(GlutApp::IM_COLOR, GlutApp::COLOR_1);
    break;
  
  case '!':
    g_app_data->randomColor(GlutApp::COLOR_1);
    break;

  case '@':
    g_app_data->randomColor(GlutApp::COLOR_2);
    break;

  case '#':
    g_app_data->randomColor(GlutApp::COLOR_3);
    break;

  case '$':
    g_app_data->randomColor(GlutApp::COLOR_4);
    break;

  case '%':
    g_app_data->randomColor(GlutApp::COLOR_5);
    break;

  case 50: //number 2, down on numpad
    if (g_app_data->getInteractionMode() == GlutApp::IM_FRACTAL) {
      g_app_data->scaleDownVertical();
    } else if (g_app_data->getInteractionMode() != GlutApp::IM_FRACTAL) {
      g_app_data->setInteractionMode(GlutApp::IM_COLOR, GlutApp::COLOR_2);
    }
    break;
  case 51: //number 3
    g_app_data->setInteractionMode(GlutApp::IM_COLOR, GlutApp::COLOR_3);
    break;
  case 52: //number 4, left on numpad
    if (g_app_data->getInteractionMode() == GlutApp::IM_FRACTAL) {
      g_app_data->scaleDownHorizontal();
    } else if (g_app_data->getInteractionMode() != GlutApp::IM_FRACTAL) {
      g_app_data->setInteractionMode(GlutApp::IM_COLOR, GlutApp::COLOR_4);
    }
    break;
  case 53: //number 5
    g_app_data->setInteractionMode(GlutApp::IM_COLOR, GlutApp::COLOR_5);
    break;
  case 54: //number 4, left on numpad
    g_app_data->scaleDownHorizontal();
    break;

  case 56: //number 8, up on numpad
    g_app_data->scaleUpVertical();
    break;

  case '-':
  case '_':
    if (g_app_data->getInteractionMode() == GlutApp::IM_COLORTABLE ||
        g_app_data->getInteractionMode() == GlutApp::IM_COLOR) {
      g_app_data->decreaseGradientAmount();
    } else if (g_app_data->getInteractionMode() == GlutApp::IM_FRACTAL) {
      g_app_data->decreaseMaxNumber();
    }
    break;

  case '+':
  case '=':
    if (g_app_data->getInteractionMode() == GlutApp::IM_COLORTABLE ||
        g_app_data->getInteractionMode() == GlutApp::IM_COLOR) {
      g_app_data->increaseGradientAmount();
    } else if (g_app_data->getInteractionMode() == GlutApp::IM_FRACTAL) {
      g_app_data->increaseMaxNumber();
    }
    break;

  case '<':
  case ',': 
    g_app_data->decreaseColorTableSize();
    break;
  
  case '>':
  case '.':
    g_app_data->increaseColorTableSize();
    break;

  default:
    return; // if we don't care, return without glutPostRedisplay()
  }
  
  g_app_data->recalculateGrid(false);
  glutPostRedisplay(); // tell glut to call display() as soon as possible.
}

void special_cb(int c, int x, int y) {
  (void)x;
  (void)y;
  // just for demonstration purposes
  std::cout << "special key: " << (int)c << std::endl;
  switch(c) {
  case GLUT_KEY_UP:
    g_app_data->moveUp();
    break;
  case GLUT_KEY_DOWN:
    g_app_data->moveDown();
    break;
  case GLUT_KEY_LEFT:
    g_app_data->moveLeft();
    break;
  case GLUT_KEY_RIGHT:
    g_app_data->moveRight();
    break;
  default:
    return; // if we don't care, return without glutPostRedisplay()
  }

  g_app_data->recalculateGrid(false);
  glutPostRedisplay(); // tell glut to call display() as soon as possible.
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape_cb(int w, int h) {
  // Reset our global variables to the new width and height.
  g_app_data->setSize(h, w);
  g_app_data->recalculateGrid(true);
  display_cb();

  // all of the gl*() function calls below are part of the openGL
  // library, not our code.

  // Set the pixel resolution of the final picture (Screen coordinates).
  glViewport(0, 0, w, h);

  // Set the projection mode to 2D orthographic, and set the world coordinates:
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse_cb(int mouse_button, int state, int x, int y) {
  // translate pixel coordinates to display coordinates
  int xdisplay = x;
  int ydisplay = g_app_data->getHeight() - y;
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    std::cout << "Left Mouse Down. @" << xdisplay << "," << ydisplay << std::endl;
  }
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    std::cout << "Left Mouse Up. @" << xdisplay << "," << ydisplay << std::endl;
    if (g_app_data->getInteractionMode() == GlutApp::IM_FRACTAL && g_app_data->getFractalMode() == GlutApp::M_MANDELBROT) {
      g_app_data->setABFromMouseCoords(x, y);
    }
  }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
    std::cout << "Middle Mouse Down. @" << xdisplay << "," << ydisplay << std::endl;
  }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
    std::cout << "Middle Mouse Up. @" << xdisplay << "," << ydisplay << std::endl;
    if (g_app_data->getInteractionMode() == GlutApp::IM_FRACTAL) {
      g_app_data->zoomAndMove(x, y);
    }
  }

  if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    std::cout << "Right Mouse Down. @" << xdisplay << "," << ydisplay << std::endl;
  }

  if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    std::cout << "Right Mouse Up. @" << xdisplay << "," << ydisplay << std::endl;
    if (g_app_data->getInteractionMode() == GlutApp::IM_FRACTAL) {
      g_app_data->zoomOut();
    }
  }
  glutPostRedisplay();
}

