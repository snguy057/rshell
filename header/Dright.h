#ifndef DRIGHT_H
#define DRIGHT_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include "Input.h"

using namespace std;

class Dright : public Input {
private:
    Input* left;
    string right;
public:
    Dright();
    void setLeft(Input* l);
    void setRight(string r);
    bool evaluate();
};

#endif