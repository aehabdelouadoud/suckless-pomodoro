# Makefile for C++ project with SFML and CMake

# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++17
# SFML libraries
LIBRARIES := -lsfml-audio

cdoro: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp $(LIBRARIES) -o cdoro

clean:
	rm *.o

install: cdoro
	sudo cp -r cdoro /usr/local/bin/
	sudo chmod +x /usr/local/bin/cdoro
	mkdir $(HOME)/.cdoro
	mv ./bell.mp3 $(HOME)/.cdoro/
