#include "../header/Left.h"

Left::Left() : left(0), right(0) {}

void Left::setLeft(Input* l) { left = l; }

void Left::setRight(string r) { right = r; }

bool Left::evaluate() {
	return false;
}