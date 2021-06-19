////////////////////////////////////////
// Angel.hpp                          //
// Class implementation for the Angel //
////////////////////////////////////////

#include "commonstuff.hpp"
#include "Shape.hpp"

class Angel: public Shape{
 private:
    bool status;
    int tamano;
 public:
    Angel();
    ~Angel();
    void setStatus(bool);
    bool getStatus();
    void setSize(int);
    float getSize();
    void draw();
    void teleport();
};