#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../header/Right.h"

Right::Right() : left(0), right("") {}

void Right::setLeft(Input* l) { left = l; }

void Right::setRight(string r) { right = r; }

bool Right::evaluate() {
	return false;
}