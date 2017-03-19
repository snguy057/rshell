#ifndef RIGHT_H
#define RIGHT_H

#include "Input.h"

class Right : public Input {
private:
    Input* left;
    string right;
public:
    Right();
    // AND(Input* l, Input* r);
    void setLeft(Input* l);
    void setRight(string r);
    bool evaluate();
};

#endif