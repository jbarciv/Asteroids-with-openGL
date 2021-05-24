
#include "commonstuff.hpp"
#include "ObjectsList.hpp"
extern int nShips;

ObjectsList::ObjectsList(){
    Ship *spaceShip;
    push_front(spaceShip);
    for(int i=0 ; i < NUMASTEROIDS; i++){
        Asteroid *asteroid;
        push_front(asteroid);
    }
}
ObjectsList::~ObjectsList(){

}
void ObjectsList::move(){

}
void ObjectsList::draw(){

}
void ObjectsList::add(Shape* s){

}
void ObjectsList::remove(Shape* s){

}
Ship* ObjectsList::getShip(){

}
int ObjectsList::collisions(Bullet* bullet, Ship* ship, float*){

}
void ObjectsList::reposition(Ship* ship){

}