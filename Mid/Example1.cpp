#include <iostream>
#include<string>

using namespace std;

string input;

bool isValid(string str, int n )
{


    if (!((str[0] >= 'a' && str[0] <= 'z')
          || (str[0] >= 'A' && str[0] <= 'Z') || str[0] =='_'))
        return false;
//this code

     for (int i = 1; i < n ; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z')
              || (str[i] >= 'A' && str[i] <= 'Z')
              || (str[i] >= '0' && str[i] <= '9')|| str[i] == '_' ))
            return false;
    }

    return true;
}

int main() {
    cout << "Enter a string to check if it's a valid identifier: ";
    cin >> input;
    int n = input.length();

    if (isValid(input, n)) {
        cout << "\"" << input << "\" is a valid identifier." << endl;
    } else {
        cout << "\"" << input << "\" is not a valid identifier." << endl;
    }

    return 0;
}
