src_files := $(wildcard ./src/*.cpp)
src_files_obj2custom := $(wildcard ./obj2custom/*.cpp)
inc_dir:=./src
out := ./build
lib:= -lGL -lGLU -lGLEW -lglut 

$(shell   mkdir -p $(out))

#modelviewer project for assignment 1
modelviewer:
	g++ -std=c++0x test/assign1.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/ModelViewer

obj2cutom:
	g++ -std=c++0x $(src_files_obj2custom) -o $(out)/obj2custom	

#test for city file parsing
cityparse: 
	g++ -std=c++0x test/CityParseTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/CityParseTest

#test for multiple model loading
multiplemodel:
	g++ -std=c++0x test/MultipleModelTest.cpp $(src_files) -I$(inc_dir) $(lib) -o $(out)/MultipleModelTest
