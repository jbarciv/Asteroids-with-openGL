
# For Linux
LinuxLFLAGS= -lGL -lGLU -lglut -lm
# For Mac
LDFLAGS= -L/usr/local/lib    -lm   -framework GLUT -framework OpenGL -framework Cocoa 

linux:	Cube.o
	g++ Cube.o   $(LinuxLFLAGS)  -o Cube -w

osX:	Cube.o
	g++ Cube.o   $(LDFLAGS)  -o Cube -w

clean:
	rm -f Cube
	rm -f *.o
