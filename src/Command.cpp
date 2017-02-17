#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string>
#include <string.h>
#include "Command.h"

using namespace std;

// private:
//     string cmd;
// public:
//     Command(vector<char*> input;
//     bool evaluate();

Command::Command(string cmd) : cmd(cmd) { }

/* Command::evaluate() utilizes C++ syscalls to execute the proper
 * bash command inputted by the user. If any syscall fails, the 
 * function calls perror and prints a message pertaining to where
 * the error occurred. The function allows for continuous running
 * of the program even after a call to execvp() is executed
 */
bool Command::evaluate() {
    // Process:
    // 1) Convert string cmd into a c_str
    // 2) Create a vector of char*, call strtok() on cmd and fill vector
    // 3) Create a char* array, fill with vector elements
    // 4) Execute command using fork() and execvp()
    
    char* cmd_cstr = (char*)this->cmd.c_str();
    vector<char*> arguments;
    char* tmp_cstr;
    tmp_cstr = strtok(cmd_cstr, " ");
    while (tmp_cstr != NULL) {
        if (tmp_cstr != '\0')
            arguments.push_back(tmp_cstr);
        
        tmp_cstr = strtok(NULL, " ");
    }
    char** args = new char*[arguments.size()+1];   // Char* array to be passed to execvp()

    for (unsigned i = 0; i < arguments.size(); i++) {
        args[i] = arguments.at(i);
    }
    args[arguments.size()] = NULL;

    int status = 0; // Create location in memory for which waitpid status info 
                    // is stored in
    pid_t pid = fork(); // Fork() so execvp() doesn't quit program

    // If error with fork
    if (pid == -1)
        perror("fork");

    // Child process, calls execvp()
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("exec");
            return false;
        }
    }

    // Parent process
    if (pid > 0) {
        if (waitpid(pid, &status, 0) == -1) {
            perror("wait");
            return false;
        }
        
    }

    delete[] args;

    return true;
}
