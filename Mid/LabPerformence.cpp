#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace std;

int main() {
    // File to be read
    ifstream programFile("program.cpp");
    string line;

    // Sets to store unique operators and preprocessors
    set<string> operators;
    set<string> preprocessors;

    // Common C++ operators to check in lines
    string opSymbols[] = {"+", "-", "*", "="};

    if (programFile.is_open()) {
        while (getline(programFile, line)) {
            // Check for preprocessors
            if (line.find("#include") != string::npos) {
                preprocessors.insert("include");
            } else if (line.find("#define") != string::npos) {
                preprocessors.insert("define");
            }

            // Check for operators
            for (const string& symbol : opSymbols) {
                if (line.find(symbol) != string::npos) {
                    if (symbol == "+") {
                        operators.insert("addition");
                    } else if (symbol == "-") {
                        operators.insert("subtraction");
                    } else if (symbol == "*") {
                        operators.insert("multiplication");
                    } else if (symbol == "=") {
                        operators.insert("assignment");
                    }
                }
            }
        }
        programFile.close();
    } else {
        cout << "Unable to open file";
        return 1;
    }

    // Print operators
    int count = 1;
    for (const string& op : operators) {
        cout << "Operator-" << count++ << ": " << op << endl;
    }
    cout << "Total number of the Operator: " << operators.size() << endl;

    // Print preprocessors
    count = 1;
    for (const string& pre : preprocessors) {
        cout << "Preprocessor-" << count++ << ": " << pre << endl;
    }
    cout << "Total number of preprocessor: " << preprocessors.size() << endl;

    return 0;
}

