#ifndef PIPE_H
#define PIPE_H

#include "Input.h"
#include <unistd.h>
#include <stdio.h>

class Pipe : public Input {
private:
    Input* left;
    Input* right;
public:
    Pipe();
    void setLeft(Input* l);
    void setRight(Input* r);
    bool evaluate();
};

#endif
