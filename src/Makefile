
CXXFLAGS := -std=c++11
CXXFLAGS := $(CXXFLAGS) -Wall -Wpedantic -Wextra -Werror
CXXFLAGS := $(CXXFLAGS) -g
LINKFLAGS := $(LINKFLAGS) -lpthread

LINKFILES := ThreadedGrid.o MandelbrotSet.o JuliaSet.o ComplexFractal.o ColorTable.o controllers.o user_io.o image_output.o image_drawing.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o

all: hello questions_3 guessing ascii_image image_file flag_romania ppm_menu

ThreadedGrid.o: NumberGrid.cpp NumberGrid.h ThreadedGrid.cpp ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c ThreadedGrid.cpp

MandelbrotSet.o: ComplexFractal.cpp ComplexFractal.h NumberGrid.cpp NumberGrid.h MandelbrotSet.h MandelbrotSet.cpp
	$(CXX) $(CXXFLAGS) -c MandelbrotSet.cpp

ComplexFractal.o: ComplexFractal.cpp ComplexFractal.h NumberGrid.cpp NumberGrid.h NumberGrid.o
	$(CXX) $(CXXFLAGS) -c ComplexFractal.cpp

JuilaSet.o: ComplexFractal.cpp ComplexFractal.h NumberGrid.cpp NumberGrid.h JuilaSet.h JuilaSet.cpp
	$(CXX) $(CXXFLAGS) -c JuliaSet.cpp

ColorTable.o: ColorTable.cpp ColorTable.h
	$(CXX) $(CXXFLAGS) -c ColorTable.cpp

NumberGrid.o: NumberGrid.cpp NumberGrid.h ColorTable.h PPM.h
	$(CXX) $(CXXFLAGS) -c NumberGrid.cpp

image_filters.o: image_filters.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c image_filters.cpp

ppm_menu: $(LINKFILES) ppm_menu.o
	$(CXX) $(CXXFLAGS) -o ppm_menu ppm_menu.o $(LINKFILES) $(LINKFLAGS)

ppm_menu.o: ppm_menu.cpp ActionData.h image_menu.h
	$(CXX) $(CXXFLAGS) -c ppm_menu.cpp

MenuData.o: MenuData.cpp MenuData.h
	$(CXX) $(CXXFLAGS) -c MenuData.cpp

ActionData.o: ActionData.cpp ActionData.h
	$(CXX) $(CXXFLAGS) -c ActionData.cpp

flag_romania.o: flag_romania.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c flag_romania.cpp

flag_romania: flag_romania.o $(LINKFILES)
	$(CXX) $(CXXFLAGS) -o flag_romania flag_romania.o $(LINKFILES) $(LINKFLAGS)

image_file: $(LINKFILES) image_file.o
	$(CXX) $(CXXFLAGS) -o image_file image_file.o $(LINKFILES) $(LINKFLAGS)

image_file.o: PPM.o controllers.o image_menu.h image_file.cpp
	$(CXX) $(CXXFLAGS) -c image_file.cpp

PPM.o: PPM.cpp Image.cpp Image.h Image.o PPM.h
	$(CXX) $(CXXFLAGS) -c PPM.cpp

ascii_image: $(LINKFILES) ascii_image.o
	$(CXX) $(CXXFLAGS) -o ascii_image ascii_image.o $(LINKFILES) $(LINKFLAGS)

ascii_image.o: ascii_image.cpp image_menu.h Image.o controllers.o user_io.o image_output.o
	$(CXX) $(CXXFLAGS) -c ascii_image.cpp

image_drawing.o: image_drawing.cpp image_menu.h Image.h Image.o user_io.o
	$(CXX) $(CXXFLAGS) -c image_drawing.cpp

Image.o: Image.cpp Image.h
	$(CXX) $(CXXFLAGS) -c Image.cpp

image_output.o: image_output.cpp image_menu.h Image.h Image.o
	$(CXX) $(CXXFLAGS) -c image_output.cpp

guessing: guessing.o $(LINKFILES)
	$(CXX) $(CXXFLAGS) -o guessing guessing.o $(LINKFILES)

guessing.o: guessing.cpp
	$(CXX) -std=c++11  -c guessing.cpp

questions_3: questions_3.o $(LINKFILES)
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) -o questions_3 questions_3.o $(LINKFILES)

questions_3.o: questions_3.cpp image_menu.h controllers.cpp user_io.cpp user_io.o controllers.o
	$(CXX) $(CXXFLAGS) -c questions_3.cpp

controllers.o: controllers.cpp image_menu.h user_io.o Image.o Image.h PPM.h ActionData.h ActionData.o MenuData.h MenuData.o
	$(CXX) $(CXXFLAGS) -c controllers.cpp

user_io.o: image_menu.h user_io.cpp
	$(CXX) $(CXXFLAGS) -c user_io.cpp

hello: hello.o
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) -o hello hello.o

hello.o: hello.cpp
	$(CXX) $(CXXFLAGS) -c hello.cpp

clean:
	rm -r *.o
	rm ascii_image
	rm guessing
	rm flag_romania
	rm ppm_menu
	rm hello
	rm image_file
	rm *.ppm
