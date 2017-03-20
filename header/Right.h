#ifndef RIGHT_H
#define RIGHT_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include "Input.h"

using namespace std;

class Right : public Input {
private:
    Input* left;
    string right;
public:
    Right();
    void setLeft(Input* l);
    void setRight(string r);
    bool evaluate();
};

#endif