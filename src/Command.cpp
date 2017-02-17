#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string>
#include <string.h>
#include "../header/Command.h"

using namespace std;

Command::Command(string cmd) : cmd(cmd) { }

/* Command::evaluate() utilizes C++ syscalls to execute the proper
 * bash command inputted by the user. If any syscall fails, the 
 * function calls perror and prints a message pertaining to where
 * the error occurred. The function allows for continuous running
 * of the program even after a call to execvp() is executed
 */
bool Command::evaluate() {
    // Process:
    // 1) Remove leading and trailing whitespace from cmd
    // 2) Convert string cmd into a c_str
    // 3) Create a vector of char*, call strtok() on cmd and fill vector
    // 4) Create a char* array, fill with vector elements
    // 5) Execute command using fork() and execvp()
    
    // Removing leading whitespace
    if (cmd.at(0) == ' ') {
        unsigned it = 0;
        while (cmd.at(it) == ' ') {
            it++;
        }
        cmd = cmd.substr(it);
    }

    // Removing trailing whitespace
    if (cmd.at(cmd.size()-1) == ' ') {
        unsigned it = cmd.size()-1;
        while (cmd.at(it) == ' ') {
            it--;
        }
        cmd = cmd.substr(0, it+1);
    }

    if (cmd == "exit")
        exit(0);

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

    int status; // Create location in memory for which waitpid status info 
                    // is stored in
    pid_t pid = fork(); // Fork() so execvp() doesn't quit program

    // If error with fork
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    // Child process, calls execvp()
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("exec");
            exit(1);
        }
    }

    delete[] args;

    // Parent process
    if (pid > 0) {
        waitpid(pid, &status, 0);
        if (status > 0)
            return false;
        else if (WEXITSTATUS(status) == 0)
            return true;
        else if (WEXITSTATUS(status) == 1)
            return false;
        
    }

    return true;
}
