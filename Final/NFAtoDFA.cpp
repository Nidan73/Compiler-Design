#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

const int MAX_STATES = 8;

// Map to hold NFA transitions including epsilon transitions
map<int, map<char, set<int>>> nfa;

// Function to compute epsilon closure using BFS
set<int> epsilonClosure(const set<int>& startStates) {
    queue<int> q;
    set<int> closure = startStates;

    for (int s : startStates) {
        q.push(s);
    }

    while (!q.empty()) {
        int state = q.front();
        q.pop();
        // Process epsilon transitions
        if (nfa[state].find('e') != nfa[state].end()) {
            for (int next : nfa[state]['e']) {
                if (closure.find(next) == closure.end()) {
                    closure.insert(next);
                    q.push(next);
                }
            }
        }
    }
    return closure;
}

// Function to perform transitions and return closure of the set
set<int> move(const set<int>& states, char symbol) {
    set<int> result;
    for (int state : states) {
        if (nfa[state].find(symbol) != nfa[state].end()) {
            set<int> nextStates = nfa[state][symbol];
            result.insert(nextStates.begin(), nextStates.end());
        }
    }
    return epsilonClosure(result);
}

// Helper function to print sets in a formatted manner
string printSet(const set<int>& s) {
    string result = "{ ";
    for (int state : s) {
        result += "q[" + to_string(state) + "] ";
    }
    result += "}";
    return result;
}

int main() {
    // Populate NFA transitions based on your NFA table
    nfa[0]['e'] = {7, 1};
    nfa[1]['e'] = {2, 4};
    nfa[2]['a'] = {3};
    nfa[3]['e'] = {6};
    nfa[4]['b'] = {5};
    nfa[5]['e'] = {6};
    nfa[6]['e'] = {7, 1};

    // Compute DFA from NFA
    set<int> startState = epsilonClosure({0}); // Begin with epsilon closure of the NFA start state

    cout << "DFA States and Transitions:" << endl;
    cout << "State                         | 'a' transitions           | 'b' transitions" << endl;
    map<set<int>, map<char, set<int>>> dfa;
    queue<set<int>> toProcess;
    toProcess.push(startState);
    map<set<int>, bool> processed;

    while (!toProcess.empty()) {
        set<int> currentState = toProcess.front();
        toProcess.pop();

        if (processed[currentState]) {
            continue;
        }

        // Compute transitions for 'a' and 'b' and their closures
        set<int> onA = move(currentState, 'a');
        set<int> onB = move(currentState, 'b');

        dfa[currentState]['a'] = onA;
        dfa[currentState]['b'] = onB;

        // Queue new states for processing
        if (!onA.empty() && !processed[onA]) toProcess.push(onA);
        if (!onB.empty() && !processed[onB]) toProcess.push(onB);

        processed[currentState] = true;

        // Print each state and its transitions
        cout << printSet(currentState) << " | " << printSet(onA) << " | " << printSet(onB) << endl;
    }

    return 0;
}

