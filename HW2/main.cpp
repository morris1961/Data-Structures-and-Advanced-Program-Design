#include <iostream>     //input, output
#include <string>
#include <sstream>        //read file
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

bool ertDebugMode = false;
bool sptDebugMode = false;

//forward declaration
class Ship;
class ShipList;
class Task;
class TaskList;


//Time struct
struct Time
{
    int hour;
    int min;
};

//parse HH:MM string time to integer minutes formate
Time parseTime(string sTime){
    string delimiter = ":";
    
    size_t pos = 0;
    string token;
    pos = sTime.find(delimiter);
    token = sTime.substr(0, pos);
    int hour  = stoi(token);
    sTime.erase(0, pos + delimiter.length());
    int minute = stoi(sTime);
    
    return {hour, minute};
}

//parse integer minutes formate time to HH:MM string time
string parseTime(int time)
{
    string hour = ((time/60) <10) ? ("0"+to_string(time/60)) : to_string(time/60);
    string minute = ((time%60) <10) ? ("0"+to_string(time%60)) : to_string(time%60);
    return hour + ":" + minute;
}

class Ship
{
private:
    string shipName;
    int shipWeight;
    string countryName;
    string captainName;
    bool isLoadedDanger;
public:
    //constructor
    Ship(string sName, int sWeight, string country, string cName, bool isDanger);
    //get ship information
    string getShipName(){return shipName;};
    virtual int getShipWeight(){return shipWeight;};
    string getCountryName(){return countryName;};
    string getCaptainName(){return captainName;};
    bool getIsLoadedDanger(){return isLoadedDanger;};
    //print
    void printShipInfo();
};


Ship::Ship(string sName, int sWeight, string country, string cName, bool isDanger)
{
    shipName = sName;
    shipWeight = sWeight;
    countryName = country;
    captainName = cName;
    isLoadedDanger = isDanger;
}


void Ship::printShipInfo()
{
    cout << shipName << "\t" << shipWeight << "\t" << countryName << "\t" << captainName << "\t" << isLoadedDanger << endl;
}

class ShipList
{
private:
    int shipCapacity;
    int shipNum;
    Ship **shipList;
public:
    ShipList(int numOfShips);
    ~ShipList();
    void addShip(string shipName, int shipWeight, string countryName, string captainName, bool isLoadedDanger);
    Ship* getShipByShipName(string shipName);
    void printShips();
    Ship& operator[](int index) {return *shipList[index];}
};

//constructor
ShipList::ShipList(int numOfShips)
{
    shipNum = 0;
    shipCapacity = numOfShips;
    shipList = new Ship*[numOfShips];
    //initialize nullptr
    for(int i=0; i<shipCapacity; i++)
    {
        shipList[i] = nullptr;
    }
}

//destructor
ShipList::~ShipList()
{
    for(int i=0; i<shipNum; i++)
    {
        delete shipList[i];
        shipList[i] = nullptr;
    }
}

//print every ship's info in the list
void ShipList::printShips()
{
    cout << "***************************************" << endl;
    for(int i=0; i<shipNum; i++)
        shipList[i]->printShipInfo();
    cout << "***************************************" << endl;
}

//add new Ship into shipList
void ShipList::addShip(string shipName, int shipWeight, string countryName, string captainName, bool isLoadedDanger){
    if(shipNum<shipCapacity)
    {
        Ship* newShip = new Ship(shipName, shipWeight, countryName, captainName, isLoadedDanger);
        shipList[shipNum] = newShip;
        shipNum++;
    }
}

//search ship from shipList
Ship* ShipList::getShipByShipName(string shipName)
{
    for(int i=0; i<shipNum; i++)
    {
        if(shipList[i]->getShipName().compare(shipName) == 0)
        {
            return shipList[i];
        }
    }
    return nullptr;
}

class Task
{
protected:
    Ship* shipPtr;
    int startTime;
    string type;        //I:�i��, T:���y, O:�X��
    int port;
    int startPier;
    int destPier;
    int realStartTime;
    bool isNight;
    bool vacancy;
public:
    Task(Ship* sPtr, string sTime, string type, int param1, int param2, bool vac);
    //get ship info
    string getShipName(){return shipPtr->getShipName();};
    int getStartTime(){return startTime;};
    string getType(){return type;};
    int getPort(){return port;};
    int getRealStartTime(){return realStartTime;}
    int getWaitingTime(){return realStartTime - startTime;}
    bool getIsNight(){return isNight;}
    bool getVacavcy(){return vacancy;}
    //set ship info
    void setRealStartTime(int rTime){realStartTime = rTime;}
    int movingDST(int t1, int t2, int t3);
    bool getVacancy(){return vacancy;}
    Ship getShipPtr(){return *shipPtr;}
    //print ship info
    void printTaskInfo();
};

