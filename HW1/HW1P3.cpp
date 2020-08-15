#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Ship
{
protected:
	string name;
	int weight;
	string nationality;
	string captainName;
	string danger;
public:
	Ship(string name, int weight, string nationality, string captainName, string danger);
	void print();
	string getName(){return name;}
};

Ship::Ship(string name, int weight, string nationality, string captainName, string danger)
:name(name), weight(weight), nationality(nationality), captainName(captainName), danger(danger)
{
}

void Ship::print()
{
	cout << name << " " << weight << " " << nationality << " " << captainName << " " << danger << "\n";
}

class Work
{
protected:
	string workShipName;
	int hour;
	int minute;
	int worktime;
	string type;
	Ship* workShip;
public:
	Work(string workShip, string startTime,  int worktime, string type);
	virtual void print(){}
	string getName(){return workShipName;}
	void setShip(Ship* workShip){this->workShip = workShip;}
	Ship* getShip(){return workShip;}
	int getHour(){return hour;}
	int getMinute(){return minute;}
	void addMinute(int add){this->minute += add;}
	int getTime(){return worktime;}
	string getType(){return type;}
	virtual int getPort(){}
};
Work::Work(string workShipName, string startTime, int worktime, string type)
:workShipName(workShipName), worktime(worktime), type(type)
{
	int find = startTime.find(':');
	hour = stoi(startTime.substr(0,find));
	minute = stoi(startTime.substr(find+1,2));
}

class Iwork : public Work
{
protected:
	int port;
	int pier;
public:
	Iwork(string workShipName, string startTime, int worktime, string type, int port, int pier)
	: Work(workShipName, startTime, worktime, type){this->port = port; this->pier = pier;}
	void print(){cout << workShipName << " " << hour << ":" << minute << " " << worktime << " " << type << " " << port << " " << pier << endl;}
	int getPort(){return port;}
};

class Owork : public Work
{
protected:
	int port;
	int pier;
public:
	Owork(string workShipName, string startTime, int worktime, string type, int port, int pier)
	: Work(workShipName, startTime, worktime, type){this->port = port; this->pier = pier;}
	void print(){cout << workShipName << " " << hour << ":" << minute << " " << worktime << " " << type << " " << port << " " << pier << endl;}
	int getPort(){return port;}
};

class Twork : public Work
{
protected:
	int pierS;
	int pierT;
public:
	Twork(string workShipName, string startTime, int worktime, string type, int pierS, int pierT)
	: Work(workShipName, startTime, worktime, type){this->pierS = pierS; this->pierT = pierT;}
	void print(){cout << workShipName << " " << hour << ":" << minute << " " << worktime << " " << type << " " << pierS << " " << pierT << endl;}
};

class ShipArray
{
protected:
	int cnt;
	Ship** ship;
public:
	ShipArray(int count);
	~ShipArray();
	void add(string name, int weight, string nationality, string captainName, string danger);
	void print();
	int size(){return cnt;}
	Ship** getShip(){return ship;}
};

ShipArray::ShipArray(int count)
{
	this->cnt = 0;
	this->ship = new Ship*[count];
}

ShipArray::~ShipArray()
{
	for(int i = 0; i < this->cnt; i++)
		delete this->ship[i];
	delete [] this->ship;
}

void ShipArray::add(string name, int weight, string nationality, string captainName, string danger)
{
	ship[cnt] = new Ship(name, weight, nationality, captainName, danger);
	cnt++;
}

void ShipArray::print()
{
	for(int i = 0; i < this->cnt; i++)
		ship[i]->print();
}

class WorkArray
{
protected:
	int cnt;
	Work** work;
public:
	WorkArray(int count);
	~WorkArray();
	void add(string workShipName, string startTime, int worktime, string type, int p1, int p2);
	void add(Work* work);
	void print();
	int size(){return cnt;}
	Work** getWork(){return work;}
	void del(int index);
};

WorkArray::WorkArray(int count)
{
	this->cnt = 0;
	this->work = new Work*[count];
}

