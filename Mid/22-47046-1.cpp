#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace std;

bool contains(const string& line, const string& pattern) {
    size_t lineLength = line.length();
    size_t patternLength = pattern.length();

    if (patternLength > lineLength) return false;
    for (size_t i = 0; i <= lineLength - patternLength; i++) {
        bool match = true;
        for (size_t j = 0; j < patternLength; j++) {
            if (line[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isOperator(const string& line) {
    for (char c : line) {
        if (c == '+' || c == '-' || c == '*' || c == '=') {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream programFile("C://Study Matirial//9th sem//Compiler//Lab//program.cpp");
    string line;

    set<string> functions;
    set<string> operators;

    if (programFile.is_open()) {
        while (getline(programFile, line)) {

            size_t intPos = line.find("int ");
            if (intPos != string::npos) {
                size_t start = intPos + 4;
                size_t end = line.find("(", start);
                if (end != string::npos) {
                    size_t nameStart = start;
                    while (nameStart < end && line[nameStart] == ' ') {
                        ++nameStart;
                    }
                    size_t nameEnd = nameStart;
                    while (nameEnd < end && isAlpha(line[nameEnd])) {
                        ++nameEnd;
                    }
                    string functionName = line.substr(nameStart, nameEnd - nameStart);
                    if (functionName != "main") {
                        functions.insert(functionName);
                    }
                }
            }

            if (isOperator(line)) {
                if (contains(line, "+")) {
                    operators.insert("addition");
                }
                if (contains(line, "-")) {
                    operators.insert("subtraction");
                }
                if (contains(line, "*")) {
                    operators.insert("multiplication");
                }
                if (contains(line, "=")) {
                    operators.insert("assignment");
                }
            }
        }
        programFile.close();
    } else {
        cout << "Unable to open file" << endl;
        return 1;
    }

    int count = 1;
    for (const string& func : functions) {
        cout << "Function-" << count++ << ": " << func << endl;
    }
    cout << "Total number of the user defined function: " << functions.size() << endl;

    count = 1;
    for (const string& op : operators) {
        cout << "Operator-" << count++ << ": " << op << endl;
    }
    cout << "Total number of the operators: " << operators.size() << endl;

    return 0;
}
