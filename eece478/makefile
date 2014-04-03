src_files := $(wildcard ./src/*.cpp)
src_files_obj2custom := $(wildcard ./obj2custom/*.cpp)
inc_dir:=./src
out := ./build
lib:= -lGL -lGLU -lGLEW -lglut 

$(shell   mkdir -p $(out))

#modelviewer project for assignment 1
modelviewer:
	g++ -std=c++0x test/assign1.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/ModelViewer

#assignment 2 utility
obj2cutom:
	g++ -std=c++0x $(src_files_obj2custom) -o $(out)/obj2custom	

#test for city file parsing
cityparse: 
	g++ -std=c++0x test/CityParseTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/CityParseTest

#test for multiple model loading
multiplemodel:
	g++ -std=c++0x test/MultipleModelTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/MultipleModelTest

#test for parametric curve
parametriccurve:
	g++ -g -std=c++0x test/CurveTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/ParametricCurveTest

#test for camera motion with parametric curve
camerapath:
	g++ -g -std=c++0x test/CameraPathTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/CameraPathTest

#test for curve parsing
curveparse:
	g++ -g -std=c++0x test/CurveParse.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/CurveParseTest

#test for curve drawing
curvedraw:
	g++ -g -std=c++0x test/CurveTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/CurveDraw

#test for DOM parse
domparse:
	g++ -g -std=c++0x test/DOMParseTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/DOMParseTest

#test for curve parse using DOM and curve drawing
curveparsedraw:
	g++ -g -std=c++0x test/CurveParseDraw.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/CurveParseDrawTest

#test for animation parsing
animationparsetest:
	g++ -g -std=c++0x test/AnimationParseTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/AnimationParseTest

#test for animation manager
animationmanager:
	g++ -g -std=c++0x test/AnimationManagerTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/AnimationManagerTest

#test for animation manager with drawing
animationmanagerdraw:
	g++ -g -std=c++0x test/AnimationManagerDraw.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/AnimationManagerDrawTest

#test for image capture
recordertest:
	g++ -g -std=c++0x test/RecorderTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/RecorderTest

#test for image capture
matrixmathtest:
	g++ -g -std=c++0x test/MatrixMathTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/MatrixMathTest