WorkArray::~WorkArray()
{
	for(int i = 0; i < this->cnt; i++)
		delete this->work[i];
	delete [] this->work;
}

void WorkArray::add(string workShipName, string startTime, int worktime, string type, int p1, int p2)
{
	if(type == "I")
	{
		work[cnt] = new Iwork(workShipName, startTime, worktime, type, p1, p2);
		cnt++;
	}
	else if(type == "O")
	{
		work[cnt] = new Owork(workShipName, startTime, worktime, type, p1, p2);
		cnt++;
	}
	else if(type == "T")
	{
		work[cnt] = new Twork(workShipName, startTime, worktime, type, p1, p2);
		cnt++;
	}
}

void WorkArray::add(Work* work)
{
	this->work[this->cnt] = work;
	cnt++;
}

void WorkArray::print()
{
	for(int i = 0; i < this->cnt; i++)
		work[i]->print();
}

void WorkArray::del(int index)
{
	Work** tempwork = new Work* [cnt - 1];
	for(int i = 0; i < index; i++)
	{
		tempwork[i] = this->work[i];
	}
	for(int i = index + 1; i < this->cnt; i++)
	{
		tempwork[i - 1] = this->work[i];
	}
	cnt--;
	this->work = tempwork;
}

ShipArray parseShip(string fileName)
{
	int count = 0;
	string words;
	ifstream file;
	file.open(fileName);
	if(file)
	{
		while(!file.eof())
		{
			getline(file, words, '\n');
			count++;
		}
	}
	file.close();
	
	ShipArray ship(count);
	file.open(fileName);
	if(file)
	{	
		string name;
		string weight;
		string nationality;
		string captainName;
		string danger;
		while(!file.eof())
		{
			getline(file, name, ',');
			getline(file, weight, ',');
			getline(file, nationality, ',');
			getline(file, captainName, ',');
			getline(file, danger, '\n');
			if(name != "")
			{
				ship.add(name, stoi(weight), nationality, captainName, danger);
			}
		}
	}
	file.close();
	return ship;
}

WorkArray parseWork(string fileName)
{
	int count = 0;
	string words;
	ifstream file;
	file.open(fileName);
	if(file)
	{
		while(!file.eof())
		{
			getline(file, words, '\n');
			count++;
		}
	}
	file.close();
	
	WorkArray work(count);
	file.open(fileName);
	if(file)
	{	
		string workShipName;
		string startTime;
		string worktime;
		string type;
		string p1;
		string p2;
		while(!file.eof())
		{
			getline(file, workShipName, ',');
			getline(file, startTime, ',');
			getline(file, worktime, ',');
			getline(file, type, ',');
			getline(file, p1, ',');
			getline(file, p2, '\n');
			if(workShipName != "" )
			{
				work.add(workShipName, startTime, stoi(worktime), type, stoi(p1), stoi(p2));
			}
		}
	}
	file.close();
	return work;
	
}

void connect(WorkArray* workarray, ShipArray* shiparray)
{
	for(int i = 0; i < workarray->size(); i++)
		for(int j = 0; j < shiparray->size(); j++)
		{
			if(workarray->getWork()[i]->getName() == shiparray->getShip()[j]->getName())
				workarray->getWork()[i]->setShip(shiparray->getShip()[j]);
		}
}

WorkArray** sep(WorkArray* workarray)
{
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < workarray->size(); i++)
	{
		if(workarray->getWork()[i]->getType() == "O" || workarray->getWork()[i]->getType() == "I")
		{
			if(workarray->getWork()[i]->getPort() == 1)
				cnt1++;
			else if(workarray->getWork()[i]->getPort() == 2)
				cnt2++;
		}
	}
	WorkArray** workPort = new WorkArray*[2];
	workPort[0] = new WorkArray(cnt1);
	workPort[1] = new WorkArray(cnt2);
	for (int i = 0; i < workarray->size(); i++)
	{
		if(workarray->getWork()[i]->getType() == "O" || workarray->getWork()[i]->getType() == "I")
		{
			if(workarray->getWork()[i]->getPort() == 1)
			{
				workPort[0]->add(workarray->getWork()[i]);
			}	
			else if(workarray->getWork()[i]->getPort() == 2)
			{	
				workPort[1]->add(workarray->getWork()[i]);
			}
		}
	}
	return workPort;
}

