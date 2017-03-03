#include "../header/Paren.h"

Paren::Paren(Input* ch) : child(ch) { }

bool Paren::evaluate() {
    return child->evaluate();
}