#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <unistd.h>
#include <string>

#include "../header/Input.h"
#include "../header/Command.h"
#include "../header/AND.h"
#include "../header/OR.h"
#include "../header/SemiColon.h"

using namespace std;

bool onlySpace(const string& userInput);

void parse(string& userInput, Input*& inputs);

void makeTree(Input*& inputs, vector<char>& connectors, 
                vector<string>& commands);

Input* makeTree_(vector<char>& connectors, vector<string>& commands);


int main () {
    // Display command line and read input
    string userInput = "";
    Input* inputs = 0;

    char host[256];
    char* user = getlogin();
    gethostname(host, 256);

    while(1) {
        cout << user << "@" << host << "$ ";
        getline(cin, userInput);
        // cout << userInput << endl;

        // checks if there is no input, only spaces, or comments
        if (userInput == "" || onlySpace(userInput)) {
            continue;
        }
        
        // Calls parse on user's input
        try {
            parse(userInput, inputs);
        }
        catch(string s) {
            cout << s << endl;
            continue;
        }

        inputs->evaluate();
    }
    return 0;
}

// checks for only spaces or if comments
bool onlySpace(const string& userInput) {
    for (unsigned it = 0; it < userInput.size(); it++) {
        if (userInput.at(it) != ' ' && userInput.at(it) != '#') {
            return false;
        }
        else if (userInput.at(it) == '#') {
            return true;
        }
    }

    return true;
} 

void parse(string& userInput, Input*& inputs) {
    bool commentFound = 0;
    // bool openingQuote = 0;
    bool closingQuote = 0;
    // bool semicolon = 0;
    // bool AND = 0;
    // bool OR = 0;
    bool closingTest = 0;

    bool commandPushed = 0;

    vector<char> connectors;
    vector<string> commands;

    // index on string we are beginning at
    unsigned begin = 0;

    // searches for comments and resizes the string to all 
    // whitespace and comments
    for (unsigned i = 0; i < userInput.size() && !commentFound; i++) {
        if (userInput.at(i) == '#') {
            userInput = userInput.substr(begin, i - begin);
            commentFound = 1;
        }
    }
        
    for (unsigned it = 0; it < userInput.size(); it++) {
        // ignore any leading whitespace
        if (commandPushed == 1) {
            while (userInput.at(it) == ' ' && it < userInput.size()) {
                it++;
                begin++;
            }
            commandPushed = 0;
        }

        // checks for opening and closing quotes
        if (userInput.at(it) == '\"') {
            // openingQuote = 1;
            it++;
            while (closingQuote == 0 && it < userInput.size()) {
                if (userInput.at(it) == '\"') {
                    closingQuote = 1;
                }
                else {
                    it++;
                }
            }
            if (closingQuote == 0) {
                string s = "Error no closingQuote found";
                throw s;
            }
            closingQuote = 0;
        }

        else if (userInput.at(it) == '\'') {
            // openingQuote = 1;
            it++;
            while (closingQuote == 0 && it < userInput.size()) {
                if (userInput.at(it) == '\'') {
                    closingQuote = 1;
                }
                else {
                    it++;
                }
            }
            if (closingQuote == 0) {
                string s = "Error no closingQuote found";
                throw s;
            }
            closingQuote = 0;
        }

        // looks for the test [ ]
        else if (userInput.at(it) == '[') {
            // int testBegin = it;
            it++;
            while (closingTest == 0 && it < userInput.size()) {
                if (userInput.at(it) == ']') {
                    closingTest = 1;
                    // userInput.erase(it, 1);
                    // userInput.replace(testBegin, 1, "test "); 
                }
                else {
                    it++;
                }
            }
            if (closingTest == 0) {
                string s = "Error no closing ']' found";
                throw s;
            }
            closingTest = 0;
        }

        // checks for semicolon connector
        else if (userInput.at(it) == ';') {
            connectors.push_back(';');
            commands.push_back(userInput.substr(begin, it - begin));
            begin = it + 1;
            commandPushed = 1;
        }

        // checks for AND connector
        else if (userInput.at(it) == '&' &&
                    it < (userInput.size() - 1) &&
                    userInput.at(it + 1) == '&') {
            connectors.push_back('&');
            commands.push_back(userInput.substr(begin, it - begin));
            begin = it + 2;
            commandPushed = 1;
        }

        // checks for OR connector
        else if (userInput.at(it) == '|' &&
                    it < (userInput.size() - 1) &&
                    userInput.at(it + 1) == '|') {
            connectors.push_back('|');
            commands.push_back(userInput.substr(begin, it - begin));
            begin = it + 2;
            commandPushed = 1;
        }
    }
    // if there are no connectors, then push the command to commands
    commands.push_back(userInput.substr(begin, userInput.size() - begin));

    if (!connectors.empty() && connectors.back() == ';' 
            && commands.back() == "") {
        connectors.pop_back();
        commands.pop_back();
    }

    // Builds the tree of Inputs
    makeTree(inputs, connectors, commands);
}

void makeTree(Input*& inputs, vector<char>& connectors, 
                vector<string>& commands) {

    // checks to see if there are any empty commands
    for(unsigned i = 0; i < commands.size(); i++) {
        if (commands.at(i) == "") {
            string s = "Error empty arguement(s) passed into a connector";
            throw s;
        }
    }

    // if there are only connectors and no commands OR if the number
    // of commands is <= number of connectors.
    if (commands.size() == 0 || commands.size() <= connectors.size()) {
        string s = "Error empty arguement(s) passed into a connector";
        throw s;
    }

    // if there is only one command with no connectors, just return that 
    // command
    if (commands.size() == 1) {
        Input* in = new Command(commands.at(0));
        inputs = in;
        in = 0;
        return;
    }
    
    // start of recursive calls
    inputs = makeTree_(connectors, commands);
}

// a helper function for the recusion
Input* makeTree_(vector<char>& connectors, 
                vector<string>& commands) {
    // base case, returns a Command
    if (commands.size() == 1) {
        return new Command(commands.at(0));
    }

    // builds the tree based on the connector type. in the end it returns the 
    // top node
    if (connectors.back() == ';') {
        connectors.pop_back();
        SemiColon* con = new SemiColon();
        // con->right = new Command(commands.back());
        con->setRight(new Command(commands.back()));
        commands.pop_back();
        // con->left = makeTree_(connectors, commands);
        con->setLeft(makeTree_(connectors, commands));
        return con;
    }

    if (connectors.back() == '&') {
        connectors.pop_back();
        AND* con = new AND();
        // con->right = new Command(commands.back())
        con->setRight(new Command(commands.back()));
        commands.pop_back();
        // con->left = makeTree_(connectors, commands)
        con->setLeft(makeTree_(connectors, commands));
        return con;
    }

    if (connectors.back() == '|') {
        connectors.pop_back();
        OR* con = new OR();
        // con->right = new Command(commands.back());
        con->setRight(new Command(commands.back()));
        commands.pop_back();
        // con->left = makeTree_(connectors, commands);
        con->setLeft(makeTree_(connectors, commands));
        return con;
    }

    return 0;
}
