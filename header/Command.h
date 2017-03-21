/*
 * Header file for Command class to implement bash commands
 * using C++ syscalls
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "Input.h"
#include <vector>
#include <string>

using namespace std;

class Command : public Input {
private:
    string cmd;
public:
    Command(string cmd);
    string getCmd();
    bool evaluate();

    bool testEvaluate();
};

#endif
