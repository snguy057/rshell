#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../header/Dright.h"

Dright::Dright() : left(0), right(0) {}

void Dright::setLeft(Input* l) { left = l; }

void Dright::setRight(string r) { right = r; }

bool Dright::evaluate() {
	return false;
}