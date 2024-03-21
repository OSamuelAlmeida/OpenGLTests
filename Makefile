run: ./build/OpenGLLearn
	./build/OpenGLLearn

compile: ./build/Makefile
	cd build && make

cmake:
	cd build && cmake ..