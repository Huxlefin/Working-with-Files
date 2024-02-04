/* 
Hubert Pilichowski's Project 5
COP 3363
Using the input of a file, print out statistics about the file
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// declaring functions
void readFile(string inputFile, string outputFile);
string checkLegit(string file);
void fileStats (int totalLet, int upper, int lower, int white, int otherChar, int digits,
 int totalChar, char letters[], int lettercount[], string file, string outputFile);

// main function
int main()
{
    string inputFile;
    string outputFile;

    cout << "Please enter the name of the input file.\n";
    cout << "Filename:  ";
    cin >> inputFile;

    inputFile = checkLegit(inputFile);

    cout << "Please enter the name of the output file.\n";
    cout << "Filename:  ";
    cin >> outputFile;

    // check to see if the file exists in the directory
    outputFile = checkLegit(outputFile);

    cout << "\nProcessing complete";

    // call the read file function
    readFile(inputFile, outputFile);

}

// the fucntion that checks whether the file exits in the current directory
string checkLegit(string file)
{
    ifstream in1;
    in1.clear();
    in1.open(file);

    while (!in1)
    {
        cout << "This file does not exist in the current directory. Please input a valid file name: ";
        cin >> file;
        in1.clear();
        in1.open(file);
    }

    return file;
}

// this function reads the file and sends all the information to the filestats function
void readFile(string inputFile, string outputFile)
{

    ifstream in1;
    in1.clear();
    in1.open(inputFile);

    char textChar;

    // letter array and array for counting the number of each letter
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
     'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int letterCounter[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0};

    // all variables for statistics
    int isUpper = 0;
    int isLower = 0;
    int totalLetters = 0;
    int whiteSpace = 0;
    int digits = 0;
    int otherChar = 0;
    int totalChar = 0;
    
    while (!in1.eof())
    {
        in1.get(textChar);
        totalChar += 1;

        // uppercase and lowercase letters
        if (isupper(textChar))
            isUpper++;
        else if (islower(textChar))
            isLower++;

        // white spaces
        if (isspace(textChar))
            whiteSpace++;

        // finds all the numbers
        if (isdigit(textChar))
            digits++;
        
        // check other characters
        if (!isalpha(textChar) && !isdigit(textChar) && !isspace(textChar))
            otherChar++;

        for (int i = 0; i <= 25; i++)
        {
            textChar = tolower(textChar);
            if (textChar == letters[i])
            {
                letterCounter[i] += 1;
            }
        }

    }
    totalLetters = isUpper + isLower;

    fileStats(totalLetters, isUpper, isLower, whiteSpace, otherChar, digits, totalChar, letters, letterCounter, inputFile,  out);

}


// this function calculates and sends all of the information about the file into the output file given by the user
void fileStats(int totalLet, int upper, int lower, int white, int otherChar, int digits,
 int totalChar, char letters[], int lettercount[], string file, string outputFile)
{
    ofstream out;
    out.open(outputFile);

    // change all values into floats so can do calculations with them
    float totalLetf = totalLet;
    float upperf = upper;
    float lowerf = lower;
    float whitef = white;
    float otherCharf = otherChar;
    float digitsf = digits;
    float totalCharf = totalChar;

    // calculations about the letters
    out.setf(ios::fixed);
    out.setf(ios::showpoint);
    out.precision(2);

    float letterPer = (totalLetf/totalCharf) * 100;
    float whitePer = (whitef/totalCharf) * 100;
    float digitPer = (digitsf/totalCharf) * 100;
    float otherCharPer = (otherCharf/totalCharf) * 100;
    float upperPer = (upperf/totalLetf) * 100;
    float lowerPer = (lowerf/totalLetf) * 100;

    // Output into file
    out << "Statistics for file: " << file << "\n";
    out << "-------------------------------------------------\n\n";
    out << "Total # of characters in file:\t" << totalChar << "\n\n";
    out << "Category                How many in file           \% of file\n";
    out << "----------------------------------------------------------------------\n";
    out << "Letters";
    out.width(33);
    out << totalLet;
    out.width(20);
    out << letterPer << " \%" << "\n";
    out << "White Space";
    out.width(29);
    out << white;
    out.width(20);
    out << whitePer << " \%" << "\n";
    out << "Digits";
    out.width(34);
    out << digits;
    out.width(20);
    out << digitPer << " \%" << "\n";
    out << "Other characters";
    out.width(24);
    out << otherChar;
    out.width(20);
    out << otherCharPer << " \%" << "\n\n\n";

    // Letter Statistics Output
    out << "LETTER STATISTICS\n\n";
    out << "Category                How many in file    \% of all letters\n";
    out << "----------------------------------------------------------------------\n";
    out << "Uppercase";
    out.width(31);
    out << upper;
    out.width(20);
    out << upperPer << " \%" << "\n";
    out << "Lowercase";
    out.width(31);
    out << lower;
    out.width(20);
    out << lowerPer << " \%" << "\n";

    // for each individual letter
    for (int i=0; i <= 25; i++)
    {
        out << letters[i];
        out.width(39);
        out << lettercount[i];
        out.width(20);

        // percent calculations for each individual letter
        float iFloat = lettercount[i];
        out << (iFloat/totalLetf) * 100 << " \%" << "\n";
    }

    char textChar;
    int number = 0;
    int numOfNums = 0;
    int sumOfNums = 0;


    // the number stats
    ifstream in1;
    in1.clear();
    in1.open(file);

    while (!in1.eof())
    {
        in1.get(textChar);

        // check how many digits are in one number
        if (isdigit(textChar))
        {
            int tempChar = in1.peek();
            number = (textChar - 48);
            while (isdigit(tempChar))
                {
                    number = number * 10 + (tempChar - 48);
                    in1.get(textChar);
                    tempChar = in1.peek();
                }

            numOfNums++;
            sumOfNums += number;
            number = 0;
        }

    }

    // final output
    out << "\n\nNUMBER ANALYSIS\n\n";
    out << "Number of integers in the file:" << setw(4);
    out << numOfNums << "\n";
    out << "Their sum:" << setw(25);
    out << sumOfNums << "\n";
    
    float numOfNumsF = numOfNums;
    float sumOfNumsF = sumOfNums;

    out.setf(ios::fixed);
    out.setf(ios::showpoint);
    out.precision(2);
    float average = (sumOfNumsF/numOfNumsF);

    out << "Their average:" << setw(21) << average;

}
