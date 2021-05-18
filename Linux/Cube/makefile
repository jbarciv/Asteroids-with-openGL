
LinuxLFLAGS= -lGL -lGLU -lglut -lm

#
# How to make .c into .o
#
.cpp.o: commonstuff.h
	g++   -c $< -w

linux:	Cube.o
	g++ Cube.o   $(LinuxLFLAGS)  -o Cube -w


clean:
	rm -f Cube
	rm -f *.o
