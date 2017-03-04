#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <unistd.h>
#include <string>
#include <stack>

#include "../header/Input.h"
#include "../header/Command.h"
#include "../header/AND.h"
#include "../header/OR.h"
#include "../header/SemiColon.h"
#include "../header/Paren.h"

using namespace std;

bool onlySpace(const string& userInput);

void parse(string& userInput, Input*& inputs);

void makeTree(Input*& inputs, vector<char>& connectors, 
                vector<string>& commands);

Input* makeTree_(vector<char>& connectors, vector<string>& commands, 
                Input*& DecorInput);


int main () {
    // Display command line and read input
    string userInput = "";
    Input* inputs = 0;

    // char host[256];
    // char* user = getlogin();
    // gethostname(host, 256);

    while(1) {
        // cout << user << "@" << host 
        cout << "$ ";
        getline(cin, userInput);
        // cout << userInput << endl;

        // checks if there is no input, only spaces, or comments
        if (userInput == "" || onlySpace(userInput)) {
            continue;
        }
        
        // Calls parse on user's input
        try {
            parse(userInput, inputs);
            inputs->evaluate();
        }
        catch(string s) {
            cout << s << endl;
            continue;
        }

    }
    return 0;
}
// POTENTIAL SUGGESTION: Move all code below to a separate header file so main
// file doesn't look so huge

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
    unsigned openPar = 0; // Counter for opening parentheses
    unsigned closePar = 0;  // Counter for closing parentheses

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
        // Preliminary check for matching parentheses
        else if (userInput.at(i) == '(')
            openPar++;
        else if (userInput.at(i) == ')')
            closePar++;
    }

    // Remove trailing white space
    if (userInput.at(userInput.size()-1) == ' ') {
        unsigned it = userInput.size()-1;
        while (userInput.at(it) == ' ') {
            it--;
        }
        userInput = userInput.substr(0, it+1);
    }

    if (openPar != closePar) {
        string s = "Error: Uneven amount of parentheses";
        throw s;
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
            string pushCmd = userInput.substr(begin, it - begin);
            // ADDING EMPTY STRING SKIP LOGIC
            if (pushCmd != "")
                commands.push_back(pushCmd);
            begin = it + 2;
            commandPushed = 1;
        }

        // checks for OR connector
        else if (userInput.at(it) == '|' &&
                    it < (userInput.size() - 1) &&
                    userInput.at(it + 1) == '|') {
            connectors.push_back('|');
            string pushCmd = userInput.substr(begin, it - begin);
            // ADDING EMPTY STRING SKIP LOGIC
            if (pushCmd != "")
                commands.push_back(pushCmd);
            begin = it + 2;
            commandPushed = 1;
        }

        // checks for '('
        else if (userInput.at(it) == '(') {
            connectors.push_back('(');
            begin = it + 1; // Increment but don't push a cmd
        }

        // checks of ')'
        else if (userInput.at(it) == ')') {
            connectors.push_back(')');
            string pushCmd = userInput.substr(begin, it - begin);
            // ADDING EMPTY STRING SKIP LOGIC
            if (pushCmd != "")
                commands.push_back(pushCmd);
            begin = it + 1;
            commandPushed = 1;
        }
    }
    // if there are no connectors, then push the command to commands
    if (connectors.empty() || connectors.back() != ')')
        commands.push_back(userInput.substr(begin, userInput.size() - begin));

    if (!connectors.empty() && (connectors.back() == ';' 
            || connectors.back() == ')') && commands.back() == "") {
        connectors.pop_back();
        commands.pop_back();
    }

    // Builds the tree of Inputs
    makeTree(inputs, connectors, commands);
}

