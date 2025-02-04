#include <iostream>
#include <string>

using namespace std;

// Function to check if the text matches the pattern (ab|c)*
bool matchesABorCStar(const string& text) {
	int i = 0;
	int n = text.length();

	while (i < n) {
		if (i + 1 < n && text[i] == 'a' && text[i + 1] == 'b') {
			i += 2; // Skip the next character as well because "ab" is two characters
		} else if (text[i] == 'c') {
			i += 1;
		} else {
			return false; // If it's neither "ab" nor "c", it doesn't match
		}
	}

	return true; // If all sequences in the text are valid, it matches
}

// Function to check if the text is exactly "a" or "b"
bool matchesAorB(const string& text) {
	return text == "a" || text == "b";
}

int main() {
	string text;
	string pattern;
	char ans;

	do {
		cout << "\nChoose the pattern to check:\n";
		cout << "1: (ab|c)*\n";
		cout << "2: a|b\n";
		cout << "Enter your choice (1 or 2): ";
		getline(cin, pattern);

		cout << "\nEnter the text: ";
		getline(cin, text);

		if (pattern == "1") {
			// Check against pattern (ab|c)*
			if (matchesABorCStar(text)) {
				cout << "\nThe Text Matches the Pattern (ab|c)*\n";
			} else {
				cout << "\nThe Text Doesn't Match the Pattern (ab|c)*\n";
			}
		} else if (pattern == "2") {
			// Check against pattern a|b
			if (matchesAorB(text)) {
				cout << "The Text Matches the Pattern a|b\n";
			} else {
				cout << "The Text Doesn't Match the Pattern a|b\n";
			}
		} else {
			cout << "\nInvalid pattern choice.\n";
		}

		cout << "\nDo you want to continue? (Y/N) ";
		cin >> ans;
		cin.ignore(); // Clear newline character left in the input buffer
	} while (ans == 'Y' || ans == 'y');

	return 0;
}