int solutionERT(WorkArray** workPort)
{
	for(int k = 0; k < 2; k++)
	{
		for (int i = workPort[k]->size() - 1; i > 0; i--)
	        for (int j = 0; j < i; j++)
	        {
	        	if (workPort[k]->getWork()[j]->getHour() > workPort[k]->getWork()[j + 1]->getHour())
	            {
	            	Work* temp = workPort[k]->getWork()[j];
	            	workPort[k]->getWork()[j] = workPort[k]->getWork()[j+1];
	            	workPort[k]->getWork()[j+1] = temp;
				}
				else if(workPort[k]->getWork()[j]->getHour() == workPort[k]->getWork()[j + 1]->getHour())
				{
					if(workPort[k]->getWork()[j]->getMinute() > workPort[k]->getWork()[j + 1]->getMinute())
	            	{
	            		Work* temp = workPort[k]->getWork()[j];
		            	workPort[k]->getWork()[j] = workPort[k]->getWork()[j+1];
		            	workPort[k]->getWork()[j+1] = temp;
					}	
	            	else if(workPort[k]->getWork()[j]->getMinute() == workPort[k]->getWork()[j + 1]->getMinute())
	            	{
	            		if(workPort[k]->getWork()[j]->getTime() > workPort[k]->getWork()[j + 1]->getTime())
	            		{
	            			Work* temp = workPort[k]->getWork()[j];
			            	workPort[k]->getWork()[j] = workPort[k]->getWork()[j+1];
			            	workPort[k]->getWork()[j+1] = temp;
						}
						else if(workPort[k]->getWork()[j]->getTime() == workPort[k]->getWork()[j + 1]->getTime())
						{
							if(workPort[k]->getWork()[j]->getName() > workPort[k]->getWork()[j + 1]->getName())
		            		{
		            			Work* temp = workPort[k]->getWork()[j];
				            	workPort[k]->getWork()[j] = workPort[k]->getWork()[j+1];
				            	workPort[k]->getWork()[j+1] = temp;
							}
						}
					}
				}
			}
	}
	
	int answer1 = 0;
	for(int k = 0; k < 2; k++)
	{
		for(int i = 0; i < workPort[k]->size(); i++)
		{
			workPort[k]->getWork()[i]->addMinute(workPort[k]->getWork()[i]->getHour() * 60);
		}
	}
	for(int k = 0; k < 2; k++)
	{
		int timeLine[2][workPort[k]->size()] = {0};
		for(int i = 0; i < workPort[k]->size(); i++)
		{
			bool hit = false;
			for(int j = 0; j < i; j++)
			{
				if( (workPort[k]->getWork()[i]->getMinute() >= timeLine[1][j]
					 && workPort[k]->getWork()[i]->getMinute() + workPort[k]->getWork()[i]->getTime() >= timeLine[1][j])
					 || (workPort[k]->getWork()[i]->getMinute() <= timeLine[0][j]
					 && workPort[k]->getWork()[i]->getMinute() + workPort[k]->getWork()[i]->getTime() <= timeLine[0][j]))
				{
					continue;
				}
				else
				{
					hit = true;
					break;
				}			
			}
			
			if(hit)
			{
				int count = 0;
				for(int j = 0; j < i - 1; j++)
				{
					if(workPort[k]->getWork()[i]->getMinute() < timeLine[1][j])
					{
						if(timeLine[0][j + 1] - timeLine[1][j] == workPort[k]->getWork()[i]->getTime())
						{
							timeLine[0][i] = timeLine[1][j];
							timeLine[1][i] = timeLine[0][j + 1];
							answer1 += timeLine[0][i] - workPort[k]->getWork()[i]->getMinute();
							break;
						}
						else
							count++;
					}
					else
						count++;
				}
				if(count == i - 1)
				{
					timeLine[0][i] = timeLine[1][i - 1];
					timeLine[1][i] = timeLine[0][i] + workPort[k]->getWork()[i]->getTime();
					answer1 += timeLine[0][i] - workPort[k]->getWork()[i]->getMinute();
				}
			}
			else
			{
				timeLine[0][i] = workPort[k]->getWork()[i]->getMinute();
				timeLine[1][i] = workPort[k]->getWork()[i]->getMinute() + workPort[k]->getWork()[i]->getTime();
			}
			 
			for (int j = i; j > 0; j--)
	        	for (int l = 0; l < j; l++)
	        	{
	        		if(timeLine[0][l] > timeLine[0][l + 1])
	        		{
	        			int temp1 = timeLine[0][l], temp2 = timeLine[1][l];
						timeLine[0][l] = timeLine[0][l + 1];
						timeLine[1][l] = timeLine[1][l + 1];
						timeLine[0][l + 1] = temp1;
						timeLine[1][l + 1] = temp2;
					}
					else if(timeLine[0][l] == timeLine[0][l + 1])
					{
						if(timeLine[1][l] > timeLine[1][l + 1])
						{
							int temp1 = timeLine[0][l], temp2 = timeLine[1][l];
							timeLine[0][l] = timeLine[0][l + 1];
							timeLine[1][l] = timeLine[1][l + 1];
							timeLine[0][l + 1] = temp1;
							timeLine[1][l + 1] = temp2;
						}
					}
				}
			for(int j = 0; j <= i; j++)
				cout << timeLine[0][j] << "~" << timeLine[1][j] << " ";
			cout << "ans:" << answer1 << endl; 
		}
	}
	for(int k = 0; k < 2; k++)
	{
		for(int i = 0; i < workPort[k]->size(); i++)
		{
			workPort[k]->getWork()[i]->addMinute(-workPort[k]->getWork()[i]->getHour() * 60);
		}
	}
	return answer1;
}

