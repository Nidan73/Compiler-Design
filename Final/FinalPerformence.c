#include <iostream>
#include <cstring>

using namespace std;

// Maximum number of states and maximum length of the regular expression
const int MAX_STATES = 100;
const int MAX_REGEX_LENGTH = 50;

// transitions[i][0] will hold the next state(s) on input '0'
// transitions[i][1] will hold the next state(s) on input '1'
// transitions[i][2] will hold the next state(s) on epsilon 'e'
int transitions[MAX_STATES][3];
char regexExp[MAX_REGEX_LENGTH];
int currentState = 1;  // We'll start labeling states from 1
bool isValid = true;

// Initialize transitions to 0
void initializeTransitions() {
    for(int i = 0; i < MAX_STATES; i++) {
        for(int j = 0; j < 3; j++) {
            transitions[i][j] = 0;
        }
    }
}

// Validate that the regex only contains characters we expect: 0,1,e,|,*,(,)
bool validateRegex(const char* input) {
    int len = strlen(input);
    if(len >= MAX_REGEX_LENGTH - 1) {
        cout << "Error: Regular expression too long\n";
        return false;
    }
    for(int i = 0; i < len; i++) {
        if(input[i] != '0' && input[i] != '1' && input[i] != 'e' &&
           input[i] != '|' && input[i] != '*' &&
           input[i] != '(' && input[i] != ')')
        {
            cout << "Error: Invalid character '" << input[i]
                 << "' in regular expression\n";
            return false;
        }
    }
    return true;
}

// Check if we have enough room for 'requiredStates' more states
bool checkStateLimit(int requiredStates) {
    if(currentState + requiredStates >= MAX_STATES) {
        cout << "Error: NFA would exceed maximum state limit\n";
        return false;
    }
    return true;
}

// Build the NFA from (0|1)*11* in a naive way
void convertRegexToNFA() {
    cout << "Enter regular expression: ";
    cin >> regexExp;  // e.g., (0|1)*11*

    // Validate the input
    if(!validateRegex(regexExp)) {
        isValid = false;
        return;
    }

    cout << "Given regular expression: " << regexExp << endl;

    int i = 0;
    int len = strlen(regexExp);

    // We parse the regex in a naive left-to-right manner
    while(i < len && isValid) {
        // Check if we have enough state space to handle expansions
        if(!checkStateLimit(5)) {
            isValid = false;
            return;
        }

        // Single '0' without '|' or '*'
        if(regexExp[i] == '0' && (i+1 >= len ||
           (regexExp[i+1] != '|' && regexExp[i+1] != '*')))
        {
            transitions[currentState][0] = currentState + 1;
            currentState++;
        }
        // Single '1' without '|' or '*'
        else if(regexExp[i] == '1' && (i+1 >= len ||
                (regexExp[i+1] != '|' && regexExp[i+1] != '*')))
        {
            transitions[currentState][1] = currentState + 1;
            currentState++;
        }
        // (0|1)
        else if(i+2 < len && regexExp[i] == '0' &&
                regexExp[i+1] == '|' && regexExp[i+2] == '1')
        {
            // Union:  epsilon -> (0 branch), (1 branch)
            // We store combined states as a two-digit number
            // (like the original code did for 'a|b')
            transitions[currentState][2] = ((currentState + 1)*10) + (currentState + 3);
            currentState++;

            // '0' transition
            transitions[currentState][0] = currentState + 1;
            currentState++;

            // epsilon -> next final
            transitions[currentState][2] = currentState + 2;
            currentState++;

            // '1' transition
            transitions[currentState][1] = currentState + 1;
            currentState++;

            // final epsilon -> next
            transitions[currentState][2] = currentState + 1;
            currentState++;

            i += 2; // we consumed '0|1'
        }
        // (1|0)
        else if(i+2 < len && regexExp[i] == '1' &&
                regexExp[i+1] == '|' && regexExp[i+2] == '0')
        {
            transitions[currentState][2] = ((currentState + 1)*10) + (currentState + 3);
            currentState++;

            // '1' transition
            transitions[currentState][1] = currentState + 1;
            currentState++;

            // epsilon -> next final
            transitions[currentState][2] = currentState + 2;
            currentState++;

            // '0' transition
            transitions[currentState][0] = currentState + 1;
            currentState++;

            // final epsilon -> next
            transitions[currentState][2] = currentState + 1;
            currentState++;

            i += 2; // consumed '1|0'
        }
        // '0*'
        else if(i+1 < len && regexExp[i] == '0' && regexExp[i+1] == '*') {
            // Epsilon -> (0 branch) -> Epsilon back, typical *
            transitions[currentState][2] = ((currentState + 1)*10) + (currentState + 3);
            currentState++;

            // '0' transition
            transitions[currentState][0] = currentState + 1;
            currentState++;

            // Epsilon to combine
            transitions[currentState][2] = ((currentState + 1)*10) + (currentState - 1);
            currentState++;

            i++; // skip '*'
        }
        // '1*'
        else if(i+1 < len && regexExp[i] == '1' && regexExp[i+1] == '*') {
            transitions[currentState][2] = ((currentState + 1)*10) + (currentState + 3);
            currentState++;

            // '1' transition
            transitions[currentState][1] = currentState + 1;
            currentState++;

            // Epsilon loop
            transitions[currentState][2] = ((currentState + 1)*10) + (currentState - 1);
            currentState++;

            i++; // skip '*'
        }
        // ')*' => means closure on whatever was inside the parentheses
        else if(i+1 < len && regexExp[i] == ')' && regexExp[i+1] == '*') {
            // This is a naive way to loop back to the beginning
            // or link to the next state, similar to the original code logic
            transitions[0][2] = ((currentState + 1)*10) + 1;
            transitions[currentState][2] = ((currentState + 1)*10) + 1;
            currentState++;

            i++; // skip '*'
        }

        i++;
    }
}

// Display the transition table
void displayTransitionTable() {
    if(!isValid) {
        cout << "Cannot display transition table due to previous errors.\n";
        return;
    }

    cout << "\n\tTransition Table \n";
    cout << "_____________________________________\n";
    cout << "Current State |\tInput |\tNext State";
    cout << "\n_____________________________________\n";

    for(int i = 0; i <= currentState; i++) {
        // transitions[i][0] -> '0'
        if(transitions[i][0] != 0) {
            cout << "\n  q[" << i << "]\t      |   0   |  q["
                 << transitions[i][0] << "]";
        }
        // transitions[i][1] -> '1'
        if(transitions[i][1] != 0) {
            cout << "\n  q[" << i << "]\t      |   1   |  q["
                 << transitions[i][1] << "]";
        }
        // transitions[i][2] -> 'e'
        if(transitions[i][2] != 0) {
            // If less than 10, single next state
            if(transitions[i][2] < 10) {
                cout << "\n  q[" << i << "]\t      |   e   |  q["
                     << transitions[i][2] << "]";
            } else {
                // Two-digit: combine => q[x], q[y]
                int firstState  = transitions[i][2] / 10;
                int secondState = transitions[i][2] % 10;
                cout << "\n  q[" << i << "]\t      |   e   |  q["
                     << firstState << "] , q[" << secondState << "]";
            }
        }
    }
    cout << "\n_____________________________________\n";
}

int main() {
    initializeTransitions();
    convertRegexToNFA();
    displayTransitionTable();
    return 0;
}

