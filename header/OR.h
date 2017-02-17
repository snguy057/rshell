#ifndef OR_H
#define OR_H

#include "Input.h"

class OR : public Input {
private:
    Input* left;
    Input* right;
public:
    OR();
    // OR(Input* l, Input* r);
    void setLeft(Input* l);
    void setRight(Input* r);
    bool evaluate();
};

#endif
