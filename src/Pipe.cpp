#include "../header/Pipe.h"

Pipe::Pipe() : left(0), right(0) {}

void Pipe::setLeft(Input* l) { left = l; }

void Pipe::setRight(string r) { right = r; }

bool Pipe::evaluate() {
	return false;
}