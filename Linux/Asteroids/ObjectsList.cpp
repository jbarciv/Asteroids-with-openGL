
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
    theUFO = new Alien;
}

ObjectsList::~ObjectsList()
{
    worldobjects.clear();
}

void ObjectsList::move()
{
    // cout << "entro en ObjectsList::move " << endl;

    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
        (*i)->move();

}

void ObjectsList::draw()
{
    //cout << "Entro en ObjectsList::draw" << endl;

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

Alien* ObjectsList::getUFO(){
    return theUFO;
}
int ObjectsList::collisions(Bullet* bullet, Ship* ship, Alien* ufo, float* explos)
{   
    cout << "Entro en ObjectsList::collision" << endl;
    float pos_s[3];
    ship -> getPos(pos_s);
    float size_s = ship->getSize();
    float size_u = ufo -> getSize();
    float pos_u[3];
    ufo -> getPos(pos_u);
    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
    {      
        if((*i) == theShip) continue;   // We skip theShip and the bullet
        if((*i) == bullet) continue;
    
        float pos_a[3];                
        (*i) -> getPos(pos_a);
        float size_a = (*i)->getSize();
        // cout << "Por ahora NO collision!" << endl;
        if(mydistance(pos_a[0], pos_a[1], pos_s[0], pos_s[1]) < (size_a + size_s)) 
        {
            // cout << "pos_s[x]=" <<  pos_s[0] << endl;
            // cout << "pos_s[y]=" <<  pos_s[1] << endl;
            // cout << "pos_a[x]=" <<  pos_a[0] << endl;
            // cout << "pos_a[y]=" <<  pos_a[1] << endl;
            // cout << "mydistance=" <<  mydistance(pos_a[0], pos_a[1], pos_s[0], pos_s[1]) << endl;
            // cout << "size plus=" <<  (size_a + size_s) << endl;
            explos[0] = pos_s[0];
            explos[1] = pos_s[1];
            worldobjects.remove(ship);
            // cout << "YES COLLISION!" << endl;
            return 1;
        }
        if(mydistance(pos_u[0], pos_u[1], pos_s[0], pos_s[1]) < (size_u + size_s) && ufo->getStatus() == ACTIVE) 
        {
            // cout << "pos_s[x]=" <<  pos_s[0] << endl;
            // cout << "pos_s[y]=" <<  pos_s[1] << endl;
            // cout << "pos_a[x]=" <<  pos_a[0] << endl;
            // cout << "pos_a[y]=" <<  pos_a[1] << endl;
            // cout << "mydistance=" <<  mydistance(pos_a[0], pos_a[1], pos_s[0], pos_s[1]) << endl;
            // cout << "size plus=" <<  (size_a + size_s) << endl;
            explos[0] = pos_s[0];
            explos[1] = pos_s[1];
            worldobjects.remove(ship);
            worldobjects.push_back(ufo);
            // cout << "YES COLLISION!" << endl;
            return 6;
        }
        if(bullet)
        {   
            float pos_b[3];
            bullet -> getPos(pos_b);
            float size_b = bullet -> getSize();
            if(mydistance(pos_a[0], pos_a[1], pos_b[0], pos_b[1]) < (size_a + size_b))
            {   
                cout << "ASTEROID GOLPEADO" <<endl;
                worldobjects.remove(bullet);
                size_a = size_a / CONSTANT;
                if( size_a == SMALL)
                {
                    worldobjects.remove(*i);
                    cout << "ASTEROIDE DESTRUIDO" << endl;
                    explos[0] = pos_a[0];
                    explos[1] = pos_a[1];
                    return 4;
                } else if(size_a == MEDIUM || size_a == BIG)
                {  
                    Asteroid *x = new Asteroid;     // Cast from Shape* to Asteroid*
                    x = (Asteroid*) (*i);
                    worldobjects.push_front(x->split());
                    cout << "ASTEROIDE DEBILITADO!" << endl;
                    explos[0] = pos_a[0];
                    explos[1] = pos_a[1];
                    return (size_a == MEDIUM) ? 2 : 3;
                } 
                
            }
            if(mydistance(pos_u[0], pos_u[1], pos_b[0], pos_b[1]) < (size_u + size_b))
            {
                worldobjects.removes(ufo);
                worldobjects.removes(bullet);
                cout << "OVNI DERRIBADO, ALIEN ANIQUILADO" << endl;
                explos[0] = pos_a[0];
                explos[1] = pos_a[1];
                return 5;
            }
        }
    }
    return 0;
}

void ObjectsList::reposition(Ship* ship) // se podría hacer un variante que es esperar a que no haya ninguno cerca
{
    cout << "Entro en ObjectsList::reposition" << endl;
    float size_s = ship->getSize();
    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
    {      
        if((*i) == theShip) continue;   // We skip theShip
        float pos_a[3];
        (*i) -> getPos(pos_a);
        float size_a = (*i)->getSize();

        if(mydistance(pos_a[0], pos_a[1], 0.0, 0.0) < (size_a + size_s)) 
        {   
            Asteroid *x = new Asteroid;     // Cast from Shape* to Asteroid*
            x = (Asteroid*) (*i);
            x->reposition();            
        }
    }
    worldobjects.push_front(ship);
}