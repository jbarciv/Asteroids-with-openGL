
LDFLAGS= -L/usr/local/lib    -lm   -framework GLUT -framework OpenGL -framework Cocoa 

LinuxLFLAGS= -lGL -lGLU -lglut -lm -Wall -g

.cpp.o: commonstuff.hpp
	g++   -c $< -w


Linux:	Shape.o  Asteroid.o Bullet.o Flame.o mainAsteroids.o commonstuff.hpp Ship.o ObjectsList.o
	g++ Shape.o  Bullet.o Ship.o Asteroid.o Flame.o mainAsteroids.o ObjectsList.o $(LinuxLFLAGS)  -o mainAsteroids -w

STL:	Shape.o  Asteroid.o Bullet.o mainAsteroidsSTL.o commonstuff.hpp Ship.o ObjectsListSTL.o
	g++ Shape.o  Bullet.o Ship.o Asteroid.o mainAsteroidsSTL.o ObjectsListSTL.o $(LDFLAGS)  -o AsteroidsGL -w


noSTL:	Shape.o  Asteroid.o Bullet.o Flame.o mainAsteroids.o commonstuff.hpp Ship.o ObjectsList.o 
	g++ Shape.o  Bullet.o Ship.o Asteroid.o Flame.o mainAsteroids.o ObjectsList.o  $(LDFLAGS)  -o AsteroidsGLnoSTL -w

clean:
	rm -f *~
	rm -f *.o
	rm mainAsteroids
