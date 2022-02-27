CC = g++

GLLIBS = -lglut -lGLEW -lGL

all: UniverseMain.cpp
	$(CC) UniverseMain.cpp ../lib/utils.cpp ../lib/dataInitializer.cpp -o UniverseMain $(GLLIBS)

clean:
	rm -f UniverseMain
