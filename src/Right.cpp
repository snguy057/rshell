#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../header/Right.h"

Right::Right() : left(0), right("") {}

void Right::setLeft(Input* l) { left = l; }

void Right::setRight(string r) { right = r; }

bool Right::evaluate() {
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
	int saveOut = dup(1);
	
	// Opens file for input
	int newOut = open(right.c_str(), O_CREAT|O_RDWR);
	
	// if file does not open, then return an error
	if (newOut == -1) {
		perror("Could not open file (out)");
		return false;
	}

	// close the prev. input so we can set the new input
	close(1);
	dup2(newOut, 1);

	// execute left command
	bool success = left->evaluate();

	// Restore std output conditions
	close(1);
	dup2(saveOut, 1);
	
	return success;
}