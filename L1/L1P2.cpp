#include <iostream>
#include <string>
using namespace std;

int main ()
{
	int n = 0;
	bool have = false;
	string checkWord;
	cin >> n >> checkWord;
	for(int i = 0; i < checkWord.size(); i++)
		checkWord[i] = tolower(checkWord[i]);
	string words;
	for(int i = 0 ;i < n; i++)
	{
		cin >> words;
		if(checkWord == words)
			have = true;
	}
	if(have)
		cout << 1;
	else
		cout << 0;
	
	return 0;
}
