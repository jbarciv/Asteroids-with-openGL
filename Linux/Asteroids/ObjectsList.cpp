
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
    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
    {   
        if((*i) == theShip) continue;
        if((*i) == bullet) continue;
        float pos_a[3];
        (*i) -> getPos(pos_a);
        float size_a = (*i)->getSize();
        cout << "Por ahora NO collision!" << endl;
        if(mydistance(pos_a[0], pos_a[1], pos_s[0], pos_s[1]) < (size_a + size_s)) 
        {
            cout << "pos_s[x]=" <<  pos_s[0] << endl;
            cout << "pos_s[y]=" <<  pos_s[1] << endl;
            cout << "pos_a[x]=" <<  pos_a[0] << endl;
            cout << "pos_a[y]=" <<  pos_a[1] << endl;
            cout << "mydistance=" <<  mydistance(pos_a[0], pos_a[1], pos_s[0], pos_s[1]) << endl;
            cout << "size plus=" <<  (size_a + size_s) << endl;


            worldobjects.remove(ship);
            cout << "YES COLLISION!" << endl;
            return 1;
        }
        if(bullet)
        {   
            cout << "THERE IS A BULLET" << endl;
            float pos_b[3];
            bullet -> getPos(pos_b);
            float size_b = bullet -> getSize();
            if(mydistance(pos_a[0], pos_a[1], pos_b[0], pos_b[1]) < (size_a + size_b))
            {   
                cout << "ASTEROID GOLPEADO" << endl;
                worldobjects.remove(bullet);
                if( size_a == SMALL)
                {
                    worldobjects.remove(*i);
                    cout << "ASTEROIDE DESTRUIDO" << endl;
                    return 4;
                } else if(size_a == MEDIUM || size_a == BIG)
                {  
                    Asteroid *x = new Asteroid;
                    x = (Asteroid*) (*i);
                    worldobjects.push_front(x->split());
                    cout << "ASTEROIDE DEBILITADO!" << endl;
                }
            }
        }
    }
    return 0;
}

void ObjectsList::reposition(Ship* ship)
{
        
}