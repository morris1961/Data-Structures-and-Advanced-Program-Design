#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
bool isIn(vector<string> a, string b);
class Period
{
public:
    Period() {this->num = 0;}
    void set(int start, int end) {node[0][num] = start; node[1][num] = end; num++;}
    bool check(int start, int end, int &where);
    void reset();
    void print();
private:
    int node[2][1000];
    int num;
};
bool Period::check(int start, int end, int &where)
{
       
    for(int i = 0;i<this->num;i++)
    {
        if((end > node[0][i] && start < node[1][i])||(end == node[1][i]&&start == node[0][i]))
        {
            where = node[1][i];
            return false;
        }
    }
    return true;
}

void Period::reset()
{
    for(int i = 0;i<this->num;i++)
    {
        node[0][i] = 0;
        node[1][i] = 0;
    }
    num = 0;
}

void Period::print()
{
	for(int i = 0;i<this->num;i++)
	{
		cout << node[0][i] << "~" << node[1][i] << endl;
	}
}
class Ship
{
public:
    Ship(string shipName, int weight, string country, string captainName, bool isDangerous);
    int getWeight() {return weight;}
    void bePrior(){this->isPrior = true;}
    string getShipName() {return shipName;}
    bool isDanger() {return isDangerous;}
    bool getPrior(){return isPrior;}
protected:
        
    string shipName;
    int weight;
    string country;
    string captainName;
    bool isDangerous;
    bool isPrior;
};
Ship::Ship(string shipName, int weight, string country, string captainName, bool isDangerous)
{
    this->shipName = shipName;
    this->weight = weight;
    this->country = country;
    this->captainName = captainName;
    this->isDangerous = isDangerous;
    this->isPrior = false;
}
    
class Work
{
protected:
    string shipName;
    int startTime;
    char workType;
    Ship* ship;
    int pierCostTime;
	int costTime;
public:
    Work(string shipName, int startTime, int costTime, char workType);
    virtual int getEndPier() {};
    virtual int getStartPier() {};
    virtual int getDock() {};
    virtual int getInCostTime() {};
    virtual int getOutCostTime() {};
    char getType() {return workType;}
    int getCostTime() {return costTime;}
    int getPierCostTime() {return pierCostTime;}
    int getStartTime() {return startTime;}
    string getShipName() {return shipName;}
    void connect(Ship* ship){this->ship = ship;}
    int priorPoint(int b1, int b2, int b3, int b4);
    Ship* getShip(){return this->ship;}
};
   
Work::Work(string shipName, int startTime, int costTime, char workType)
{
    this->shipName = shipName;
    this->startTime = startTime;
    this->pierCostTime = costTime;
    this->workType = workType;
}

int Work::priorPoint(int b1, int b2, int b3, int b4)
{
    int danger = 0, prior = 0;
    if(this->ship->isDanger())
    	danger = 1;
    if(this->ship->getPrior())
    	prior = 1;
    int out = (b1*this->startTime) + (b2*this->costTime) - (b3*danger) - (b4*prior);
}

class InWork : public Work
{
private:
    int dock;
    int endPier;
    int inCostTime;
    bool isSecond;
public:
    InWork(string shipName, int startTime, int costTime, char workType, int dock, int endPier, int inCostTime):
        Work(shipName, startTime, costTime, workType) {this->dock = dock; this->endPier = endPier; this->inCostTime = inCostTime; 
		this->costTime = inCostTime + this->pierCostTime; isSecond = false;}
    int getEndPier() {return endPier;}
    int getDock() {return dock;}
    int getInCostTime() {return inCostTime;}
}; 

class OutWork : public Work
{
private:
    int dock;
    int startPier;
    int outCostTime;
    bool isSecond;
public:
    OutWork(string shipName, int startTime, int costTime, char workType, int dock, int startPier, int outCostTime):
        Work(shipName, startTime, costTime, workType) {this->dock = dock; this->startPier = startPier; this->outCostTime = outCostTime;
		this->costTime = outCostTime + this->pierCostTime; isSecond = false;}
    int getStartPier() {return startPier;}
    int getDock() {return dock;}
    int getOutCostTime() {return outCostTime;}
};
    
class TransWork : public Work
{
private:
    int startPier;
    int endPier;
public:
    TransWork(string shipName, int startTime, int costTime, char workType, int startPier, int endPier):
        Work(shipName, startTime, costTime, workType) {this->startPier = startPier; this->endPier = endPier;
		this->costTime = this->pierCostTime;}
    int getStartPier() {return startPier;}
    int getEndPier() {return endPier;}
};
    
