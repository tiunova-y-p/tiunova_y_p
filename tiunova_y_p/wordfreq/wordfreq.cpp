#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

string delim(".:,;()-?!");
string inputText;
string word;
map<string, size_t> freqTable;
//map<string, double> fTab;
size_t wordNum;
size_t index;

int main()
{
    cout << "Dictionary" << endl;
    cout << "==========" << endl << endl;
    cout << "Input text: ";

    ifstream txtFile("C:\\tiunova_y_p\\tiunova_y_p\\Debug\\text.txt", ios::in); //Открываем файл для считывания информации 
    getline(txtFile, inputText);
    txtFile.close(); // Закрываем файл

    cout << inputText << endl;

    while ((index = inputText.find_first_of(delim)) != string::npos)
        inputText[index] = ' ';

    cout << "Pure text:  " << inputText << endl;

    istringstream ss(inputText);
    wordNum = 0;

    while (ss >> word)
    {
        ++wordNum;
        freqTable[word]++; 
    }
    cout << endl;

    cout << "Frequencies table:" << endl;

    for (map<string, size_t>::iterator iter = freqTable.begin(); iter != freqTable.end(); ++iter)
    {
        double p = static_cast<double>(iter->second) / static_cast<double>(wordNum) * 100;
        cout << "\'" << iter->first << "\'\t:\t" << setw(6) << setprecision(3) << setfill(' ') << p << "%" << endl;
    }
    cout << endl;

    system("pause");

    return 0;
}

















