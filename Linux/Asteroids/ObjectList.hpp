#include "commonstuff.hpp"
#include "Shape.hpp"
#include "Ship.hpp"


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
    
    
    
    
};