int main ()
{
    char shipFile[100];
    char workFile[100];
    char priorityFile[100];
    //string shipFile = "ShipSample.txt";
    //string workFile = "WorkSample";
    char useless;
    int n = 0 , b1 = 0, b2 = 0, b3 = 0, b4 = 0;
	//int fuck[100] = {30, 12, 10, 10, 25, 10};
    cin >> n >> useless >> b1 >> useless >> b2 >> useless >> b3 >> useless >> b4;
    cin >> shipFile;
    cin >> workFile;
	cin >> priorityFile;
	
	vector<string> priorName;
	
	ifstream priorityData(priorityFile);
	
	if(priorityData)
	{
		while(!priorityData.eof())
		{
			string temp;
			getline(priorityData, temp);
			
			priorName.push_back(temp);
		}
	}
	
	
	string shipName;
    int weight;
    string country;
    string captainName;
    char tempDangerous;
    bool isDangerous;
	
    int numOfShip = 0; 
    Ship** ships = new Ship* [1000];
        
    ifstream shipData(shipFile);
        
    if(shipData)
    {
        while(!shipData.eof())
        {
            getline(shipData, shipName, ',');
            
            shipData >> weight;
            shipData.ignore();
                
            getline(shipData, country, ',');
                
            getline(shipData, captainName, ',');
                 
                 
            shipData >> tempDangerous;
            if(tempDangerous=='Y')
                isDangerous = true;
            else
                isDangerous = false;
            shipData.ignore();
             
            ships[numOfShip] = new Ship(shipName, weight, country, captainName, isDangerous);
            
            if(isIn(priorName, country))
            {
            	ships[numOfShip]->bePrior();
			}
            //cout << shipName;
            numOfShip++;
        }
    }
    
    
    //cout << endl << endl;
    int tempHour = 0;
    int tempMinute = 0;
    int startTime = 0;
    int costTime1 = 0;
    int costTime2 = 0;
    char workType;
    int startPier = 0;
    int endPier = 0;
    int dock = 0;
    string temp;
        
    int numOfWork = 0; 
    int Cnt = 0;
    
    Work** works = new Work* [1000];
    
    ifstream workData(workFile);
    
    if(workData)
    {
        while(!workData.eof())
        {
        	//cout << numOfWork;
            getline(workData, shipName, ',');
            //cout << shipName << " ";
                
            workData >> tempHour;
            workData.ignore();
            
            //cout << tempHour;
            workData >> tempMinute;
            startTime = (tempHour*60) + tempMinute;
            //cout << startTime << " ";
                
            workData.ignore();
            
            workData >> costTime1;
            workData.ignore();
            
			getline(workData, temp, ',');
			//cout << temp <<endl;
			//cout << temp << endl;
			if(temp[0] == 'T')
			{
				
				workData >> startPier;
				workData.ignore();
				
				workData >> endPier;
				workData.ignore();
				
				works[numOfWork] = new TransWork(shipName, startTime, costTime1, 'T', startPier, endPier);
			}
            
            else
            {
            	costTime2 = stoi(temp);
            
            	workData >> workType;
            	workData.ignore();
            	
            	if(workType == 'I')
            	{
	            	workData >> dock;
	            	workData.ignore();
	            	//cout << dock;
	            	
	            	workData >> endPier;
	                workData.ignore();
	                //cout << endPier;
	                works[numOfWork] = new InWork(shipName, startTime, costTime2, workType, dock, endPier, costTime1);
	                
				}
				else if(workType == 'O')
				{
					workData >> dock;
	            	workData.ignore();
	            	
	            	workData >> startPier;
	                workData.ignore();
	                
	                works[numOfWork] = new OutWork(shipName, startTime, costTime1, workType, dock, endPier, costTime2);
				}
			}
			
            numOfWork++;
            //cout << workType << endl;
        }
    }
    
    for(int i = 0;i<numOfWork;i++)
	{
		for(int j = 0;j<numOfShip;j++)
		{
			
			if(works[i]->getShipName() == ships[j]->getShipName())
			{
				works[i]->connect(ships[j]);
				break;
			}
			
		}
	}
    
    
    int inDelay1 = 0, outDelay1 = 0, inDelay2 = 0, outDelay2 = 0;
    
    int workPri[1000] = {0};
    int v[1000] = {0};
      
    for(int i = 0;i<numOfWork;i++)
    {
    	
        int min = 200000000;
        for(int j = 0;j<numOfWork;j++)
        {
            if(v[j]==1)
                continue;
                    
            if(works[j]->priorPoint(b1,b2,b3,b4)<min)
            {
                workPri[i] = j;
                min = works[j]->priorPoint(b1,b2,b3,b4);
            }
            else if(works[j]->priorPoint(b1,b2,b3,b4)==min && (works[j]->getShip()->isDanger()) && (!works[workPri[i]]->getShip()->isDanger()))
            {
            	workPri[i] = j;
            }
            else if(works[j]->priorPoint(b1,b2,b3,b4)==min && (works[j]->getShip()->isDanger() == works[workPri[i]]->getShip()->isDanger()))
            {
            	if(works[j]->getShip()->getPrior() && !works[workPri[i]]->getShip()->getPrior())
            	{
            		workPri[i] = j;
				}
				else if((works[j]->getShip()->getPrior()) == (works[workPri[i]]->getShip()->getPrior()))
				{
					if(works[j]->getShipName() < works[workPri[i]]->getShipName())
						workPri[i] = j;
				}
			}
        }
        v[workPri[i]] = 1;
        //cout << workPri[i]<<endl;
    }
    //for(int i = 0;i<numOfWork;i++)
    	//cout << workPri[i] << ", " << works[workPri[i]]->priorPoint(b1,b2,b3,b4) << endl;
    
    Period dock1, dock2;
    
    for(int i = 0;i<numOfWork;i++)
    {
    	if(works[workPri[i]]->getType() == 'T')
    	{
    		continue;
    		
		}
		else if(works[workPri[i]]->getType() == 'I')
		{
			
			if(works[workPri[i]]->getDock()==1)
			{
				int where = works[workPri[i]]->getStartTime();
	    		bool stop = false;
	    		
	    		while(!stop)
	    		{
	    			if(dock1.check(where, where + works[workPri[i]]->getInCostTime(), where))
	    			{
	    				stop = true;
	    				dock1.set(where, where + works[workPri[i]]->getInCostTime());
					}
				}
				
				inDelay1 += where - works[workPri[i]]->getStartTime();
			}
			
			else if(works[workPri[i]]->getDock()==2)
			{
				int where = works[workPri[i]]->getStartTime();
	    		bool stop = false;
	    		
	    		while(!stop)
	    		{
	    			if(dock2.check(where, where + works[workPri[i]]->getInCostTime(), where))
	    			{
	    				stop = true;
	    				dock2.set(where, where + works[workPri[i]]->getInCostTime());
					}
				}
				
				inDelay2 += where - works[workPri[i]]->getStartTime();
			}
			
		}
		
		else if(works[workPri[i]]->getType() == 'O')
		{
			if(works[workPri[i]]->getDock()==1)
			{
				int where = works[workPri[i]]->getStartTime() + works[workPri[i]]->getPierCostTime();
	    		bool stop = false;
	    		
				while(!stop)
				{
					if(dock1.check(where, where + works[workPri[i]]->getOutCostTime(), where))
	    			{
	    				stop = true;
	    				dock1.set(where, where + works[workPri[i]]->getOutCostTime());
					}
				}
				outDelay1 += where - works[workPri[i]]->getStartTime() - works[workPri[i]]->getPierCostTime();
			}
			
			else if(works[workPri[i]]->getDock()==2)
			{
				
				int where = works[workPri[i]]->getStartTime() + works[workPri[i]]->getPierCostTime();
	    		bool stop = false;
	    		
				while(!stop)
				{
					if(dock2.check(where, where + works[workPri[i]]->getOutCostTime(), where))
	    			{
	    				stop = true;
	    				dock2.set(where, where + works[workPri[i]]->getOutCostTime());
					}
				}
				outDelay2 += where - works[workPri[i]]->getStartTime() - works[workPri[i]]->getPierCostTime();
			}
		}
		//cout << SPTdelay << endl;
	}
	//dock1.print();
    cout << inDelay1 << " " << outDelay1 << " " << inDelay2 << " " << outDelay2;
    //cout << "75 5 0 0";
    
    shipData.close();
    workData.close();
    priorityData.close();
    for(int i = 0;i<numOfShip;i++)
    	delete ships[i];
	for(int i = 0;i<numOfWork;i++)
		delete works[i];
	
    return 0;   
}

bool isIn(vector<string> a, string b)
{
	string temp;
	if(b.find(" ",0)!=string::npos)
	{
		temp.append(1, b[0]);
		temp.append(1,b[b.find(" ",0)+1]);
		int pos = b.find(" ",0)+1;
		while(b.find(" ",pos)!=string::npos)
		{
			temp.append(1,b[b.find(" ",pos)+1]);
			pos = b.find(" ",pos)+1;
		}
		b = temp;
	}
	for(int i = 0;i<a.size();i++)
	{
		if(a[i]==b)
			return true;
	}
	return false;
}
