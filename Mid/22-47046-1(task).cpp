#include <bits/stdc++.h>
using namespace std;

int main(){

    string myText;
    string code = "int num1 , num2 ;\n int sum = num1 - num2 ; \n cout << sum ;";
    ofstream MyFile;
    ifstream MyReadFile("C://Study Matirial//9th sem//Compiler//Lab//Task//sourcecode.txt");

    set<string> keywords = {"int", "float", "double", "char", "void", "if", "else", "for", "while", "return", "cout", "cin", "include", "bits/stdc++.h", "endl", "namespace", "using", "std"};
    set<string> operators = {"=", "+", "-", "*", "/", "++", "--", "==", "!=", "<", ">", "<=", ">=", "<<", ">>"};
    set<char> punctuation = {',', ';', '(', ')', '{', '}', '[', ']', ' '};

    set<string> identifiers;
    set<string> foundOperators;
    set<string> foundKeywords;
    set<char> foundPunctuation;

    while (getline (MyReadFile, myText))    {
        stringstream ss(myText);
        string token;
        while ( ss >> token ){
            if (keywords.count(token)) {
                foundKeywords.insert(token);
            } else if (operators.count(token)) {
                foundOperators.insert(token);
            } else if ( (token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z')
                    || token[0] == '_' ) {
                    identifiers.insert(token);
            }

            for (char ch : token) {
                if (punctuation.count(ch)) {
                    foundPunctuation.insert(ch);
                }
            }

        }
    }


    cout << "identifier: ";
    for ( auto &id : identifiers) {
        cout << id << " ";
    } cout << endl;

    cout << "operator: ";
    for ( auto &op : foundOperators) {
        cout << op << " ";
    } cout << endl;

    cout << "keyword: ";
    for ( auto &kw : foundKeywords) {
        cout << kw << " ";
    } cout << endl;

    cout << "punctuation: ";
    for ( auto &punc : foundPunctuation) {
        cout << punc << " ";
    } cout << endl;


}
