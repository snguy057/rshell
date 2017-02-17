#include "AND.h"

AND::AND() : left(0), right(0) {}

void AND::setLeft(Input* l) { left = l; }

void AND::setRight(Input* r) { right = r; }

bool AND::evaluate() {
    // If left command is executed, then right command does as well
    if (left->evaluate())
        right->evaluate();
    // If left command does not execute, then AND does not execute
    else
        return false;

    return true;
}
