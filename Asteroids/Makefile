
LDFLAGS= -L/usr/local/lib    -lm   -framework GLUT -framework OpenGL -framework Cocoa 

LinuxLFLAGS= -lGL -lGLU -lglut -lm -Wall -g

.cpp.o: commonstuff.hpp
	g++   -c $< -w


Linux:	Shape.o  Asteroid.o Bullet.o Flame.o  Angel.o commonstuff.hpp Ship.o ObjectsList.o mainAsteroids.o Alien.o
	g++ Shape.o  Bullet.o Ship.o Asteroid.o Flame.o Angel.o ObjectsList.o mainAsteroids.o Alien.o $(LinuxLFLAGS)  -o mainAsteroids -w

STL:	Shape.o  Asteroid.o Bullet.o mainAsteroidsSTL.o commonstuff.hpp Ship.o ObjectsListSTL.o
	g++ Shape.o  Bullet.o Ship.o Asteroid.o mainAsteroidsSTL.o ObjectsListSTL.o $(LDFLAGS)  -o AsteroidsGL -w


noSTL:	Shape.o  Asteroid.o Bullet.o Flame.o mainAsteroids.o commonstuff.hpp Ship.o ObjectsList.o 
	g++ Shape.o  Bullet.o Ship.o Asteroid.o Flame.o mainAsteroids.o ObjectsList.o  $(LDFLAGS)  -o AsteroidsGLnoSTL -w

Asteroids: Shape.o  Asteroid.o Bullet.o Flame.o  Angel.o commonstuff.hpp Ship.o ObjectsList.o mainAsteroids.o Alien.o
	g++ -o Asteroids Shape.o  Asteroid.o Bullet.o Flame.o  Angel.o commonstuff.hpp Ship.o ObjectsList.o mainAsteroids.o Alien.o

Objects: Shape.cpp Shape.hpp Asteroid.cpp Asteroid.hpp Bullet.cpp Bullet.hpp Flame.hpp Flame.cpp Angel.hpp Angel.cpp Alien.hpp Alien.cpp commonstuff.hpp Ship.hpp Ship.cpp ObjectsList.hpp ObjectsList.cpp mainAsteroids.cpp
	g++ -c Shape.cpp
	g++ -c Asteroid.cpp
	g++ -c Bullet.cpp
	g++ -c Flame.cpp
	g++ -c Angel.cpp
	g++ -c Alien.cpp
	g++ -c Ship.cpp
	g++ -c ObjectsList.cpp
	g++ -c mainAsteroids.cpp

clean:
	rm -f *~
	rm -f *.o
	rm mainAsteroids
