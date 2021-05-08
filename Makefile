CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic -Wc++11-extensions
BIN=prog

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^
	./prog > out.ppm
	open out.ppm

pathtracer: pathtracer.cpp
