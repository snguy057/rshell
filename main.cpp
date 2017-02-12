#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>

using namespace std;

int main () {
    // Display command line and read input
    string userInput = "";
    vector<char*> inputs; 

    cout << "$ ";
    getline(cin, userInput);

    // Converts input from string to cstring
    char userCstr[userInput.size() + 1];
    strcpy(userCstr, userInput.c_str());

    printf("%s\n", userCstr);
    
    // char* token = strtok(userCstr, "|| && ;");

    return 0;
}