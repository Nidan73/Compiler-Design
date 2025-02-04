#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {

    string code;
    getline ( cin , code);
    int sz = code.size();

    if (code[0]=='/' && code[1]=='/')
        {
            cout<< "this is single line comment";
         }
    else if (code[0]=='/' && code[1]=='*' && code[sz-1]=='/'&& code[sz-2]=='*')
        {
            cout<< "this is multiline comment";
         }

   else
        {
            cout<< "this is no comment";
         }
    return 0;
}
//its a good day /* its a very good day and we are very tired at the end of the day */
