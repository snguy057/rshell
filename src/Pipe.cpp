#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../header/Pipe.h"

Pipe::Pipe() : left(0), right(0) {}

void Pipe::setLeft(Input* l) { left = l; }

void Pipe::setRight(Input* r) { right = r; }

bool Pipe::evaluate() {
	// 1) pipe
    int pipe1[2];
    pipe(pipe1);
    
    // 2) overwrite standard output -- SAVE OUTPUT
    int saveOut = dup(1);
    if (saveOut == -1) {
        perror("dup out");
        return false;
    }
    if (dup2(pipe1[1], 1) == -1) {
        perror("out dup2");
        return false;
    }

    // 3) run left
    bool leftside = left->evaluate();

    if (!leftside) {
        return false;
    }

    // 4) restore standard output
    if (dup2(saveOut, 1) == -1) {
        perror("leftside restore");
        return false;
    }

    // 5) overwrite standard input -- SAVE
    int saveIn = dup(0);
    if (saveIn == -1) {
        perror("dup in");
        return false;
    }
    if (dup2(pipe1[0], 0) == -1) {
        perror("in dup2");
        return false;
    }

    // 6) call right
    bool rightside = right->evaluate();

    // 7) restore standard input
    if (dup2(saveIn, 0) == -1) {
        perror("rightside restore");
        return false;
    }

    if (close(pipe1[0]) == -1) {
        perror("close 0");
        return false;
    }
    if (close(pipe1[1]) == -1) {
        perror("close 1");
        return false;
    }

    // 8) return value
    if (leftside && rightside)
        return true;
    else
        return false;
}