int solutionSPT(WorkArray** workPort)
{
	for(int k = 0; k < 2; k++)
	{
		for (int i = workPort[k]->size() - 1; i > 0; i--)
	        for (int j = 0; j < i; j++)
	        {
	        	if(workPort[k]->getWork()[j]->getTime() > workPort[k]->getWork()[j + 1]->getTime())
	        	{
	        		Work* temp = workPort[k]->getWork()[j];
	            	workPort[k]->getWork()[j] = workPort[k]->getWork()[j+1];
	            	workPort[k]->getWork()[j+1] = temp;
				}
				else if(workPort[k]->getWork()[j]->getTime() == workPort[k]->getWork()[j + 1]->getTime())
				{
					if (workPort[k]->getWork()[j]->getHour() > workPort[k]->getWork()[j + 1]->getHour())
		            {
		            	Work* temp = workPort[k]->getWork()[j];
		            	workPort[k]->getWork()[j] = workPort[k]->getWork()[j+1];
		            	workPort[k]->getWork()[j+1] = temp;
					}
					else if(workPort[k]->getWork()[j]->getHour() == workPort[k]->getWork()[j + 1]->getHour())
					{
						if (workPort[k]->getWork()[j]->getMinute() > workPort[k]->getWork()[j + 1]->getMinute())
			            {
			            	Work* temp = workPort[k]->getWork()[j];
			            	workPort[k]->getWork()[j] = workPort[k]->getWork()[j+1];
			            	workPort[k]->getWork()[j+1] = temp;
						}
						else if (workPort[k]->getWork()[j]->getMinute() == workPort[k]->getWork()[j + 1]->getMinute())
						{
							if(workPort[k]->getWork()[j]->getName() > workPort[k]->getWork()[j + 1]->getName())
				            {
				            	Work* temp = workPort[k]->getWork()[j];
				            	workPort[k]->getWork()[j] = workPort[k]->getWork()[j+1];
				            	workPort[k]->getWork()[j+1] = temp;
							}
						}
					}
				}
			}
	}
	
	for(int k = 0; k < 2; k++)
	{
		for(int i = 0; i < workPort[k]->size(); i++)
		{
			workPort[k]->getWork()[i]->addMinute(workPort[k]->getWork()[i]->getHour() * 60);
		}
	}
	int answer2 = 0;
	
	for(int k = 0; k < 2; k++)
	{
		int timeLine[2][workPort[k]->size()] = {0};
		for(int i = 0; i < workPort[k]->size(); i++)
		{
			bool hit = false;
			for(int j = 0; j < i; j++)
			{
				if( (workPort[k]->getWork()[i]->getMinute() >= timeLine[1][j]
					 && workPort[k]->getWork()[i]->getMinute() + workPort[k]->getWork()[i]->getTime() >= timeLine[1][j])
					 || (workPort[k]->getWork()[i]->getMinute() <= timeLine[0][j]
					 && workPort[k]->getWork()[i]->getMinute() + workPort[k]->getWork()[i]->getTime() <= timeLine[0][j]))
				{
					continue;
				}
				else
				{
					hit = true;
					break;
				}			
			}
			
			if(hit)
			{
				int count = 0;
				for(int j = 0; j < i - 1; j++)
				{
					if(workPort[k]->getWork()[i]->getMinute() < timeLine[1][j])
					{
						if(timeLine[0][j + 1] - timeLine[1][j] >= workPort[k]->getWork()[i]->getTime())
						{
							timeLine[0][i] = timeLine[1][j];
							timeLine[1][i] = timeLine[0][i] + workPort[k]->getWork()[i]->getTime();
							answer2 += timeLine[0][i] - workPort[k]->getWork()[i]->getMinute();
							break;
						}
						else
							count++;
					}
					else
						count++;
				}
				if(count == i - 1)
				{
					timeLine[0][i] = timeLine[1][i - 1];
					timeLine[1][i] = timeLine[0][i] + workPort[k]->getWork()[i]->getTime();
					answer2 += timeLine[0][i] - workPort[k]->getWork()[i]->getMinute();
				}
			}
			else
			{
				timeLine[0][i] = workPort[k]->getWork()[i]->getMinute();
				timeLine[1][i] = workPort[k]->getWork()[i]->getMinute() + workPort[k]->getWork()[i]->getTime();
			}
			 
			for (int j = i; j > 0; j--)
	        	for (int l = 0; l < j; l++)
	        	{
	        		if(timeLine[0][l] > timeLine[0][l + 1])
	        		{
	        			int temp1 = timeLine[0][l], temp2 = timeLine[1][l];
						timeLine[0][l] = timeLine[0][l + 1];
						timeLine[1][l] = timeLine[1][l + 1];
						timeLine[0][l + 1] = temp1;
						timeLine[1][l + 1] = temp2;
					}
					else if(timeLine[0][l] == timeLine[0][l + 1])
					{
						if(timeLine[1][l] > timeLine[1][l + 1])
						{
							int temp1 = timeLine[0][l], temp2 = timeLine[1][l];
							timeLine[0][l] = timeLine[0][l + 1];
							timeLine[1][l] = timeLine[1][l + 1];
							timeLine[0][l + 1] = temp1;
							timeLine[1][l + 1] = temp2;
						}
					}
				}
//			for(int j = 0; j <= i; j++)
//				cout << timeLine[0][j] << "~" << timeLine[1][j] << " ";
//			cout << "ans:" << answer2 << endl; 
		}
	}
	
	
	for(int k = 0; k < 2; k++)
	{
		for(int i = 0; i < workPort[k]->size(); i++)
		{
			workPort[k]->getWork()[i]->addMinute(-workPort[k]->getWork()[i]->getHour() * 60);
		}
	}
	return answer2;
}

int main()
{
	int m;
	string shipFile = "ShipSample.txt";
    string workFile = "worksample" + to_string(65) + ".txt";
	ShipArray shiparray = parseShip(shipFile);
	WorkArray workarray = parseWork(workFile);
	WorkArray** workPort = sep(&workarray);

	return 0;
}

