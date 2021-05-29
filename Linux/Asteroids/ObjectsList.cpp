
#include "commonstuff.hpp"
#include "ObjectsList.hpp"
#include "Asteroid.hpp"
using namespace std;

extern int nShips;
extern ObjectsList worldobjects;

ObjectsList::ObjectsList()
{   
    n = 0; // List begins empty
    head = NULL; // it does not make sense with list<> template
    theShip = new Ship;
    worldobjects.push_front(theShip);
    for(int i=0 ; i < NUMASTEROIDS; i++)
    {
        Asteroid *asteroid = new Asteroid;
        worldobjects.push_front(asteroid);
    }
}

ObjectsList::~ObjectsList()
{
    worldobjects.clear();
}

void ObjectsList::move()
{
    cout << "entro en ObjectsList::move " << endl;

    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
        (*i)->move();
}

void ObjectsList::draw()
{
    cout << "Entro en ObjectsList::draw" << endl;

    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
        (*i)->draw();
}

void ObjectsList::add(Shape* s)
{
    worldobjects.push_front(s);
}

void ObjectsList::removes(Shape* s)
{
    worldobjects.remove(s);
}

Ship* ObjectsList::getShip()
{
    return theShip;
}

int ObjectsList::collisions(Bullet* bullet, Ship* ship, float* explos)
{   
    cout << "Entro en ObjectsList::collision" << endl;
    float pos_s[3];
    ship -> getPos(pos_s);
    float size_s = ship->getSize();
    cout << "collision0!" << endl;

    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
    {   
        cout << "collision1!" << endl;
        if((*i) == theShip) continue;
        if((*i) == bullet) continue;
        cout << "collision2!" << endl;
        float pos_a[3];
        (*i) -> getPos(pos_a);
        float size_a = (*i)->getSize();
        cout << "collision3!" << endl;
        if(mydistance(pos_a[0], pos_a[1], pos_s[0], pos_s[1]) < (size_a + size_s)) 
        {
            cout << "collision3.5!" << endl;
            worldobjects.remove(ship);
            return 1;
        }
        if(bullet)
        {   
            cout << "collision4!" << endl;
            float pos_b[3];
            bullet -> getPos(pos_b);
            float size_b = bullet -> getSize();
            cout << "collision5!" << endl;
            if(mydistance(pos_a[0], pos_a[1], pos_b[0], pos_b[1]) < (size_a + size_b))
            {   
                cout << "collision5.5!" << endl;
                worldobjects.remove(bullet);
                cout << "collision6!" << endl;
                if( size_a == SMALL)
                {
                    cout << "collision7!" << endl;
                    worldobjects.remove(*i);
                    cout << "collision8!" << endl;
                    return 4;
                } else if(size_a == MEDIUM || size_a == BIG)
                {   
                    cout << "explode0!" << endl;
                    Asteroid *x = new Asteroid;
                    cout << "explode1!" << endl;
                    x = (Asteroid*) (*i);
                    cout << "explode2!" << endl;
                    worldobjects.push_front(x->split());
                    cout << "explode3!" << endl;
                }
            }
        }
    }
    return 0;
}

void ObjectsList::reposition(Ship* ship)
{
        
}