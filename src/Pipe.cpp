#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../header/Pipe.h"

Pipe::Pipe() : left(0), right(0) {}

void Pipe::setLeft(Input* l) { left = l; }

void Pipe::setRight(Input* r) { right = r; }

bool Pipe::evaluate() {
	return false;
}