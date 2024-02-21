#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <chrono>
#include <random>
#include <windows.h>

using namespace std;

#include "GenEquation.h"

void readPlainText(vector<char>& plainText, const string& fileName) {
    ifstream plainTextFile(fileName);
    char getCharOne;

    if (plainTextFile.is_open()) {
        while (plainTextFile.get(getCharOne)) {
            if (getCharOne >= 'a' && getCharOne <= 'z')
            {
                getCharOne = getCharOne - 32;
                plainText.push_back(getCharOne);
            }
            else if (getCharOne >= 'A' && getCharOne <= 'Z')
            {
                plainText.push_back(getCharOne);
            }
            else if (isblank(getCharOne))
            {
                plainText.push_back(' ');
            }
            else if (ispunct(getCharOne))
            {
                plainText.push_back(getCharOne);
            }
            else if (isspace(getCharOne))
            {
                plainText.push_back(getCharOne);
            }
            else if (isdigit(getCharOne))
            {
                plainText.push_back(getCharOne);
            }
        }
        plainTextFile.close();
    }
}

void caesarCipherEncrypt(const vector<char>& plainText, vector<char>& cipherText, int key) {
    char getCharTwo;

    for (int i = 0; i < plainText.size(); i++) {
        getCharTwo = plainText[i];
        if (getCharTwo >= 'a' && getCharTwo <= 'z')
        {
            //normal shifting from a to z
            getCharTwo = getCharTwo + key;
            //shifting from z back to a
            if (getCharTwo > 'z')
            {
                getCharTwo = getCharTwo - 'z' + 'a' - 1;
            }
            else if (getCharTwo < 'a')
            {
                //shifting from z to a
                getCharTwo = getCharTwo + 26;
            }
            //store char as element of cipherText
            cipherText.push_back(getCharTwo);
        }
        else if (getCharTwo >= 'A' && getCharTwo <= 'Z')
        {
            getCharTwo = getCharTwo + key;
            if (getCharTwo > 'Z')
            {
                getCharTwo = getCharTwo - 'Z' + 'A' - 1;
            }
            else if (getCharTwo < 'A')
            {
                getCharTwo = getCharTwo + 26;
            }
            cipherText.push_back(getCharTwo);
        }

        //push back blank space, punctuations, integer etc as it is
        else if (isblank(getCharTwo))
        {
            cipherText.push_back(' ');
        }
        else if (ispunct(getCharTwo))
        {
            cipherText.push_back(getCharTwo);
        }
        else if (isspace(getCharTwo))
        {
            cipherText.push_back(getCharTwo);
        }
        else if (isdigit(getCharTwo))
        {
            cipherText.push_back(getCharTwo);
        }
    }
}

void saveCipherTextToFile(const vector<char>& cipherText, const string& outputCipherText) {
    ofstream myfile(outputCipherText);

    for (int i = 0; i < cipherText.size(); i++) {
        myfile << cipherText[i];
    }

    cout << "Output Encrypted Text to: " << outputCipherText << endl;
    myfile.close();
}

void caesarCipherDecrypt(const vector<char>& cipherText, vector<char>& decryptedText, int key) {
    char getCharThird;

    for (int i = 0; i < cipherText.size(); i++) {
        getCharThird = cipherText[i];
        if (getCharThird >= 'a' && getCharThird <= 'z')
        {
            //reverting back to decrrypted text
            getCharThird = getCharThird - key;
            if (getCharThird < 'a')
            {
                //shift z to a
                getCharThird = getCharThird + 'z' - 'a' + 1;
            }
            else if (getCharThird > 'z')
            {
                //shift a to z
                getCharThird = getCharThird - 26;
            }
            decryptedText.push_back(getCharThird);
        }
        else if (getCharThird >= 'A' && getCharThird <= 'Z')
        {
            getCharThird = getCharThird - key;
            if (getCharThird < 'A')
            {
                getCharThird = getCharThird + 'Z' - 'A' + 1;
            }
            else if (getCharThird > 'Z')
            {
                getCharThird = getCharThird - 26;
            }
            decryptedText.push_back(getCharThird);
        }

        //push back blank space, punctuations, integer etc as it is
        else if (isblank(getCharThird))
        {
            decryptedText.push_back(' ');
        }
        else if (ispunct(getCharThird))
        {
            decryptedText.push_back(getCharThird);
        }
        else if (isspace(getCharThird))
        {
            decryptedText.push_back(getCharThird);
        }
        else if (isdigit(getCharThird))
        {
            decryptedText.push_back(getCharThird);
        }
    }
}

void saveDecryptedTextToFile(const vector<char>& decryptedText, const string& outputDecryptedText) {
    ofstream myfileTwo(outputDecryptedText);

    for (int i = 0; i < decryptedText.size(); i++) {
        myfileTwo << decryptedText[i];
    }

    cout << "Output Decrypted Text to: " << outputDecryptedText << endl;
    myfileTwo.close();
}

int main()
{
    time_t start, end;
    time(&start);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, 25);

    // Map of keywords to corresponding formulas
    map<string, string> formulas = {
        {"ALGEBRA", "X + Y = Z"},
        {"PERIMETER OF SQUARE", "P = 2(LENGTH * WIDTH)"},
        {"AREA OF SQUARE", "A = LENGTH * LENGTH"},
        {"RECTANGLE", "A = WIDTH * HEIGHT"},
        // Add more keywords and formulas as needed
    };

    vector<char> plainText;
    vector<char> cipherText;
    vector<char> decryptedText;

    int key;

    string fileName = "plaintext.txt";
    string outputCipherText = "ciphertext.txt";
    string outputDecryptedText = "decrypted.txt";

    readPlainText(plainText, fileName);
    cout << "Reading from file: " << fileName << endl;
    Sleep(1238);
    key = distr(gen);

    caesarCipherEncrypt(plainText, cipherText, key);
    saveCipherTextToFile(cipherText, outputCipherText);

    cout << "Decrypting Cipher Text... " << endl;
    Sleep(1836);

    caesarCipherDecrypt(cipherText, decryptedText, key);
    saveDecryptedTextToFile(decryptedText, outputDecryptedText);

    cout << endl;

    // Prompt user to input a question
    cout << "Processing Decrypted Text for Equation Generation... " << endl;
    Sleep(1936);
    
    if (ifstream ifs{outputDecryptedText })
    {
        string userQuestion((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());

        // Generate the correct equation based on user input
        string generatedEquation = generateEquation(userQuestion, formulas);

        // Display the user's question and the generated equation
        cout << "\nYour question: " << userQuestion << endl;
        cout << "Generated equation: " << generatedEquation << endl;
    }

    // You can now proceed with code to solve the equation, check user input, etc.

    time(&end); 
    double time_taken = double(end - start);
    printf("Time taken by function : %.2f seconds\n", time_taken);

    return 0;
}