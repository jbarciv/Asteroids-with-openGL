
#include "Asteroid.hpp"
#include "Shape.hpp"
#include "Bullet.hpp"
#include "Alien.hpp"
#include "Ship.hpp"
#include "Flame.hpp"
#include "Angel.hpp"
using namespace std;

#ifndef __OBJECTSLIST_H_
#define __OBJECTSLIST_H_

class ObjectsList: public list<Shape*>
{
    
    private:
        int n;
        Shape* head;
    public:
        Ship* theShip;
        Alien* theUFO;
        Angel* theAngel;
    public:
        ObjectsList();
        ~ObjectsList();
        void move();
        void draw();
        void add(Shape* s);
        void removes(Shape* s);
        Ship* getShip();
        Alien* getUFO();
        Angel* getAngel();
        int collisions(Bullet* bullet, Ship* ship, Alien* ufo, Angel* angel, float*);
        void reposition(Ship* ship);
};

#endif