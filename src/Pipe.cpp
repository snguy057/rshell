#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <string.h>
#include <vector>
#include "../header/Pipe.h"

Pipe::Pipe() : left(0), right("") {}

void Pipe::setLeft(Input* l) { left = l; }

void Pipe::setRight(string r) { right = r; }

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

    // FIXME BELOW
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

    // Conversion to c string, creating char* vector
    char* cmd_cstr = (char*)right.c_str();
    vector<char*> arguments;
    char* tmp_cstr;
    tmp_cstr = strtok(cmd_cstr, " ");
    while (tmp_cstr != NULL) {
        if (tmp_cstr != '\0')
            arguments.push_back(tmp_cstr);
        
        tmp_cstr = strtok(NULL, " ");
    }

    // Char* array to be passed to execvp()
    char** args = new char*[arguments.size()+1];

    for (unsigned i = 0; i < arguments.size(); i++) {
        args[i] = arguments.at(i);
    }
    args[arguments.size()] = NULL;

    int status; // Create location in memory for which waitpid status info 
                    // is stored in

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

    // 6) execute right
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

    // Deallocating char** b/c no longer needed
    delete[] args;

    // Parent process
    if (pid > 0) {
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
        waitpid(pid, &status, 0);
        if (status > 0) // If status returned, execvp failed
            return false;
        else if (WEXITSTATUS(status) == 0)  // Successful execution
            return true;
        else if (WEXITSTATUS(status) == 1)  // Unsuccessful execution
            return false;
        
    }

    // Shouldn't be hit
    return false;
}