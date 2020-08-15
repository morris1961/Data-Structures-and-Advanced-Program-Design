#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
using namespace std;

template <typename Item>
class StackInterFace
{
public:
	/*
	@return if the stack is empty
	*/
	virtual bool isEmpty() const = 0;
	/*
	@pre the stack shouldn't be empty 
	@post erase the last item of the stack
	@return it the removal is successed
	*/
	virtual bool pop() = 0;
	/*
	@pre the stack shouldn't be empty 
	@return it the last item of the stack
	*/
	virtual Item peek() const = 0;
	/*
	@post put a item to the back of the stack
	@return it the last item of the stack
	*/
	virtual bool push(const Item& anItem) = 0;
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
class Stack : public StackInterFace<Item>
{
private:
	Node<Item>* topPtr;
public:
	Stack() {topPtr = nullptr;}
	~Stack();
	bool isEmpty() const {return (topPtr == nullptr);}	
	bool push(const Item& anItem);
	bool pop();
	Item peek() const throw(logic_error);
	void print() const;
};

template <typename Item>
Stack<Item>::~Stack()
{
	while(!this->isEmpty())
		this->pop();
}

template <typename Item>
bool Stack<Item>::push(const Item& anItem)
{
	Node<Item>* nPtr = new Node<Item> (anItem, this->topPtr);
	this->topPtr = nPtr;
	return true;
}

template <typename Item>
bool Stack<Item>::pop()
{
	bool result = false;
	if(!this->isEmpty())
	{
		result = true;
		Node<Item>* oPtr = this->topPtr;
		topPtr = oPtr->getNext();
		delete oPtr;
	}
	return result;
}

template <typename Item>
Item Stack<Item>::peek() const throw(logic_error)
{
	if(this->topPtr != nullptr)
		return this->topPtr->getItem();
	else
		throw logic_error("nothing!");
}

template <typename Item>
void Stack<Item>::print() const
{
	if(this->isEmpty())
		cout << "EMPTY!!" << endl;
	else
	{
		Stack stacktoPrint;
		Node<Item>* nodePtr = this->topPtr;
		while(nodePtr != nullptr)
		{
			stacktoPrint.push(nodePtr->getItem());
			nodePtr = nodePtr->getNext();
		}
		nodePtr = stacktoPrint.topPtr;
		cout << nodePtr->getItem();
		while(nodePtr->getNext() != nullptr)
		{
			nodePtr = nodePtr->getNext();
			cout << "," << nodePtr->getItem();
		}
		cout << endl;
	}
}

int main()
{
	string firstLine = "";
	cin >> firstLine;
	int n = (firstLine.size() + 1)/2;
	bool** net = new bool *[n];
	for(int i = 0; i < n; i++)
		net[i] = new bool [n];
	for(int i = 0; i < n; i++)
		for(int j = 0 ; j < n; j++)
			net[i][j] = false;
			
	for(int i = 0; i < n; i++)
		net[0][i] = firstLine[i*2] == '1' ? true:false;
	for(int i = 1; i < n; i++)
	{
		cin >> firstLine;
		for(int j = 0; j < n; j++)
		{
			net[i][j] = firstLine[j*2] == '1' ? true:false;
		}
	}
	
//	for(int i = 0; i < n; i++)
//	{
//		for(int j = 0; j < n; j++)
//			cout << net[i][j] << " ";
//		cout << endl;
//	}
		
	Stack<int> dfs;
	dfs.push(1);
	for(int i = 0; i < n; i++)
		net[i][0] = false;
	dfs.print();
	
	vector<int> came;
	bool keep = true;
	while(keep && !dfs.isEmpty())
	{
		int cur = dfs.peek()-1;
		int count = 0;
		for(int i = 0; i < n; i++)
		{
			if(net[cur][i])
			{
				bool repeat = false;
				for(int j = 0; j < came.size(); j++)
				{
					if(i+1 == came[j])
					{
						repeat = true;
						break;
					}
				}
				if(repeat)
					count++;
				else
				{
					came.push_back(i+1);
					dfs.push(i+1);
				}
			}
			else
				count++;
		}
		if(count == n)
		{
			dfs.pop();
//			dfs.print();
		}
		else
		{
			dfs.print();
		}
		try
		{
			if(dfs.peek() == n)
				keep = false;
		}
		catch(logic_error e)
		{
			break;
		}
	}
	
	if(keep)
		cout << 0;
	else
		cout << 1;	
	
	return 0;
}
