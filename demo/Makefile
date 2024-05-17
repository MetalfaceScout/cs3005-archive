CXX := g++
CXXFLAGS := -Wall -std=c++11 -Wpedantic -Wextra -Werror -g
LDFLAGS :=
OPENGL_LDFLAGS := -lglut -lGLU -lGL

UNAME := $(shell uname)

# OS X specific options
ifeq ($(UNAME), Darwin)
OPENGL_LDFLAGS := -framework OpenGL -framework GLUT
CXXFLAGS := $(CXXFLAGS) -Wno-deprecated
endif

TARGETS := hello glut_main

all: $(TARGETS)

hello: hello.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

hello.o: hello.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

glut_main: glut_main.o gl_draw.o glut_app.o GlutApp.o glut_callback.o Rectangle.o Shape.o ShapeList.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(OPENGL_LDFLAGS)

glut_main.o: glut_main.cpp glut_app.h GlutApp.h ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

gl_draw.o: gl_draw.cpp glut_app.h GlutApp.h ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

glut_app.o: glut_app.cpp glut_app.h GlutApp.h ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

GlutApp.o: GlutApp.cpp GlutApp.h Rectangle.h glut_app.h ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

glut_callback.o: glut_callback.cpp glut_app.h GlutApp.h ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Rectangle.o: Rectangle.cpp Rectangle.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Shape.o: Shape.cpp Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

ShapeList.o: ShapeList.cpp ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	-rm -f *.o *~
	-rm -f $(TARGETS)

