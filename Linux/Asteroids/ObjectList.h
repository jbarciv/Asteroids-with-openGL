 
#include "Shape.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Ship.h"
#include "Flame.h"

class ObjectList{
    private:
        int n;
        nodo* head;
    public:
        Ship* theShip;
    public:
        ObjectList();
        ~ObjectList();
        void move();
        void draw();
        void add(Shape* s);
        void remove(Shape* s);
        Ship* getShip();
        int collision(Bullet* bullet, Ship* ship, float*);
        void reposition(Ship* ship);
};