#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

template <typename Item>
class QueueInterFace
{
public:
	/*
	@return if the queue is empty
	*/
	virtual bool isEmpty() const = 0;
	/*
	@post add newEntry to the last of the queue
	@input a item to be added
	@return if the addition is successful 
	*/	
	virtual bool enqueue(const Item& newEntry) = 0;
	/*
	@pre the queue is not empty
	@post delete the first added item in the queue
	@return if the removal is successful
	*/
	virtual bool dequeue() = 0;
	/*
	@pre the queue is not empty
	@return the first added item 
	*/
	virtual Item peekFront() const = 0;
};

template <typename Item>
class Node
{
private:
	Item item;
	Node<Item>* next;
public:
	Node() {this->next = nullptr;}
	Node(const Item& anItem) {this->item = anItem; this->next = nullptr;}
	Node(const Item& anItem, Node<Item>* nextPtr) {this->item = anItem; this->next = nextPtr;}
	void setItem(const Item& anItem) {this->item = anItem;}
	void setNext(Node<Item>* nextPtr) {this->next = nextPtr;}
	Item getItem() const {return this->item;}
	Node<Item>* getNext() const {return this->next;}
};

template <typename Item>
class Queue : public QueueInterFace<Item>
{
private:
	int itemCnt;
	Node<Item>* headptr;
public:
	Queue();
	~Queue();
	bool isEmpty() const;
	bool enqueue(const Item& newEntry);
	bool dequeue();
	Item peekFront() const throw (logic_error);
	void clear();
	void print() const;
};

template <typename Item>
Queue<Item>::Queue() : itemCnt(0), headptr(nullptr)
{
}

template <typename Item>
Queue<Item>::~Queue()
{
	while(!this->isEmpty())
		this->dequeue();
}

template <typename Item>
bool Queue<Item>::isEmpty() const
{
	return (this->itemCnt == 0);
}

template <typename Item>
bool Queue<Item>::enqueue(const Item& newEntry)
{
	Node<Item>* newptr = new Node<Item>(newEntry);
	if(this->isEmpty())
	{
		headptr = newptr;
	}
	else
	{
		Node<Item>* cur = this->headptr;
		for(int i = 0; i < this->itemCnt-1; i++)
			cur = cur->getNext();
		cur->setNext(newptr);
	}
	this->itemCnt++;
	return true;
}

template <typename Item>
bool Queue<Item>::dequeue()
{
	if(this->isEmpty())
	{
		return false;
	}
	else
	{
		Node<Item>* todelete = this->headptr;
		this->headptr = this->headptr->getNext();
		delete todelete;
		this->itemCnt--;
		return true;
	}
}

template <typename Item>
Item Queue<Item>::peekFront() const throw (logic_error)
{
	if(!this->isEmpty())
		return this->headptr->getItem();
	else 
		throw logic_error("empty");
}

template <typename Item>
void Queue<Item>::print() const
{
	if(this->isEmpty())
		cout << "Empty!" << endl;
	else
	{
		Node<Item>* cur = this->headptr;
		for(int i = 0; i < this->itemCnt-1; i++)
		{
			cout << cur->getItem() << ",";
			cur = cur->getNext();
		}
		cout << cur->getItem() << endl;
	}
}

template <typename Item>
void Queue<Item>::clear()
{
	while(!this->isEmpty())
		this->dequeue();
}

template <typename Item>
class PriQueue : public Queue<Item>
{
public:
	PriQueue();
	bool enqueue(const Item& newEntry);
};

template <typename Item>
PriQueue<Item>::PriQueue() : Queue<Item>()
{
}

template <typename Item>
bool PriQueue<Item>::enqueue(const Item& newEntry)
{
	Node<Item>* newptr = new Node<Item>(newEntry);
	if(this->isEmpty())
	{
		this->headptr = newptr;
	}
	else
	{
		Node<Item>* cur = this->headptr;
		Node<Item>* pre = nullptr;
		for(int i = 0; i < this->itemCnt-1; i++)
		{
			//assume there are not two same start time
			if(cur->getItem() < newEntry)
			{
				break;
			}
			pre = cur;
			cur = cur->getNext();
		}
		if(cur == this->headptr)
		{
			newptr->setNext(this->headptr);
			this->headptr = newptr;
		}
		else
		{
			newptr->setNext(pre->getNext());
			pre->setNext(newptr);
		}
	}
	this->itemCnt++;
	return true;
}

