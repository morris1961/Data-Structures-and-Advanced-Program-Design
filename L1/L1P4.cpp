#include <iostream>
#include <string>
#include <cctype>
#include <fstream> 
using namespace std;

int main ()
{
	bool have = false;
	string checkWord, fileName;
	cin >> checkWord;
	cin.ignore();
	getline(cin,fileName);
	for(int i = 0; i < checkWord.size(); i++)
		checkWord[i] = tolower(checkWord[i]);
	
	string words;
	
	ifstream file;
	file.open(fileName);
	ofstream fout;
	fout.open("plain-text.txt");
	if(file.is_open())
	{
		while(!file.eof())
		{
			file >> words;
			fout << "Comparing " << checkWord << " with " << words;
			if(checkWord == words)
			{
				fout << "... Got it!\n";
				have = true;
			}
			else
			{
				fout << "\n";
			}
				
		}
	}
	else
	{
		cout << "file fail";
	}
	file.close();
	fout.close();
	

	

	if(have)
		cout << 1;
	else
		cout << 0;
	return 0;
}
