#include <iostream>
#include "HaffmanAlgorithm.h"
#include "Map.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
    string phrase;
    cout << "Enter the text: ";
    getline(cin, phrase);
    cout << "Size before the compression: " << phrase.length() * 8 << " bits" << endl;
    cout << "\nCodes and frequencies table: " << endl;
    HaffmanTree encode(phrase);

   string code = encode.getCode(phrase);
   cout << "\nEncoding result: " << code<<endl;

   cout << "\nSize after the compression: "<<code.length()<<" bits"<<endl;

   cout << "Compression coefficient: " <<encode.Compression(phrase, code)<< "% "<<endl;
   string decode = encode.getText(code, encode);
   cout << "\nDecoding result:" << decode<< endl;
    return 0;
}