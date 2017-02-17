#ifndef AND_H
#define AND_H

#include "Input.h"

class AND : public Input {
private:
    Input* left;
    Input* right;
public:
    AND();
    // AND(Input* l, Input* r);
    void setLeft(Input* l);
    void setRight(Input* r);
    bool evaluate();
};

#endif
