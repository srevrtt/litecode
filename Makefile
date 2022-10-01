# linux makefile
CC = g++
ARGS = -std=c++17 -g -Wall -O3
SRCS = src/*.cpp src/platform/linux/*.cpp src/gui_components/window.cpp dependencies/glad/glad.c
LINKER_FLAGS = `pkg-config --libs gtk+-3.0`
COMPILE_FLAGS = `pkg-config --cflags gtk+-3.0`
INCLUDE_DIR = -Idependencies -Idependencies/glm
LIBS = -ldl -lGL -lX11

build:
	$(CC) $(COMPILE_FLAGS) $(SRCS) $(INCLUDE_DIR) -o bin/litecode $(LINKER_FLAGS) $(LIBS)

run:
	./bin/litecode
