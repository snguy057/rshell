#include "../header/Right.h"

Right::Right() : left(0), right(0) {}

void Right::setLeft(Input* l) { left = l; }

void Right::setRight(string r) { right = r; }

bool Right::evaluate() {
	return false;
}