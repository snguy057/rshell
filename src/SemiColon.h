#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "Input.h"

class SemiColon : public Input {
private:
    Input* left;
    Input* right;
public:
    SemiColon();
    // SemiColon(Input* l, Input* r);
    void setLeft(Input* l);
    void setRight(Input* r);
    bool evaluate();
};

#endif
