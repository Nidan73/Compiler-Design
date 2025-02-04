#include <iostream>
#include <cstring>

using namespace std;

class NFAConverter {
private:
    static const int MAX_STATES = 100;  // Increased from 20 to 100
    static const int MAX_REGEX_LENGTH = 50;  // Added maximum regex length
    int transitions[MAX_STATES][3];
    char regex[MAX_REGEX_LENGTH];
    int currentState;
    bool isValid;

    void initializeTransitions() {
        for(int i = 0; i < MAX_STATES; i++) {
            for(int j = 0; j < 3; j++) {
                transitions[i][j] = 0;
            }
        }
    }

    bool validateRegex(const char* input) {
        int len = strlen(input);
        if(len >= MAX_REGEX_LENGTH - 1) {
            cout << "Error: Regular expression too long\n";
            return false;
        }

        for(int i = 0; i < len; i++) {
            if(input[i] != 'a' && input[i] != 'b' && input[i] != 'e' &&
               input[i] != '|' && input[i] != '*' && input[i] != '(' && input[i] != ')') {
                cout << "Error: Invalid character '" << input[i] << "' in regular expression\n";
                return false;
            }
        }
        return true;
    }

    bool checkStateLimit(int requiredStates) {
        if(currentState + requiredStates >= MAX_STATES) {
            cout << "Error: NFA would exceed maximum state limit\n";
            return false;
        }
        return true;
    }

public:
    NFAConverter() : currentState(1), isValid(true) {
        initializeTransitions();
    }

    void convertRegexToNFA() {
        cout << "Enter regular expression: ";
        cin >> regex;

        if(!validateRegex(regex)) {
            isValid = false;
            return;
        }

        cout << "Given regular expression: " << regex << endl;

        int i = 0;
        int len = strlen(regex);

        while(i < len && isValid) {
            // Check state limit before each operation
            if(!checkStateLimit(5)) {  // 5 is the maximum states needed for any single operation
                isValid = false;
                return;
            }

            if(regex[i] == 'a' && (i + 1 >= len || (regex[i+1] != '|' && regex[i+1] != '*'))) {
                transitions[currentState][0] = currentState + 1;
                currentState++;
            }
            else if(regex[i] == 'b' && (i + 1 >= len || (regex[i+1] != '|' && regex[i+1] != '*'))) {
                transitions[currentState][1] = currentState + 1;
                currentState++;
            }
            else if(regex[i] == 'e' && (i + 1 >= len || (regex[i+1] != '|' && regex[i+1] != '*'))) {
                transitions[currentState][2] = currentState + 1;
                currentState++;
            }
            else if(i + 2 < len && regex[i] == 'a' && regex[i+1] == '|' && regex[i+2] == 'b') {
                transitions[currentState][2] = ((currentState + 1) * 10) + (currentState + 3);
                currentState++;
                transitions[currentState][0] = currentState + 1;
                currentState++;
                transitions[currentState][2] = currentState + 3;
                currentState++;
                transitions[currentState][1] = currentState + 1;
                currentState++;
                transitions[currentState][2] = currentState + 1;
                currentState++;
                i += 2;
            }
            else if(i + 2 < len && regex[i] == 'b' && regex[i+1] == '|' && regex[i+2] == 'a') {
                transitions[currentState][2] = ((currentState + 1) * 10) + (currentState + 3);
                currentState++;
                transitions[currentState][1] = currentState + 1;
                currentState++;
                transitions[currentState][2] = currentState + 3;
                currentState++;
                transitions[currentState][0] = currentState + 1;
                currentState++;
                transitions[currentState][2] = currentState + 1;
                currentState++;
                i += 2;
            }
            else if(i + 1 < len && regex[i] == 'a' && regex[i+1] == '*') {
                transitions[currentState][2] = ((currentState + 1) * 10) + (currentState + 3);
                currentState++;
                transitions[currentState][0] = currentState + 1;
                currentState++;
                transitions[currentState][2] = ((currentState + 1) * 10) + (currentState - 1);
                currentState++;
                i++;
            }
            else if(i + 1 < len && regex[i] == 'b' && regex[i+1] == '*') {
                transitions[currentState][2] = ((currentState + 1) * 10) + (currentState + 3);
                currentState++;
                transitions[currentState][1] = currentState + 1;
                currentState++;
                transitions[currentState][2] = ((currentState + 1) * 10) + (currentState - 1);
                currentState++;
                i++;
            }
            else if(i + 1 < len && regex[i] == ')' && regex[i+1] == '*') {
                transitions[0][2] = ((currentState + 1) * 10) + 1;
                transitions[currentState][2] = ((currentState + 1) * 10) + 1;
                currentState++;
                i++;
            }
            i++;
        }
    }

    void displayTransitionTable() const {
        if(!isValid) {
            cout << "Cannot display transition table due to previous errors.\n";
            return;
        }

        cout << "\n\tTransition Table \n";
        cout << "_____________________________________\n";
        cout << "Current State |\tInput |\tNext State";
        cout << "\n_____________________________________\n";

        for(int i = 0; i <= currentState; i++) {
            if(transitions[i][0] != 0)
                cout << "\n  q[" << i << "]\t      |   a   |  q[" << transitions[i][0] << "]";
            if(transitions[i][1] != 0)
                cout << "\n  q[" << i << "]\t      |   b   |  q[" << transitions[i][1] << "]";
            if(transitions[i][2] != 0) {
                if(transitions[i][2] < 10)
                    cout << "\n  q[" << i << "]\t      |   e   |  q[" << transitions[i][2] << "]";
                else
                    cout << "\n  q[" << i << "]\t      |   e   |  q[" << transitions[i][2]/10
                         << "] , q[" << transitions[i][2]%10 << "]";
            }
        }
        cout << "\n_____________________________________\n";

    }
};

int main() {
    NFAConverter nfa;
    nfa.convertRegexToNFA();
    nfa.displayTransitionTable();
    return 0;
}
