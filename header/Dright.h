#ifndef DRIGHT_H
#define DRIGHT_H

#include "Input.h"

class Dright : public Input {
private:
    Input* left;
    string right;
public:
    Dright();
    // AND(Input* l, Input* r);
    void setLeft(Input* l);
    void setRight(string r);
    bool evaluate();
};

#endif