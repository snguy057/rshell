#ifndef PIPE_H
#define PIPE_H

#include "Input.h"
#include <unistd.h>
#include <stdio.h>
#include <string>

using namespace std;

class Pipe : public Input {
private:
    Input* left;
    string right;
public:
    Pipe();
    void setLeft(Input* l);
    void setRight(string r);
    bool evaluate();
};

#endif
