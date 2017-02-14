#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "Input.h"

using namespace std;

bool onlySpace(const string& userInput);

void parse(string& userInput, vector<Input*>& inputs);

void makeTree(vector<Input*>& inputs, vector<char>& connectors, 
                vector<string>& commands);

Input* makeTree_(vector<char>& connectors, vector<string>& commands);

/*  Note for Ethan!!!
    I am going to be creating the commands giving you a string NOT a cstring.
    Also I am going to assume that the class names are as follows:
        Connector
        Command
        AND
        OR
        SemiColon

    I have decieded to build the Input tree using recursion becuase it allows
    us to have a "indefinite" ammount of commands.  This also means that we 
    I may have to make the parse function return a Input*.  Read my code over
    and hopefully you understand it. If you have any questions, i'll talk to 
    you about it (face to face, lul i can't explain in text).
*/

int main () {
    // Display command line and read input
    string userInput = "";
    vector<Input*> inputs; 

    cout << "$ ";
    getline(cin, userInput);

    // checks if there is no input, only spaces, or comments
    while (userInput == "" || onlySpace(userInput)) {
        cout << "$ ";
        getline(cin, userInput);
    }

    if (userInput == "exit") {
        exit(0);
    }
    // Converts input from string to cstring
    // char userCstr[userInput.size() + 1];
    // strcpy(userCstr, userInput.c_str());

    // Calls parse on user's input
    try {
        parse(userInput, inputs);
    }
    catch(string s) {
        cout << s << endl;
    }
    return 0;
}

// checks for only spaces or if comments
bool onlySpace(const string& userInput) {
    for (int it = 0; it < userInput.size(); it++) {
        if (userInput.at(it) != ' ' && userInput.at(it) != '#') {
            return false;
        }
        else if (userInput.at(it) == '#') {
            return true;
        }
    }

    return true;
} 

void parse(string& userInput, vector<Input*>& inputs) {
    bool commentFound = 0;
    bool openingQuote = 0;
    bool closingQuote = 0;
    bool semicolon = 0;
    bool AND = 0;
    bool OR = 0;

    vector<char> connectors;
    vector<string> commands;

    // index on string we are beginning at
    int begin = 0;

    // seraches for comments and resizes the string to all 
    // whitespace and comments
    for (int i = 0; i < userInput.size() && !commentFound; i++) {
        if (userInput.at(i) == '#') {
            userInput = userInput.substr(begin, i - begin);
            commentFound = 1;
        }
    }

    for (int it = 0; it < userInput.size(); it++) {
        // ignore any leading whitespace
        while (userInput.at(it) == ' ' && it < userInput.size()) {
            it++;
            begin++;
        }

        // checks for opening and closing quotes
        if (userInput.at(it) == '\"') {
            openingQuote = 1;
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
        }

        else if (userInput.at(it) == '\'') {
            openingQuote = 1;
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
        }

        // checks for semicolon connector
        else if (userInput.at(it) == ';') {
            connectors.push_back(';');
            commands.push_back(userInput.substr(begin, it - begin));
            begin = it + 1;
        }

        // checks for AND connector
        else if (userInput.at(it) == '&' &&
                    it < (userInput.size() - 1) &&
                    userInput.at(it + 1) == '&') {
            connectors.push_back('&');
            commands.push_back(userInput.substr(begin, it - begin));
            begin = it + 2;
        }

        // checks for OR connector
        else if (userInput.at(it) == '|' &&
                    it < (userInput.size() - 1) &&
                    userInput.at(it + 1) == '|') {
            connectors.push_back('|');
            commands.push_back(userInput.substr(begin, it - begin));
            begin = it + 2;
        }
    }
    // if there are no connectors, then push the command to commands
    commands.push_back(userInput.substr(begin, userInput.size() - begin));

    // Builds the tree of Inputs
    makeTree(inputs, connectors, commands);
}

void makeTree(vector<Input*>& inputs, vector<char>& connectors, 
                vector<string>& commands) {
    // checks to see if there are any empty commands
    for(int i = 0; i < commands.size(); i++) {
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
        inputs.push_back(in);
        return;
    }
    
    // start of recursive calls
    inputs.push_back(makeTree_(connectors, commands));
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
        Input* con = new SemiColon();
        con->right = new Command(commands.back())
        commands.pop_back();
        con->left = makeTree_(connectors, commands)
        return con;
    }

    if (connectors.back() == '&') {
        connectors.pop_back();
        Input* con = new AND();
        con->right = new Command(commands.back())
        commands.pop_back();
        con->left = makeTree_(connectors, commands)
        return con;
    }

    if (connectors.back() == '|') {
        connectors.pop_back();
        Input* con = new OR();
        con->right = new Command(commands.back())
        commands.pop_back();
        con->left = makeTree_(connectors, commands)
        return con;
    }

    return 0;
}