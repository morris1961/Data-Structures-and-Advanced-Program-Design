#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Path
{
private:
	int capacity;
	vector<int> nodes;
public:
	Path(int n);
	Path(Path path, int node, int cap);
	void print(vector<string> allNode) const;
	void print() const;
	int getTail() const {return nodes.back();}
	int getBefTail() const{return nodes[nodes.size()-2];}
	int getCapacity() const {return capacity;}
	bool repeat() const;
	int operator[](int i) const{return this->nodes[i];}
	int size() const{return this->nodes.size();}
};

Path::Path(int n):capacity(-1)
{
	this->nodes.push_back(n);
}

Path::Path(Path path, int node, int cap)
{
	for(int i = 0; i < path.nodes.size(); i++)
    	this->nodes.push_back(path.nodes[i]);
  	this->nodes.push_back(node);
  	this->capacity = cap;
}

void Path::print(vector<string> allNode) const
{
	cout << allNode[nodes[0]];
	for(int i = 1; i < nodes.size(); i++)
		cout << "," << allNode[nodes[i]];
	cout << ";" << capacity << endl;
}

void Path::print() const
{
	cout << nodes[0];
	for(int i = 1; i < nodes.size(); i++)
		cout << "," << nodes[i];
	cout << ";" << capacity << endl;
}

bool Path::repeat() const
{
	for(int i = 0; i < nodes.size(); i++)
		for(int j = i+1; j < nodes.size(); j++)
		{
			if(nodes[i] == nodes[j])
				return true;
		}
	return false;
}

class NetWork
{
private:
	int n;
	int** res;
public:
	NetWork(int n);
	~NetWork();
	void setRes(string s, string t, int res, vector<string> allNode);
	void print() const;
	vector<Path> getNext(Path path) const;
	void sortPath(vector<Path>& path, vector<string> allNodes) const;
	Path getAugPath(vector<string> allNodes) const;
	void send(Path path);
	int getMaxFlow(vector<Path> &ansPath, vector<string> allNodes);
};

NetWork::NetWork(int n): n(n)
{
	this->res = new int* [n];
	for(int i = 0; i < n; i++)
		res[i] = new int [n];
	
	for(int i = 0; i < this->n; i++)
		for(int j = 0; j < this->n; j++)
			res[i][j] = 0;
	
}

NetWork::~NetWork()
{
	for(int i = 0; i < this->n; i++)
	{
		delete res[i];
	}
	delete res;		
}

void NetWork::setRes(string s, string t, int res, vector<string> allNode)
{
	int start, end;
	for(int i = 0; i < allNode.size(); i++)
	{
		if(s == allNode[i])
			start = i;
		if(t == allNode[i])
			end = i;
	}
	this->res[start][end] = res;
}

void NetWork::print() const
{
	for(int i = 0; i < this->n; i++)
	{
		for(int j = 0; j < this->n; j++)
			cout << setw(2) << this->res[i][j] << " ";
		cout << endl;
	}  
}

vector<Path> NetWork::getNext(Path path) const
{
	vector<Path> ansPath;
	for(int i = 0; i < this->n; i++)
	{
		if(this->res[path.getTail()][i] > 0)
		{
			int oldC = path.getCapacity();
			int newC = res[path.getTail()][i];
			if(oldC != -1 && newC > oldC)
				newC = oldC;
			Path newPath(path, i, newC);
			ansPath.push_back(newPath);
		}
	}
	return ansPath;
}

void NetWork::sortPath(vector<Path>& path, vector<string> allNodes) const
{
	for (int i = path.size() - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
        {
        	if (res[path[j].getBefTail()][path[j].getTail()] < res[path[j+1].getBefTail()][path[j+1].getTail()])
            {
            	Path temp = path[j];
            	path[j] = path[j+1];
            	path[j+1] = temp;
			}
			else if(res[path[j].getBefTail()][path[j].getTail()] == res[path[j+1].getBefTail()][path[j+1].getTail()])
			{
				if(allNodes[path[j].getTail()] > allNodes[path[j+1].getTail()])
				{
					Path temp = path[j];
            		path[j] = path[j+1];
            		path[j+1] = temp;
				}
			}
		}
}

Path NetWork::getAugPath(vector<string> allNodes) const
{
	Path ansPath(0);
	Path ftPath(0);
	vector<Path> path;
	path.push_back(ftPath);
	
	bool keep = true;
	
	int count = 0, meet = 1;
	
	while(keep && path.size() > 0)
	{

//		cout <<"---------------------" << endl;
//		for(int i = 0; i < path.size(); i++)
//		{
//			path[i].print();
//		}
//		cout << endl;
		
		

//		for(int i = 0; i < path.size(); i++)
//		{
//			path[i].print();
//		}
		
		Path curPath = path.front();
		path.erase(path.begin());
		vector<Path> newPath = this->getNext(curPath);
		this->sortPath(newPath, allNodes);
		
//		for(int i = 0; i < newPath.size(); i++)
//		{
//			newPath[i].print();
//		}
//		cout << endl;

		for(int i = 0; i < newPath.size(); i++)
		{
			if(newPath[i].repeat())
			{
				newPath.erase(newPath.begin()+i);
				i--;
			}
		}

		for(int i = 0; i < newPath.size(); i++)
		{
			if(newPath[i].getTail() == this->n - 1)
			{
				ansPath = newPath[i];
				keep = false;
				break;
			}
			else
			{
				path.push_back(newPath[i]);
			}
		}
	}
	return ansPath;
}

void NetWork::send(Path path)
{
	int cap = path.getCapacity();
	for(int i = 0; i < path.size()-1; i++)
	{
		this->res[path[i]][path[i+1]] += -cap;
		this->res[path[i+1]][path[i]] += cap;
	}
}

int NetWork::getMaxFlow(vector<Path> &ansPath, vector<string> allNodes)
{
	int maxFlow = 0;
	Path cur = this->getAugPath(allNodes);
	while(cur.size() > 1)
	{
		ansPath.push_back(cur);
		maxFlow += cur.getCapacity();
		this->send(cur);
		cur = this->getAugPath(allNodes);
	}
	return maxFlow;
}

int main()
{
	int n = 0, m = 0;
	cin >> n;
	cin.ignore();
	cin >> m;
	
	vector<string> allNode;
	string node;
	cin >> node;
	int begin = 0;
	size_t found = node.find(',');
	while(found != string::npos)
	{
		string temp = node.substr(0, found);
		allNode.push_back(temp);
		node.erase(0,found+1);
		found = node.find(',');
	}
	allNode.push_back(node);
	
	NetWork net(n);
	string p;
	string s, t;
	int res;
	for(int i = 0; i < m; i++)
	{
		cin >> p;

		found = p.find(',');
		s = p.substr(0, found);
		p.erase(0,found+1);
	
		found = p.find(',');
		t = p.substr(0, found);
		p.erase(0,found+1);
		
		found = p.find(',');
		res = stoi(p.substr(0, found));
		p.erase(0,found+1);
		net.setRes(s, t, res, allNode);
	}

	vector<Path> ansPath;
	int ans = net.getMaxFlow(ansPath, allNode);
	for(int i = 0; i < ansPath.size(); i++)
		ansPath[i].print(allNode);
	cout << ans;
	
	return 0;
}
/*
7,10
s,a,b,c,d,e,t
s,a,9
s,c,7
s,e,5
d,t,2
d,a,3
b,d,7
e,c,4
e,d,4
c,b,3
a,b,6
*/
