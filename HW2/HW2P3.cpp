#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
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
	int getWeight(){return weight;}
	int getDanger(){return danger == "Y" ?  1 : 0;}
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
	int allWorkTime;
	string type;
	Ship* workShip;
public:
	Work(string workShip, string startTime, string type);
	~Work(){}
	virtual void print(){}
	string getName(){return workShipName;}
	void setShip(Ship* workShip){this->workShip = workShip;}
	Ship* getShip(){return workShip;}
	int getHour(){return hour;}
	int getMinute(){return minute;}
	void addMinute(int add){this->minute += add;}
	virtual int getOutTime(){}
	virtual int getInTime(){}
	virtual int getWorkTime(){}
	string getType(){return type;}
	virtual int getPort(){}
	int getAllWorkTime(){return allWorkTime;}
	virtual void setAllWorkTime(double m, double *abc, double *t) throw(logic_error){};
};

Work::Work(string workShipName, string startTime, string type)
:workShipName(workShipName), type(type)
{
	int find = startTime.find(':');
	hour = stoi(startTime.substr(0,find));
	minute = stoi(startTime.substr(find+1,2));
	workShip = nullptr;
}

class Iwork : public Work
{
protected:
	int outTime;
	int inTime;
	int port;
	int pier;
public:
	Iwork(string workShipName, string startTime, string type, int port, int pier):Work(workShipName, startTime, type)
	{this->port = port; this->pier = pier;}
	void print(){cout << workShipName << " " << hour << ":" << minute << " " << allWorkTime << " " << type << " " << port << " " << pier << endl;}
	int getPort(){return port;}
	int getOutTime(){return outTime;}
	int getInTime(){return inTime;}
	void setAllWorkTime(double m, double *a, double *t) throw(logic_error);
};

void Iwork::setAllWorkTime(double m, double *a, double *t) throw(logic_error)
{
	if(hour == -1 || port == -1 || pier == -1 || workShip == nullptr)
	{
		allWorkTime = -1;
		throw logic_error("has no value");
	}
	else
	{
		bool isNight = (hour >= 18 || hour < 6 || (hour == 6 && minute == 0));
		int cof[3] = {0};
		cof[0] = 1;
		if(port == 1)
		{
			if(pier%2 == 0)
			{
				cof[1] = pier/2;
				cof[2] = 1;
			}
			else if(pier%2 == 1)
			{
				cof[1] = pier/2 + 1;
				
			}
		}
		else if(port == 2)
		{
			if(pier%2 == 0)
			{
				cof[1] = (m - pier)/2 + 1; 
				cof[2] = 1;
			}
			else if(pier%2 == 1)
			{
				cof[1] = (m - pier)/2 + 1;
			}
		}
		double dis = cof[0] * t[0] + cof[1] * t[1] + cof[2] * t[2];
//		cout << endl << a[0] << " " << (a[1] * dis) << " " << (a[2] * workShip->getWeight()) << " " << (a[3] * workShip->getDanger()) << " " << (a[4] * (isNight ? 1:0)) << endl;
		allWorkTime = a[0] + (a[1] * dis) + (a[2] * workShip->getWeight()) + (a[3] * workShip->getDanger()) + (a[4] * (isNight ? 1:0));
	}
}

class Owork : public Work
{
protected:
	int outTime;
	int inTime;
	int port;
	int pier;
public:
	Owork(string workShipName, string startTime, string type, int port, int pier):Work(workShipName, startTime, type)
	{this->port = port; this->pier = pier;}
	void print(){cout << workShipName << " " << hour << ":" << minute << " " << allWorkTime << " " << type << " " << port << " " << pier << endl;}
	int getPort(){return port;}
	int getOutTime(){return outTime;}
	int getInTime(){return inTime;}
	void setAllWorkTime(double m, double *b, double *t) throw(logic_error);
};

void Owork::setAllWorkTime(double m, double *b, double *t) throw(logic_error)
{
	if(hour == -1 || port == -1 || pier == -1 || workShip == nullptr)
	{
		allWorkTime = -1;
		throw logic_error("has no value");
	}
	else
	{
		bool isNight = (hour >= 18 || hour < 6 || (hour == 6 && minute == 0));
		int cof[3] = {0};
		cof[0] = 1;
		if(port == 1)
		{
			if(pier%2 == 0)
			{
				cof[1] = pier/2;
				cof[2] = 1;
			}
			else if(pier%2 == 1)
			{
				cof[1] = pier/2 + 1;
				
			}
		}
		else if(port == 2)
		{
			if(pier%2 == 0)
			{
				cof[1] = (m - pier)/2 + 1;
				cof[2] = 1;
			}
			else if(pier%2 == 1)
			{
				cof[1] = (m - pier)/2 + 1;
			}
		}
//		cout << cof[0] << " " << cof[1] << " " << cof[2] << endl;
		double dis = cof[0] * t[0] + cof[1] * t[1] + cof[2] * t[2];
//		cout << endl << b[0] << " " << (b[1] * dis) << " " << (b[2] * workShip->getWeight()) << " " << (b[3] * workShip->getDanger()) << " " << (b[4] * (isNight ? 1:0)) << endl;
		allWorkTime = b[0] + (b[1] * dis) + (b[2] * workShip->getWeight()) + (b[3] * workShip->getDanger()) + (b[4] * (isNight ? 1:0));
	}
}

