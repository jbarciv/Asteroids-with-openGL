
#include "Shape.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Ship.hpp"
#include "Flame.hpp"

#ifndef __OBJECTSLIST_H_
#define __OBJECTSLIST_H_

class ObjectsList: list<Shape*>
{
    private:
        int n;
        Shape* head;
    public:
        Ship* theShip;
    public:
        ObjectsList();
        ~ObjectsList();
        void move();
        void draw();
        void add(Shape* s);
        void remove(Shape* s);
        Ship* getShip();
        int collisions(Bullet* bullet, Ship* ship, float*);
        void reposition(Ship* ship);
};

#endif