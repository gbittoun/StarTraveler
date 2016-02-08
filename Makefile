PROJECT=ShaderExamples
TEST_PROJECT=ShaderExamples_test
SOURCES=Camera.cpp  ErrorStateBase.cpp  GLHandler.cpp  main.cpp  Quaternion.cpp  SDLApplication.cpp  ShaderLoader.cpp  StarField.cpp
TEST_SOURCES=tests/Camera.cpp tests/Quaternion.cpp
LDFLAGS=-lSDL -lGL -lGLEW -lGLU -lm -lstdc++
DEBUG_CFLAGS=-g -std=c++11 -c -Wall -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL
CC=g++

# Automatic generation of some important lists
OBJECTS=$(SOURCES:.cpp=.o)
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

all: CCFLAGS=$(DEBUG_CFLAGS)
all: clean_main $(PROJECT)

release: CCFLAGS=$(filter-out -g, $(DEBUG_CFLAGS))
release: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

$(TEST_PROJECT): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ $<

check: CCFLAGS=-DUNITTEST $(DEBUG_CFLAGS)
check: LDFLAGS:=$(LDFLAGS) -lCppUTest -lCppUTestExt
check: SOURCES:=$(SOURCES) $(TEST_SOURCES)
check: clean_main $(TEST_PROJECT)

clean:
	rm -f $(TEST_OBJECTS)
	rm -f $(OBJECTS)
	rm -f $(TEST_PROJECT)
	rm -f $(PROJECT)

clean_main:
	rm -f main.o