class Twork : public Work
{
protected:
	int worktime;
	int pierS;
	int pierT;
public:
	Twork(string workShipName, string startTime, string type, int pierS, int pierT)
	: Work(workShipName, startTime, type){this->pierS = pierS; this->pierT = pierT;}
	void print(){cout << workShipName << " " << hour << ":" << minute << " "
	 << allWorkTime << " " << type << " " << pierS << " " << pierT << endl;}
	int getWorkTime(){return worktime;}
	void setAllWorkTime(double m, double *c, double *t) throw(logic_error);
};

void Twork::setAllWorkTime(double m, double *c, double *t) throw(logic_error)
{
	if(hour == -1 || pierS == -1 || pierT == -1 || type == "N" || workShip == nullptr)
	{
		allWorkTime = -1;
		throw logic_error("has no value");
	}
	else
	{
		bool isNight = (hour >= 18 || hour < 6 || (hour == 6 && minute == 0));
		int cof[3] = {0};
		cof[0] = 0;
		if( abs(pierT - pierS)%2 == 0)
		{
			cof[1] = abs((pierT - pierS)/2);
		}
		else if(abs(pierT - pierS)%2 == 1)
		{
			cof[2] = 1;
			if(pierT%2 == 0)
				pierT -= 1;
			else if(pierS%2 == 0)
				pierS -= 1;
			cof[1] = abs((pierT - pierS)/2);
		}
//		cout << "k" << cof[0] << " " << cof[1] << " " << cof[2] <<endl;
		double dis = cof[0] * t[0] + cof[1] * t[1] + cof[2] * t[2];
		allWorkTime = c[0] + (c[1] * dis) + (c[2] * workShip->getWeight()) + (c[3] * workShip->getDanger()) + (c[4] * (isNight ? 1:0));
	}
}

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
	void add(string workShipName, string startTime, string type, string p1, string p2);
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

void WorkArray::add(string workShipName, string startTime, string type, string p1, string p2)
{
	if(startTime == "")
		startTime = "-1:-1";
	if(type == "")
		type = "N";
	if(p1 == "")
		p1 = "-1";
	if(p2 == "")
		p2 = "-1";
	if(type == "I")
	{
		work[cnt] = new Iwork(workShipName, startTime, type, stoi(p1), stoi(p2));
		cnt++;
	}
	else if(type == "O")
	{
		work[cnt] = new Owork(workShipName, startTime, type, stoi(p1), stoi(p2));
		cnt++;
	}
	else
	{
		work[cnt] = new Twork(workShipName, startTime, type, stoi(p1), stoi(p2));
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
		string type;
		string p1;
		string p2;
		while(!file.eof())
		{
			getline(file, workShipName, ',');
			getline(file, startTime, ',');
			getline(file, type, ',');
			getline(file, p1, ',');
			getline(file, p2, '\n');
			if(workShipName != "")
			{			
//				cout << workShipName << " " << startTime << " " << type << " " << p1 << " " << p2 << endl;
				work.add(workShipName, startTime, type, p1, p2);
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


int main()
{
	string num;
	double m, a[5] = {0}, b[5] = {0}, c[5] = {0}, t[3] = {0};
	string shipFile = "C:\\Users\\user\\Desktop\\testship.txt";
    string workFile = "C:\\Users\\user\\Desktop\\testwork.txt";
    getline(cin, num, ',');
    m = stod(num);
	for(int i = 0; i < 5; i++)
	{
		getline(cin, num, ',');
		 a[i] = stod(num);
	}
	for(int i = 0; i < 5; i++)
	{
		getline(cin, num, ',');
		 b[i] = stod(num);
	}
	for(int i = 0; i < 5; i++)
	{
		getline(cin, num, ',');
		 c[i] = stod(num);
	}
	for(int i = 0; i < 2; i++)
	{
		getline(cin, num, ',');
		 t[i] = stod(num);
	}
	getline(cin, num, '\n');
	t[2] = stod(num);
	cin >> shipFile >> workFile;
	ShipArray shiparray = parseShip(shipFile);
	WorkArray workarray = parseWork(workFile);
	connect(&workarray, &shiparray);
	int count = 0;
//	workarray.print();
	
	try
	{
		if(workarray.getWork()[0]->getType() == "I")
			workarray.getWork()[0]->setAllWorkTime(m, a, t);
		if(workarray.getWork()[0]->getType() == "O")
			workarray.getWork()[0]->setAllWorkTime(m, b, t);
		if(workarray.getWork()[0]->getType() == "T"|| workarray.getWork()[0]->getType() == "N")
			workarray.getWork()[0]->setAllWorkTime(m, c, t);
	}
	catch(logic_error e)
	{
		count++;
	}
	cout << workarray.getWork()[0]->getAllWorkTime();
//	if(workarray.getWork()[0]->getAllWorkTime() == -1)
//			count++; 
	for(int i = 1; i < workarray.size(); i++)
	{
		try
		{
			if(workarray.getWork()[i]->getType() == "I")
				workarray.getWork()[i]->setAllWorkTime(m, a, t);
			else if(workarray.getWork()[i]->getType() == "O")
				workarray.getWork()[i]->setAllWorkTime(m, b, t);
			else
				workarray.getWork()[i]->setAllWorkTime(m, c, t);
		}
		catch(logic_error e)
		{
			count++; 
		}
		cout  << "," << workarray.getWork()[i]->getAllWorkTime();
//		if(workarray.getWork()[i]->getAllWorkTime() == -1)
//			count++; 
	}
	cout << endl << count;
//	workarray.print();
	return 0;
}
//200,5,0.0225,0.007,5,5,3,0.015,0.007,4,5,4,0.02,0.005,7,4,7,1,9
//AnotherAnotherShipSample.txt
//AnotherAnotherWorkSample.txt
