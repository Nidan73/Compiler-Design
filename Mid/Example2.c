#include <iostream>
#include <string>

using namespace std;

string input;

// Function to check if the string is a valid identifier
bool isValid(string str, int n) {
    if (!((str[0] >= 'a' && str[0] <= 'z') ||
          (str[0] >= 'A' && str[0] <= 'Z') ||
          str[0] == '_'))
        return false;

    for (int i = 1; i < n; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') ||
              str[i] == '_'))
            return false;
    }

    return true;
}

// Function to check if the string is a single-line comment
bool isSingleLineComment(string str) {
    return (str.length() >= 2 && str[0] == '/' && str[1] == '/');
}

// Function to check if the string is a multi-line comment
bool isMultiLineComment(string str) {
    return (str.length() >= 4 && str.substr(0, 2) == "/*" && str.substr(str.length() - 2) == "*/");
}

int main() {
    cout << "Enter a string: ";
    getline(cin, input); // Use getline to allow spaces and newlines in input

    if (isSingleLineComment(input)) {
        cout << "\"" << input << "\" is a single-line comment." << endl;
    } else if (isMultiLineComment(input)) {
        cout << "\"" << input << "\" is a multi-line comment." << endl;
    } else {
        int n = input.length();
        if (isValid(input, n)) {
            cout << "\"" << input << "\" is a valid identifier." << endl;
        } else {
            cout << "\"" << input << "\" is not a valid identifier." << endl;
        }
    }

    return 0;
}