class Event
{
private:
	int start;
	string name;
	int process;	
public:
	Event();
	Event(int start, string name, int process);
	friend ostream& operator<<(ostream& os, const Event& event)
	{
		os << event.name << " " << event.process;
		return os;
	}
	bool operator < (const Event& event) {return (this->start < event.start);}
	bool operator > (const Event& event) {return (this->start > event.start);}
	int getStart() const {return this->start;}
	string getName() const {return this->name;}
	int getProcess() const {return this->process;}
	void execute(int time){this->process -= time;}
};

Event::Event() : start(0), name(""), process(0)
{
}

Event::Event(int start, string name, int process) : start(start), name(name), process(process)
{
}

void Sort(Event* array, int length)
{
	for (int i = length - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
        {
        	if (array[j].getStart() > array[j + 1].getStart())
        	{
        		Event temp1 = array[j];
        		array[j] = array[j+1];
        		array[j+1] = temp1;
			}
		}
            
}

int main()
{
	int n = 0;
	cin >> n;
	int* limit = new int[n-1];
	for(int i = 0; i < n-1; i++)
	{
		cin >> limit[i];
	}
	
	Queue<Event>** queue = new Queue<Event>* [n];
	for(int i = 0; i < n; i++)
		queue[i] = new Queue<Event>();
	Event* event = new Event[500];
	int count = 0;
	int lastStop = 0;
	
	string input;
	cin.ignore();
	while(getline(cin, input))
	{//assume the input order is from the lower to the higher
		if(input.find(".exe") != string::npos)
		{
			int start = stoi(input.substr(0, input.find(" ")));
			string name = input.substr(input.find(" ")+1, input.rfind(" ") - input.find(" ")-1);
			int process = stoi(input.substr(input.rfind(" ")+1, input.length() - input.rfind(" ")));
			Event e(start, name, process);
			event[count] = e;
			count++;
			Sort(event, count);
//			cout << start << " " << name << " " << process << endl;
		}
		else if(input.find("ps") != string::npos)
		{
			Event* toPrint = new Event[count];
			for(int i = 0; i < count; i++)
				toPrint[i] = event[i];
			int end = stoi(input.substr(0, input.find(" ")));
			queue[0]->enqueue(event[0]);
			int now = event[0].getStart();
			long long int curL = 0;
			int nowQ = 0, nowE = 0;
			Queue<Event>* curQ = queue[0];
			
			while(now != end)
			{
				for(int i = 0; i < n; i++)
				{
					if(!queue[i]->isEmpty())
					{
						if(i != n-1)
							curL = limit[i];
						else
							curL = 999999;
						curQ = queue[i];
						nowQ = i;
						break;
					}
				}
//				cout << nowQ << " ";
//				curQ->print();
				try
				{
					Event curE = curQ->peekFront();
					curQ->dequeue();
					while(curL != 0 && curE.getProcess() != 0)
					{
//						cout << curE << " residual: " << curL <<  endl;
						curE.execute(1);
						now += 1;
						curL -= 1;
						bool priHasExe = false;
						for(int i = 0; i < count; i++)
						{
							if(now == event[i].getStart())
							{
								queue[0]->enqueue(event[i]);
								if(nowQ != 0)
									priHasExe = true;
								break;
							}
						}
						if(priHasExe || now == end)
							break;
					}
					if(curE.getProcess() == 0)
						;
					else if(curL == 0) 
						queue[nowQ+1]->enqueue(curE);
					else
						queue[nowQ]->enqueue(curE);
//					cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
//					for(int i = 0; i < n; i++)
//					{
//						cout << i << ": ";
//						queue[i]->print();
//					}
//					cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
					for(int i = 0; i < count; i++)
					{
						if(curE.getName() == toPrint[i].getName())
						{
							toPrint[i] = curE;
//							cout << "--------------------------" << endl;
//							for(int i = 0; i < count; i++)
//								cout << toPrint[i] << endl;
//							cout << "--------------------------" << endl;
							break;
						}
					} 
				}
				catch (logic_error e)
				{
					bool haveNew = false;
					for(int i = 0; i < count; i++)
					{
						if(event[i].getStart() >= now)
						{
							queue[0]->enqueue(event[i]);
							haveNew = true;
							now = event[i].getStart();
							break;
						}
					}
					if(!haveNew)
						break;
				}
			}
			for(int i = 0; i < count; i++)
			{
				if(end < toPrint[i].getStart())
					break;
				cout << toPrint[i] << endl;
			}
			delete [] toPrint;
			for(int i = 0; i < n; i++)
				queue[i]->clear();
		}
	} 
	
	delete [] limit;
	delete [] event; 
	for(int i = 0; i < n; i++)
		delete queue[i];
	delete [] queue;
	return 0;
}
