#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    // Create and open a text file
    ofstream MyFile;
    MyFile.open("NewFile.txt");

    // Write to the file
    MyFile << "this is a file containing information of students : "<<endl;
    MyFile << "Name            Dept      CGPA    "<<endl;
    MyFile << "Nipa Nasrin     CSE       3.78    "<<endl;
    MyFile << "Karim Hossain   BBA       3.56    "<<endl;
    MyFile << "Shaheen Shah    CSE       3.98    "<<endl;


    // Close the file

    MyFile.close();

    string line;
    ifstream ReadFile("NewFile.txt");

    if (!ReadFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    // Read and display each line
    while (getline(ReadFile, line)) {
        cout << line << endl;
    }

    // Close the read file
    ReadFile.close();

    return 0;
}
