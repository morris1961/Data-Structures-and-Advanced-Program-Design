#include <iostream>
using namespace std;

void bubbleSort(int*, int);

int main()
{
	int n = 0, m = 0, s = 0, st = 0;
	cin >> n >> m;
	int **note = new int *[n], *u = new int [m], *v = new int [m];
	int *count = new int[n];
	for (int i = 0; i < n; i++)
		count[i] = 0;
	for (int i = 0; i < m; i++)
	{
		cin >> u[i] >> v[i];
		u[i]--;
		v[i]--;
		count[u[i]]++;
		count[v[i]]++;
	}
	cin >> st >> s;
	st--;
	for (int i = 0; i < n; i++)
	{
		note[i] = new int [count[i]];
		count[i] = 0;
	}
	for (int i = 0; i < m; i++)
	{
		note[u[i]][count[u[i]]] = v[i];
		count[u[i]]++;
		note[v[i]][count[v[i]]] = u[i];
		count[v[i]]++;
	}
//	for(int i = 0; i < n; i++)
//	{
//		cout << i+1;
//		for (int j = 0; j < count[i]; j++)
//			cout << " " << note[i][j]+1;
//		cout << endl;
//	}
	if(count[st] > 0)
	{
		if(s == 1)
		{
			cout << note[st][0]+1;
			for (int j = 1; j < count[st]; j++)
				cout << " " << note[st][j]+1;
		}
		else if(s == 2)
		{
			int step2 = 0, ansCt = 0;
			for(int i = 0; i < count[st]; i++)
			{
				step2 += count[note[st][i]];
			}
			int *answer = new int [step2];
			for(int i = 0; i < count[st]; i++)
			{
				answer[ansCt] = note[st][i];
				ansCt++;
				for(int k = 0; k < ansCt-1 ;k++)
				{
					if(note[st][i] == answer[k])
					{
						ansCt--;
						break;
					}
				}
				for(int j = 0; j < count[note[st][i]]; j++)
				{
					if (note[note[st][i]][j] != st)
					{
						answer[ansCt] = note[note[st][i]][j];
						ansCt++;
						for(int k = 0; k < ansCt-1 ;k++)
						{
							if(note[note[st][i]][j] == answer[k])
							{
								ansCt--;
								break;
							}		
						}			
					}
				}
			}
			bubbleSort(answer, ansCt);
			cout << answer[0]+1;
			for (int j = 1; j < ansCt; j++)
				cout << " " << answer[j]+1;
		}
	}
	return 0;
}

void bubbleSort(int *answer, int len)
{
	for (int i = len - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (answer[j] > answer[j + 1])
            {
            	int temp = answer[j];
            	answer[j] = answer[j+1];
            	answer[j+1] = temp;
			}
}
