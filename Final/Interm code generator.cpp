#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int tmpVarCounter = 1; // Counter for temporary variables

// Function to generate a temporary variable name
string generateTempVar() {
    return "T" + to_string(tmpVarCounter++);
}

// Function to generate intermediate code for the given expression
void generateIntermediateCode(string expression) {
    string result;
    size_t pos;

    // Process *, / operators first (higher precedence)
    while ((pos = expression.find_first_of("*/")) != string::npos) {
        // Find the operator and operands
        char op = expression[pos];

        // Find the left operand
        size_t leftEnd = pos - 1;
        while (leftEnd > 0 && isalnum(expression[leftEnd])) {
            leftEnd--;
        }
        if (!isalnum(expression[leftEnd])) {
            leftEnd++;
        }
        string leftOperand = expression.substr(leftEnd, pos - leftEnd);

        // Find the right operand
        size_t rightStart = pos + 1;
        while (rightStart < expression.size() && isalnum(expression[rightStart])) {
            rightStart++;
        }
        string rightOperand = expression.substr(pos + 1, rightStart - (pos + 1));

        // Generate temporary variable
        string tempVar = generateTempVar();
        cout << tempVar << " = " << leftOperand << " " << op << " " << rightOperand << endl;

        // Replace the operation with the temporary variable
        expression.replace(leftEnd, rightStart - leftEnd, tempVar);
    }

    // Process +, - operators (lower precedence)
    while ((pos = expression.find_first_of("+-")) != string::npos) {
        // Find the operator and operands
        char op = expression[pos];

        // Find the left operand
        size_t leftEnd = pos - 1;
        while (leftEnd > 0 && isalnum(expression[leftEnd])) {
            leftEnd--;
        }
        if (!isalnum(expression[leftEnd])) {
            leftEnd++;
        }
        string leftOperand = expression.substr(leftEnd, pos - leftEnd);

        // Find the right operand
        size_t rightStart = pos + 1;
        while (rightStart < expression.size() && isalnum(expression[rightStart])) {
            rightStart++;
        }
        string rightOperand = expression.substr(pos + 1, rightStart - (pos + 1));

        // Generate temporary variable
        string tempVar = generateTempVar();
        cout << tempVar << " = " << leftOperand << " " << op << " " << rightOperand << endl;

        // Replace the operation with the temporary variable
        expression.replace(leftEnd, rightStart - leftEnd, tempVar);
    }

    // Final result
    cout << "w = " << expression << endl;
}

int main() {
    string expression;

    cout << "Enter the expression : ";
    cin >> expression;

    // Remove the 'w=' part for intermediate processing
    size_t equalPos = expression.find('=');
    if (equalPos != string::npos) {
        expression = expression.substr(equalPos + 1);
    }

    cout << "\nIntermediate Code:\n";
    generateIntermediateCode(expression);

    return 0;
}
