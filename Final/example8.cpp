#include <bits/stdc++.h>
using namespace std;

int main(){

    string myText;
    ofstream MyFile;
    ifstream MyReadFile("C://Study Matirial//9th sem//Compiler//Lab//Task//semicolne.txt");

    int cnt = 0;
    bool isdefined = 1;
    stack<char> st;
    stack<char> st1;
    stack<char> st2;
    int bracketError = 0;
    int bracketErrortype = 0;

    while (getline (MyReadFile, myText)) {
        cnt++;
        if ( isdefined )
            for ( auto c : myText ){
                if ( c == '(' ) st.push('(');
                else if ( c == ')' ){
                    if ( st.empty() ){
                        bracketError = cnt;
                        bracketErrortype = 1;
                        isdefined = 0;
                        break;
                    }
                    st.pop();
                }
                if ( c == '{' ) st1.push('{');
                else if ( c == '}' ){
                    if ( st1.empty() ){
                        bracketError = cnt;
                        bracketErrortype = 2;
                        isdefined = 0;
                        break;
                    }
                    st1.pop();
                }
                if ( c == '[' ) st2.push('[');
                else if ( c == ']' ){
                    if ( st2.empty() ){
                        isdefined = 0;
                        bracketError = cnt;
                        bracketErrortype = 3;
                        break;
                    }
                    st2.pop();
                }
            }

        if ( myText.find( ')' ) != string::npos || myText.find( '}' ) != string::npos ) continue;
        if ( myText[myText.size()-1] != ';' ){
            cout << "Error! expected ; at the end of the line no: " << cnt << endl;
        }

    }

    if ( !st.empty() || !st1.empty() || !st2.empty() ) isdefined = 0, bracketError = cnt, bracketErrortype = 2;
    if ( !isdefined ){
        if ( bracketErrortype == 1 ) cout << "Error! () bracket missmatch at line: " << bracketError << endl;
        if ( bracketErrortype == 2 ) cout << "Error! {} bracket missmatch at line: " << bracketError << endl;
        if ( bracketErrortype == 3 ) cout << "Error! [] bracket missmatch at line: " << bracketError << endl;
    }


}
