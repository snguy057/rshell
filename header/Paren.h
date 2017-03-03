/*
 * Header file for parentheses precedence handling class. Essentially is a
 * Decorator element which allows tree of Input* to view the commands contained
 * within parentheses as a single connector/command node
 */

#ifndef PAREN_H
#define PAREN_H

#include "Input.h"

class Paren : public Input {
private:
    Input* child;
public:
    Paren(Input* ch);
    bool evaluate();
};

#endif