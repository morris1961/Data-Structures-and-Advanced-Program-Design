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
	int itemCnt;
public:
	Stack() {topPtr = nullptr; itemCnt = 0;}
	~Stack();
	bool isEmpty() const {return (topPtr == nullptr);}	
	bool push(const Item& anItem);
	bool pop();
	Item peek() const throw(logic_error);
	void print() const;
	int getCnt() const {return this->itemCnt;}
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
	itemCnt++;
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
		itemCnt--;
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
	int n = 0;
	cin >> n;
	
	int** net = new int *[n];
	for(int i = 0; i < n; i++)
		net[i] = new int [n];
	for(int i = 0; i < n; i++)
		for(int j = 0 ; j < n; j++)
			net[i][j] = 0;
			
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> net[i][j];
//	for(int i = 0; i < n; i++)
//	{
//		for(int j = 0; j < n; j++)
//			cout << net[i][j] << " ";
//		cout << endl;
//	}

	int Cnt = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = i; j < n; j++)
			if(net[i][j] == 1)
				Cnt++;
	}
//	cout << Cnt;

	if(Cnt >= n)
	{
		cout << 0;
	}
	else if(Cnt < n)
	{
		int second = 0;
		int **fnet = new int*[n];
		for(int i = 0; i < n; i++)
		{
			fnet[i] = new int[n];
			for(int j = 0; j < n; j++)
				fnet[i][j] = net[i][j];
		}
		
		int max = 0;
		vector<int> came;
		Stack<int> dfs;
		dfs.push(0);
		came.push_back(0);
		while(!dfs.isEmpty())
		{
			int cur = dfs.peek();
			int count = 0;
			for(int i = 0; i < n; i++)
			{
				if(fnet[cur][i] == 1)
				{
					bool repeat = false;
					for(int j = 0; j < came.size(); j++)
					{
						if(i == came[j])
						{
							repeat = true;
							break;
						}
					}
					if(repeat)
						count++;
					else
					{
//						fnet[i][cur] = 0;
						dfs.push(i);
						came.push_back(i);
						break;
					}
				}
				else
					count++;
			}
			if(count == n)
			{
				if(max < dfs.getCnt())
				{
					max = dfs.getCnt();
					second = dfs.peek();
				}
				dfs.pop();
			}
//				dfs.print();
		}
		

//		for(int i = 0; i < n; i++)
//		{
//			fnet[i] = new int[n];
//			for(int j = 0; j < n; j++)
//				fnet[i][j] = net[i][j];
//		}
		
//		cout << second << " "; 
		int ans = 0;
		came.clear();
		dfs.push(second);
		came.push_back(second);
		while(!dfs.isEmpty())
		{
			bool firstPush = true;
			int cur = dfs.peek();
			int count = 0;
			for(int i = 0; i < n; i++)
			{
				if(fnet[cur][i] == 1)
				{
					bool repeat = false;
					for(int j = 0; j < came.size(); j++)
					{
						if(i == came[j])
						{
							repeat = true;
							break;
						}
					}
					if(repeat)
						count++;
					else
					{
//						fnet[i][cur] = 0;
						dfs.push(i);
						came.push_back(i);
						break;
					}
				}
				else
					count++;
			}
			if(count == n)
			{
				if(ans < dfs.getCnt())
					ans = dfs.getCnt();
				dfs.pop();
			}
//				dfs.print();
		}
//		cout << ans;
		

		for(int i = 0; i < n; i++)
		{
			delete [] fnet[i];
		}
		delete [] fnet;
		
		if(ans % 2 == 1)
			ans = ans+1;
		else if(ans % 2 == 0)
			ans = ans + 2;
		cout << 1 << " " << ans/2;
	}
		
	
	
	return 0;
}
