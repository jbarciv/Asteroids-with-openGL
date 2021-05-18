 
LDFLAGS= -L/usr/local/lib    -lm   -framework GLUT -framework OpenGL -framework Cocoa 

LinuxLFLAGS= -lGL -lGLU -lglut -lm


#
# How to make .c into .o
#
.cpp.o: commonstuff.h
	g++   -c $< -w



# STL:	Shape.o  Asteroid.o Bullet.o mainAsteroidsSTL.o commonstuff.h Ship.o ObjectsListSTL.o
# 	g++ Shape.o  Bullet.o Ship.o Asteroid.o mainAsteroidsSTL.o ObjectsListSTL.o $(LDFLAGS)  -o AsteroidsGL -w


noSTL:	Shape.o  Asteroid.o Bullet.o Flame.o mainAsteroids.o commonstuff.h Ship.o ObjectsList.o 
	g++ Shape.o  Bullet.o Ship.o Asteroid.o Flame.o mainAsteroids.o ObjectsList.o  $(LDFLAGS)  -o AsteroidsGLnoSTL -w


Linux:	Shape.o  Asteroid.o Bullet.o mainAsteroids.o commonstuff.h Ship.o ObjectsList.o
	g++ Shape.o  Bullet.o Ship.o Asteroid.o mainAsteroids.o ObjectsList.o $(LinuxLFLAGS)  -o AsteroidsGL -w

clean:
	rm -f *~
	rm -f *.o
