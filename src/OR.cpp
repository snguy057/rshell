#include "../header/OR.h"

OR::OR() : left(0), right(0) {}

void OR::setLeft(Input* l) { left = l; }

void OR::setRight(Input * r) { right = r; }

bool OR::evaluate() {
    // If left command is not executed, then right command executes
    if(!left->evaluate())
        right->evaluate();

    return true;
}
