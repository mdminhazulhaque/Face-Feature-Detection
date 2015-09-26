MAKEFILE      = Makefile
CXX           = g++
LINK_OPENCV   = `pkg-config --libs --cflags opencv`
SOURCES       = Face-Feature-Detection
OBJECTS       = main.o
TARGET        = Face-Feature-Detection

all:
	$(CXX) -c -m64 -pipe -O2 -Wall -W -fPIE -o $(OBJECTS) $(SOURCES)
	$(CXX) -m64 -Wl,-O1 -o $(TARGET) $(OBJECTS) $(LINK_OPENCV)

clean:
	rm -f $(TARGET)