//constructor
Task::Task(Ship* sPtr, string sTime, string aType, int param1, int param2, bool vac)
{
    Time parsedTime = parseTime(sTime);
    
    shipPtr =  sPtr;
    startTime = (parsedTime.hour*60) + parsedTime.min;
    isNight = (startTime <= 360 || startTime >= 1080) ? true : false;
    type = aType;
    vacancy = vac;
    realStartTime = 0;
    
    if(type=="I")
    {
        port = param1;
        startPier = 0;
        destPier = param2;
        realStartTime = 0;
    }
    else if(type=="O")
    {
        port = param1;
        startPier = param2;
        destPier = 0;
        realStartTime = 0;
    }
    else if(type=="T")
    {
        port = 0;
        startPier = param1;
        destPier = param2;
        realStartTime = startTime;
    }
};

int Task::movingDST(int t1, int t2, int t3)
{
    if(type == "T")
    {
        if(startPier % 2 != destPier % 2)
            return t3 + ((startPier % 2 == 0) ? abs(destPier + 1 - startPier) / 2 * t2 : abs(startPier + 1 - destPier) / 2 * t2);
    }
    else if(port == 1)
    {
        return (-(startPier + destPier) % 2 + 1) * t3 + (startPier + destPier + 1) / 2 * t2;
    }
    return -(startPier + destPier) / 2 + 4;
}


//print task information
void Task::printTaskInfo()
{
    cout << shipPtr->getShipName() << "\t" << parseTime(startTime) << "\t" << type << "\t";
    cout << parseTime(realStartTime) << "\t" << realStartTime- startTime << endl;
    cout << isNight << endl;
    /*if(type=="I")
     {
     cout << port << "\t" << destPier << endl;
     }
     else if(type=="O")
     {
     cout << port << "\t" << startPier << endl;
     }
     else if(type=="T")
     {
     cout << startPier << "\t" << destPier << endl;
     }  */
}


class TaskList
{
private:
    //array information
    Task **taskList;
    int taskCapacity;
    int taskNum;
    
    //function
    void swap(Task** swapList, int i, int j);
public:
    TaskList(int numOfTasks);
    ~TaskList();
    //void addTask()
    void addTask(Ship* shipPtr, string sTime, string type, int param1, int param2, bool vac);
    int getTaskNum(){return taskNum;}
    
    void printTasks();
    Task& operator[](int index) {return *taskList[index];}
    
};

//constructor: create array of task
TaskList::TaskList(int numOfTasks)
{
    taskNum = 0;
    taskCapacity = numOfTasks;
    taskList = new Task*[numOfTasks];
}

//destructor: delete task in taskList
TaskList::~TaskList()
{
    for(int i=0; i<taskNum; i++)
    {
        delete taskList[i];
        taskList[i] = nullptr;
    }
}

//swap task
void TaskList::swap(Task** swapList, int i, int j)
{
    Task* temp = swapList[i];
    swapList[i] = swapList[j];
    swapList[j] = temp;
}

//print each task's infomation in taskList
void TaskList::printTasks()
{
    cout << "***********************************************" << endl;
    for(int i=0; i<taskNum; i++){
        taskList[i]->printTaskInfo();
    }
    cout << "***********************************************" << endl;
}

//add task into taskList
void TaskList::addTask(Ship* shipPtr, string sTime, string type, int param1, int param2, bool vac)
{
    if(taskNum<taskCapacity)
    {
        Task* newTask = new Task(shipPtr, sTime, type, param1, param2, vac);
        taskList[taskNum] = newTask;
        taskNum++;
    }
}



