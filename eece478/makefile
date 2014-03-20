src_assign1 := $(wildcard src/*.cpp)
src_dir:=./src
out := ./build
lib:= -lGL -lGLU -lGLEW -lglut

$(shell   mkdir -p $(out))

modelviewer:
	g++ -std=c++0x test/assign1.cpp $(src_assign1) -I$(src_dir) $(lib) -o $(out)/modelviewer
