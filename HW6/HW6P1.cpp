#include <iostream>
#include <cmath>
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
	Item peekFront() const;
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
		todelete = nullptr;
		this->itemCnt--;
		return true;
	}
}

template <typename Item>
Item Queue<Item>::peekFront() const
{
	return this->headptr->getItem();
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
void Sort(Item* arrive, Item* portime, int n)
{
	for (int i = n - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
        {
        	if (arrive[j] > arrive[j + 1])
        	{
        		Item temp1 = arrive[j];
        		arrive[j] = arrive[j+1];
        		arrive[j+1] = temp1;
        		Item temp2 = portime[j];
        		portime[j] = portime[j+1];
        		portime[j+1] = temp2;
			}
		}
            
}

int main()
{
	Queue<double> arrQ, porQ;
	int n = 0;
	double u = 0, l = 0;
	cin >> n >> l >> u;
	double theorem = l/(u*(u-l));
	double *arrive = new double [n], *portime = new double [n];
	for(int i = 0; i < n; i++)
	{
		cin >> arrive[i] >> portime[i];
	}
	Sort(arrive, portime, n);
	for(int i = 0; i < n; i++)
	{
		arrQ.enqueue(arrive[i]);
		porQ.enqueue(portime[i]);
	}
//	arrQ.print();
//	porQ.print();
	double cur = 0, delay = 0;
	while(!arrQ.isEmpty() && !porQ.isEmpty())
	{
		double cust = arrQ.peekFront(), porcess = porQ.peekFront();
		if(cust >= cur)
		{
			cur = cust + porcess;
		}
		else if(cust < cur)
		{
			delay += cur - cust;
			cur += porcess;
		}
		arrQ.dequeue();
		porQ.dequeue();
//		cout << delay << endl;
	}
	cout << delay << endl;
	cout << round(((delay/n) - theorem)/theorem * 100);
	return 0;
}
