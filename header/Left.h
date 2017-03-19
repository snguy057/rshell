#ifndef LEFT_H
#define LEFT_H

#include "Input.h"

class Left : public Input {
private:
    Input* left;
    string right;
public:
    Left();
    // AND(Input* l, Input* r);
    void setLeft(Input* l);
    void setRight(string r);
    bool evaluate();
};

#endif