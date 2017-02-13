#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

void parse(string& userInput, vector<char*>& inputs) {
    bool commentFound = 0;
    bool openingQuote = 0;
    bool closingQuote = 0;
    bool semicolon = 0;
    bool AND = 0;
    bool OR = 0;

    // Iterator for parsing
    int it = 0;
    // index on string we are beginning at
    int begin = 0;
    
    // ignore any leading whitespace
    while (userInput.at(it) == ' ' && it < userInput.size()) {
        it++;
    }

    // seraches for comments and resizes the string to all 
    // whitespace and comments
    for (int i = it; i < userInput.size() && !commentFound; i++) {
        if (userInput.at(i) == '#') {
            userInput = userInput.substr(it, i - it);
            commentFound = 1;
        }
    }

    for (it = 0; it < userInput.size(); it++) {
        // checks for opening and closing quotes for unwanted connectors
        if (userInput.at(it) == '\"' || userInput.at(it) == '\'') {
            openingQuote = 1;
            it++;
            while (closingQuote == 0 && it < userInput.size()) {
                if (userInput.at(it) == '\"' || userInput.at(it) == '\'') {
                    closingQuote = 1;
                }
            }
            if (closingQuote == 0) {
                // throw "Error no closing quote found";
            }
        }

        else if (userInput.at(it) == ';') {
            char temp[it - begin + 1];
            string temp2 = userInput.substr(begin, it - begin);
            strcpy(temp, temp2.c_str());
            // printf("%s\n", temp);
            inputs.push_back(temp);
        }

    }
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

int main () {
    // Display command line and read input
    string userInput = "";
    vector<char*> inputs; 

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
    // try {
        parse(userInput, inputs);
    // }
    // catch() {

    // }
    return 0;
}