#ifndef PIPE_H
#define PIPE_H

#include "Input.h"

class Pipe : public Input {
private:
    Input* left;
    Input* right;
public:
    Pipe();
    // OR(Input* l, Input* r);
    void setLeft(Input* l);
    void setRight(Input* r);
    bool evaluate();
};

#endif