int main(){
    
    int m =0, t1 =0, t2 =0, t3 =0;
    double a0 =0, a1 =0, a2 =0, a3 =0, a4 =0, b0 =0, b1 =0, b2 =0, b3 =0, b4 =0, c0 =0, c1 =0, c2 =0, c3 =0, c4 =0;
    string line;
    string shipFileName;
    string taskFileName;
    cin >> line >> shipFileName >> taskFileName;
    
    string delimiter = ",";
    size_t last = 0;
    size_t next = 0;
    
    next = line.find(delimiter, last);
    m = stoi(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    a0 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    a1 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    a2 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    a3 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    a4 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    b0 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    b1 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    b2 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    b3 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    b4 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    c0 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    c1 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    c2 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    c3 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    c4 = stod(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    t1 = stoi(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    t2 = stoi(line.substr(last, next-last));
    last = next + 1;
    next = line.find(delimiter, last);
    t3 = stoi(line.substr(last, next-last));
    last = next + 1;
    
    //count ship / task numbers
    int shipCount = 0;
    ifstream infile(shipFileName);
    while(!infile.eof())//count how many ships there are in the file
    {
        string temp;
        getline(infile, temp);
        shipCount++;
    }
    infile.close();
    
    int taskCount = 0;
    infile.open(taskFileName);
    while(!infile.eof())//count how many tasks there are in the file
    {
        string temp;
        getline(infile, temp);
        taskCount++;
    }
    infile.close();
//    ifstream infile(shipFileName);
//    int shipCount = count(istreambuf_iterator<char>(infile), istreambuf_iterator<char>(), '\n') +1;
//    infile.close();
//
//    infile.open(taskFileName);
//    int taskCount = count(istreambuf_iterator<char>(infile), istreambuf_iterator<char>(), '\n') +1;
//    infile.close();
    
    //workData** work = new workData* [workAmount];
    ShipList shipList(shipCount);
    TaskList taskList(taskCount);
    cout << shipCount <<" "<< taskCount;
    
    //read ship information
    infile.open(shipFileName);
    while(getline(infile, line))
    {
        string shipName;
        int shipWeight=0;
        string countryName;
        string captainName;
        bool isLoadedDanger=false;
        
        string delimiter = ",";
        size_t last = 0;
        size_t next = 0;
        //shipName
        next = line.find(delimiter, last);
        shipName = line.substr(last, next-last);
        last = next + 1;
        //shipWeight
        next = line.find(delimiter, last);
        shipWeight = stoi(line.substr(last, next-last));
        last = next + 1;
        //countryName
        next = line.find(delimiter, last);
        countryName = line.substr(last, next-last);
        last = next + 1;
        //captainName
        next = line.find(delimiter, last);
        captainName = line.substr(last, next-last);
        last = next + 1;
        //isLoadedDanger
        isLoadedDanger = (line.substr(last)=="Y") ? true : false;
        
        //create ship
        shipList.addShip(shipName, shipWeight, countryName, captainName, isLoadedDanger);
    }
    infile.close();
    //shipList.printShips();
    
    //read task information
    infile.open(taskFileName);
    while(getline(infile, line))
    {
        string shipName;
        string startTime;
        string type;
        int param1 =0;
        int param2 =0;
        
        //string split
        string delimiter = ",";
        size_t pos = 0;
        
        //if(line.find(",,") != string::npos || line.find(",\0"))
        
        //shipName
        pos = line.find(delimiter);
        shipName = line.substr(0, pos);
        cout << "<" << shipName<<">" <<endl;
        line.erase(0, pos + delimiter.length());
        //startTime
        pos = line.find(delimiter);
        
        startTime = line.substr(0, pos);
		cout <<"<"<< startTime << ">" << endl;
        line.erase(0, pos + delimiter.length());
        //type
        pos = line.find(delimiter);
        type = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        //param1
        pos = line.find(delimiter);
        param1 = stoi(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
        //param2
        param2 = stoi(line);
        bool vacancy = (shipName.empty() || startTime.empty() || type.empty() || param1 == 0 || param2 == 0) ? true : false;
        Ship* shipPtr = shipList.getShipByShipName(shipName);
        taskList.addTask(shipPtr, startTime, type, param1, param2, vacancy);
    }
    infile.close();
    //taskList.printTasks();
//    int timePredict = 0;
//    int vacCnt = 0;
//    for(int i = 0; i < taskList.getTaskNum(); i++)
//    {
//        if(taskList[i].getVacancy() == true)
//        {
//            timePredict = -1;
//            vacCnt++;
//        }
//        else
//        {
//            //Ship *ship = shipList.getShipByShipName(taskList[i].getShipName());
//            if(taskList[i].getType().compare("I") == 0)
//            {
//                timePredict = a0 + a1 * taskList[i].movingDST(t1,t2,t3) + a2 * taskList[i].getShipPtr().getShipWeight() + a3 * taskList[i].getShipPtr().getIsLoadedDanger() + a4 * taskList[i].getIsNight();
//            }
//            else if(taskList[i].getType().compare("O") == 0)
//            {
//                timePredict = b0 + b1 * taskList[i].movingDST(t1,t2,t3) + b2 * taskList[i].getShipPtr().getShipWeight() + b3 * taskList[i].getShipPtr().getIsLoadedDanger() + b4 * taskList[i].getIsNight();
//            }
//            else if(taskList[i].getType().compare("T") == 0)
//            {
//                timePredict = c0 + c1 * taskList[i].movingDST(t1,t2,t3) + c2 * taskList[i].getShipPtr().getShipWeight() + c3 * taskList[i].getShipPtr().getIsLoadedDanger() + c4 * taskList[i].getIsNight();
//            }
//        }
//        cout << timePredict;
//        if(i != taskList.getTaskNum() - 1)
//            cout << ",";
//    }
//    cout<<taskList.getTaskNum();
//    cout << endl << vacCnt;
}
/*
200,5,0.0225,0.007,5,5,3,0.015,0.007,4,5,4,0.02,0.005,7,4,7,1,9
ShipSample1.txt
WorkSample1.txt
*/
