MAKEFILE      = Makefile
CC            = gcc
CXX           = g++
CFLAGS          = $(SUBLIBS) `pkg-config --libs --cflags opencv`
SOURCES       = main.cpp
TARGET        = Face-Feature-Detection

all:
	$(CXX) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
