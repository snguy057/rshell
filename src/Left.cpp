#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../header/Left.h"

Left::Left() : left(0), right("") {}

void Left::setLeft(Input* l) { left = l; }

void Left::setRight(string r) { right = r; }

bool Left::evaluate() {
	// Removing leading whitespace
    if (right.at(0) == ' ') {
        unsigned it = 0;
        while (right.at(it) == ' ') {
            it++;
        }
        right = right.substr(it);
    }

    // Removing trailing whitespace
    if (right.at(right.size()-1) == ' ') {
        unsigned it = right.size()-1;
        while (right.at(it) == ' ') {
            it--;
        }
        right = right.substr(0, it+1);
    }

	// saves stdinput buffer
	int saveIn = dup(0);
	
	// Opens file for input
	int newIn = open(right.c_str(), O_RDWR);
	
	// if file does not open, then return an error
	if (newIn == -1) {
		perror("Could not open file (in)");
		return false;
	}

	// close the prev. input so we can set the new input
	close(0);
	dup2(newIn, 0);

	// execute left command
	bool success = left->evaluate();

	// Restore std output conditions
	close(0);
	dup(saveIn);
	
	return success;
}