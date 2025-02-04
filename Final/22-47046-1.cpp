#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

// Function to trim whitespace from both ends of a string
string trim(const string& str) {
    int start = 0;
    int finish = str.length() - 1;

    while (start <= finish && (str[start] == ' ' || str[start] == '\t')) {
        ++start;
    }

    while (finish >= start && (str[finish] == ' ' || str[finish] == '\t')) {
        --finish;
    }

    return str.substr(start, finish - start + 1);
}

// Check if a given identifier start is valid
bool isValidIdentifierStart(char c) {
    return isalpha(c) || c == '_';
}

// Check if the expression after "return" is valid
bool isValidReturnExpression(const string& expr) {
    if (expr.empty()) return false;

    string trimmedExpr = trim(expr);
    if (trimmedExpr.empty() || trimmedExpr == "-" || trimmedExpr == "+") {
        return false;
    }

    for (char c : trimmedExpr) {
        if (!isalnum(c) && c != '_' && c != '+' && c != '-' && c != '*' && c != '/' && c != ' ') {
            return false;
        }
    }
    return true;
}

// Parse and validate C++ code
int main() {
    ifstream file("C://Study Matirial//9th sem//Compiler//Lab//Task//sourcecode.txt");
    string line;
    stack<char> brackets;
    bool syntaxCorrect = true;
    int lineCount = 0;

    while (getline(file, line)) {
        lineCount++;
        string trimmedLine = trim(line);

        // Check for valid identifier in declarations or definitions
        if (trimmedLine.find("int ") == 0 || trimmedLine.find("float ") == 0 || trimmedLine.find("double ") == 0) {
            size_t pos = trimmedLine.find(' ');
            if (pos != string::npos && !isValidIdentifierStart(trimmedLine[pos + 1])) {
                cout << "Error! Invalid identifier at line: " << lineCount << endl;
                syntaxCorrect = false;
            }
        }

        // Check brackets and other characters
        for (char c : trimmedLine) {
            switch (c) {
                case '(': case '[': case '{': brackets.push(c); break;
                case ')': case ']': case '}':
                    if (brackets.empty() || (brackets.top() == '(' && c != ')') ||
                        (brackets.top() == '[' && c != ']') || (brackets.top() == '{' && c != '}')) {
                        cout << "Error! Unmatched '" << c << "' at line: " << lineCount << endl;
                        syntaxCorrect = false;
                    } else {
                        brackets.pop();
                    }
                    break;
            }
        }

        // Check for valid return statement if "return" keyword is found
        size_t returnPos = trimmedLine.find("return");
        if (returnPos != string::npos) {
            size_t semicolonPos = trimmedLine.find(';', returnPos);
            string returnExpr = trimmedLine.substr(returnPos + 6, semicolonPos - (returnPos + 6));
            if (semicolonPos == string::npos || !isValidReturnExpression(returnExpr)) {
                cout << "Invalid return statement at line: " << lineCount << endl;
                syntaxCorrect = false;
            }
        }

        // Ensure lines that aren't block closures or return statements end with a semicolon
        if (!trimmedLine.empty() && trimmedLine.back() != ';' && trimmedLine.back() != '{' && trimmedLine.back() != '}' &&
            trimmedLine.find("return") == string::npos) {
            cout << "Error! Expected ';' at the end of line: " << lineCount << endl;
            syntaxCorrect = false;
        }
    }

    if (!brackets.empty()) {
        cout << "Error! Unmatched brackets in the code." << endl;
        syntaxCorrect = false;
    }

    if (syntaxCorrect) {
        cout << "Syntax appears to be correct." << endl;
    } else {
        cout << "Syntax errors detected." << endl;
    }

    return 0;
}
