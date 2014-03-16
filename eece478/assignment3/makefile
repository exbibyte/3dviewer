# files from assignment 1
dir_assign1 = ../assignment1/src
src_assign1 := $(wildcard $(dir_assign1)/*.cpp)
src_assign1 := $(filter-out $(dir_assign1)/main.cpp, $(src_assign1))

dir_assign3 = ./src
src_assign3 := $(wildcard $(dir_assign3)/*.cpp)

out = ./build
$(shell   mkdir -p $(out))		

lib:= -lGL -lGLU -lGLEW -lglut

#test for city file parsing
CityParse: 
	g++ -std=c++0x test/CityParseTest.cpp $(src_assign3) $(src_assign1) -I$(dir_assign3) -I$(dir_assign1) $(lib) -o $(out)/CityParseTest

#test for multiple model loading
MultipleModel:
	g++ -std=c++0x test/MultipleModelTest.cpp $(src_assign3) $(src_assign1) -I$(dir_assign3) -I$(dir_assign1) $(lib) -o $(out)/MultipleModelTest
