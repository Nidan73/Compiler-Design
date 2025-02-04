#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    // Create and open a text file
    ofstream MyFile;
    MyFile.open("NewFile.txt");

    // Write to the file
    MyFile << "this is a file containing information of students : ";

    // Close the file
    MyFile.close();

    string myText;

    // Read from the text file
    //ifstream MyReadFile("C://Users//Teacher//Desktop//Fall-24-25//Compiler Design//New folder//LAB//Lab 1//Lab-1 Codes//student.txt");
    ifstream MyReadFile("C://Study Matirial//9th sem//Compiler//Lab//Task//info.txt");
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText))
    {
        // Output the text from the file

        cout << myText<<endl;

    }

    // Close the file
    MyReadFile.close();


}
