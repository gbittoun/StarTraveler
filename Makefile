PROJECT=ShaderExamples
SOURCES=Camera.cpp  ErrorStateBase.cpp  GLHandler.cpp  main.cpp  Quaternion.cpp  SDLApplication.cpp  ShaderLoader.cpp  StarField.cpp
LDFLAGS=-lSDL -lGL -lGLEW -lGLU
CFLAGS=-std=c++11 -c -Wall -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL
CC=g++

# Automatic generation of some important lists
OBJECTS=$(SOURCES:.cpp=.o)

all: $(PROJECT)

debug: CFLAGS += -g
debug: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJECTS)
	rm $(PROJECT)
