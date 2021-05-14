 
#LDFLAGS= -L/usr/local/lib    -lm   -framework GLUT -framework OpenGL -framework Cocoa 

LinuxLFLAGS= -lGL -lGLU -lglut -lm

#
# How to make .c into .o
#
.cpp.o: commonstuff.h
	g++   -c $< -w


#osX:	ejemplo_GL.o
#	g++ ejemplo_GL.o   $(LDFLAGS)  -o ejemploGL -w


linux:	ejemploGL.o
	g++ ejemploGL.o   $(LinuxLFLAGS)  -o ejemploGL -w


clean:
	rm -f *~
	rm -f *.o