void makeTree(Input*& inputs, vector<char>& connectors, 
                vector<string>& commands) {

    // ignores the () when checking for empty arguements.
    unsigned conSize = connectors.size();
    for (unsigned i = 0; i < connectors.size(); i++) {
        if (connectors.at(i) == '(' || connectors.at(i) == ')') {
            conSize--;
        }
    }

    // if there are only connectors and no commands OR if the number
    // of commands is <= number of connectors.
    if (commands.size() == 0 || commands.size() <= conSize) {
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

    Input* DecorInput = 0;
    
    // start of recursive calls
    inputs = makeTree_(connectors, commands, DecorInput);

    // SUGGEST: Create while loop to rerun makeTree_ while !connectors.empty()
    // REASON: When a parentheses decorator is created, makeTree_ returns
    //      the decorator as a single Input* to inputs without finishing
    //      the tree for the rest of the command line. Will need to send 
    //      some flag and potential decorator as extra parameter to makeTree_ 
    //      if implement this way.
    while (!connectors.empty()) {
        DecorInput = inputs;    // If connectors not empty, had DecorInput
        inputs = makeTree_(connectors, commands, DecorInput);
    }

}

// a helper function for the recusion
Input* makeTree_(vector<char>& connectors, 
                vector<string>& commands,
                Input*& DecorInput) {
    // base case, returns a Command
    if (commands.size() == 1 && connectors.empty()) {
        return new Command(commands.at(0));
    }

    // builds the tree based on the connector type. in the end it returns the 
    // top node
    // Furthermore, if a DecorInput is detected, then the DecorInput is 
    // automatically set to be the right child of the next connector
    if (connectors.back() == ';') {
        connectors.pop_back();
        SemiColon* con = new SemiColon();
        // con->right = new Command(commands.back());
        if (DecorInput == 0) {
            con->setRight(new Command(commands.back()));
            commands.pop_back();
        }
        else {
            con->setRight(DecorInput);
            DecorInput = 0;
        }
        // con->left = makeTree_(connectors, commands);
        con->setLeft(makeTree_(connectors, commands, DecorInput));
        DecorInput = con;
        return DecorInput;
    }

    if (connectors.back() == '&') {
        connectors.pop_back();
        AND* con = new AND();
        // con->right = new Command(commands.back())
        if (DecorInput == 0) {
            con->setRight(new Command(commands.back()));
            commands.pop_back();
        }
        else {
            con->setRight(DecorInput);
            DecorInput = 0;
        }
        // con->left = makeTree_(connectors, commands)
        con->setLeft(makeTree_(connectors, commands, DecorInput));
        DecorInput = con;
        return DecorInput;
    }

    if (connectors.back() == '|') {
        connectors.pop_back();
        OR* con = new OR();
        // con->right = new Command(commands.back());
        if (DecorInput == 0) {
            con->setRight(new Command(commands.back()));
            commands.pop_back();
        }
        else {
            con->setRight(DecorInput);
            DecorInput = 0;
        }
        // con->left = makeTree_(connectors, commands);
        con->setLeft(makeTree_(connectors, commands, DecorInput));
        DecorInput = con;
        return DecorInput;
    }

    if (connectors.back() == ')') {
        connectors.pop_back();
        vector<char> subConnectors;
        stack<char> conStack;   // Stack for copying connecters to subConnectors
        vector<string> subCommands;
        stack<string> comStack; // Stack for copying commands to subCommands
        unsigned parenCnt = 1;  // Counter for keeping track of nested parens

        // Initial push of last command in parentheses
        if (connectors.back() != ')') {
            comStack.push(commands.back());
            commands.pop_back();
        }
        
        while (parenCnt != 0) {
            if (connectors.back() == '(') {
                parenCnt--;
                conStack.push(connectors.back());
                connectors.pop_back();
            }
            else if (connectors.back() == ')') {
                parenCnt++;
                conStack.push(connectors.back());
                connectors.pop_back();
                if (connectors.back() != ')') {
                    comStack.push(commands.back());
                    commands.pop_back();
                }
            }
            else {
                conStack.push(connectors.back());
                connectors.pop_back();
                // If have nested parens, don't push cmd
                if (connectors.back() != ')') {
                    comStack.push(commands.back());
                    commands.pop_back();
                }
            }
        }

        conStack.pop();  // Pop '(' from stack

        // Population of subConnectors and subCommands
        for (int i = conStack.size(); i > 0; i--) {
            subConnectors.push_back(conStack.top());
            conStack.pop();
        }
        for (int i = comStack.size(); i > 0; i--) {
            subCommands.push_back(comStack.top());
            comStack.pop();
        }

        // Creation of Paren obj
        Paren* con = new Paren(makeTree_(subConnectors, subCommands, 
                                            DecorInput));
        DecorInput = con;
        
        while (!connectors.empty()) {
            DecorInput = makeTree_(connectors, commands, DecorInput);
        }

        return DecorInput; 

    }

    return 0;
}
