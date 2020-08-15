#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
    vector<string> *input;
    vector<string> output;
    int n;
 
    cin >> n;
    input = new vector<string>[n];
 
 	cin.ignore();
 	for(int i = 0; i < n; i++)
 	{
 		string line;
 		getline(cin, line);
 		int index = line.find(",");
 		while(index != string::npos)
 		{
 			string t = line.substr(0, index);
 			input[i].push_back(t);
 			line.erase(0, index+1);
 			index = line.find(",");
		}
		input[i].push_back(line);
//		for(int j = 0; j < input[i].size(); j++)
//		{
//			cout << input[i][j] << ",";
//		}
//		cout << endl;
	}
	
	for(int i = 0; i < n; i++)
	{
		if (input[i].size() == 0)
			continue;
		else if(input[i].size() == 1)
		{
//			cout << "put " << input[i][0] << endl;
			output.push_back(input[i][0]);
			input[i].pop_back();
			i = -1;
		}
		else if(input[i].size() > 1)
		{
			for(int j = input[i].size() - 1; j > 0; j--)
			{
				for(int k = 0; k < output.size(); k++)
				{
					if(input[i][j] == output[k])
					{
						input[i].pop_back();
//						j = input[i].size();
						break;
					} 
				}
			}
			if(input[i].size() == 1)
			{
//				cout << "in put " << input[i][0] << endl;
				output.push_back(input[i][0]);
				input[i].pop_back();
				i = -1;
			}
			else
				continue;
		}
		
	}
//	for(int i = 0; i < output.size(); i++)
//	{
//		cout << output[i] << endl;
//	}
	cout << output[0];
	for(int j = 1; j < output.size(); j++)
	{
		cout << "\n" << output[j];
	} 
}
