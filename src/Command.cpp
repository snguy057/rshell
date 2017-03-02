#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
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

    // Exit check
    if (cmd == "exit")
        exit(0);

    // Test Command Check
    if (cmd.at(0) == '[' && cmd.at(cmd.size() - 1) == ']') {
        cmd.replace(0, 1, "test ");
        cmd.erase(cmd.size() - 1);
    }

    if (cmd == "test" || cmd == "test ") {
        cout << "(FALSE)" << endl;
        return false;
    }
    else if (cmd.substr(0, 5) == "test ") {
        return testEvaluate(); 
    }

    // Conversion to c string, creating char* vector
    char* cmd_cstr = (char*)this->cmd.c_str();
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

// Helper that executes the test command
bool Command::testEvaluate() {
    // clears test and trailing whitespace
    if (4 < cmd.size() && cmd.at(4) == ' ') {
        unsigned it = 4;
        while (it < cmd.size() && cmd.at(it) == ' ') {
            it++;
        }
        if (it < cmd.size()) {
            cmd = cmd.substr(it);   
        }
        else {
            cout << "(FALSE)" << endl;
            return false;
        }
    }

    string flag = cmd.substr(0, 2);

    struct stat s;

    // checks for a flag
    if (flag.at(0) == '-') {
        // Clears whitespace after the flag 
        if (2 < cmd.size() && cmd.at(2) == ' ') {
            unsigned it = 2;
            while (it < cmd.size() && cmd.at(it) == ' ') {
                it++;
            }
            cmd = cmd.substr(it);
        }
        
        // Checks if for a valid flag.
        if (flag != "-f" && flag != "-d" && flag != "-e") {
            string er = "Invalid flag passed into the test."; 
            throw er;
            return false;
        }  

        if (stat(cmd.c_str(), &s) == -1) {
            cout << "(FALSE)" << endl;
            return false;
        }

        // Flag is -f
        if (flag == "-f") {
            if (S_ISREG(s.st_mode)) {
                cout << "(TRUE)" << endl;
                return true;
            }
            cout << "(FALSE)" << endl;
            return false;
        }
        // Flag is -d 
        else if (flag == "-d") {
            if (S_ISDIR(s.st_mode)) {
                cout << "(TRUE)" << endl;
                return true;
            }
            cout << "(FALSE)" << endl;
            return false;
        }
        
        else if (flag == "-e") {
            cout << "(TRUE)" << endl;
            return true;
            
        }
    }

    // No flag
    if (stat(cmd.c_str(), &s) == -1) {
        cout << "(FALSE)" << endl;
        return false;
    }
    
    cout << "(TRUE)" << endl;
    return true;
    
}
