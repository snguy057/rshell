#include "../header/SemiColon.h"

SemiColon::SemiColon() : left(0), right(0) {}

void SemiColon::setLeft(Input* l) { left = l; }

void SemiColon::setRight(Input* r) { right = r; }

bool SemiColon::evaluate() {
    // For semicolon, both commands execute regardless
    left->evaluate();
    right->evaluate();
    return true;
}
