#include <bits/stdc++.h>
using namespace std;

int main(){

    string myText;
    ofstream MyFile;
    ifstream MyReadFile("C://Study Matirial//9th sem//Compiler//Lab//Task//semicolne.txt");

    int cnt = 0;
    while (getline (MyReadFile, myText)) {
        cnt++;
        if ( myText.find( ')' ) != string::npos || myText.find( '}' ) != string::npos ) continue;
        if ( myText[myText.size()-1] != ';' ){
            cout << "Error! expected ; at the end of the line no: " << cnt << endl;
        }
    }

}
