#include <iostream>
#include <string>
using namespace std;

int main ()
{
	int money_num = 0;
	cin >> money_num;
	string money = to_string(money_num);
//	money.insert(0,"$");&& money.size() - i != 1
	for(int i = 0; i < money.size() ;i++)
	{
		if(i%4 == 3 )
			money.insert(money.size() - i, ",");
	}
	cout << money;
	return 0;
}
