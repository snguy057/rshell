#ifndef LEFT_H
#define LEFT_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include "Input.h"

using namespace std;

class Left : public Input {
private:
    Input* left;
    string right;
public:
    Left();
    void setLeft(Input* l);
    void setRight(string r);
    bool evaluate();
};

#endif