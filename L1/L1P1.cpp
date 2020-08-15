#include <iostream>
#include <string>
using namespace std;

int main ()
{
	string sen, dle = ",.:;!?";	
	getline(cin, sen);
	int count = 0;
	for(int i = 0; i < 6; i++)
	{
		while(sen.find(dle[i]) != string::npos)
		{
//			cout << sen.find(dle[i]) << "\n";
			count++;
		}
	}
	cout << count;
	return 0;
}
