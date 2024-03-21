run: compile
	./build/OpenGLLearn

compile: cmake
	cd build && $(MAKE)

cmake:
	cd build && cmake ..

all: run

.PHONY: run compile cmake