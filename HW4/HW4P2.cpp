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
	string input;
	cin >> input;
	
	string numS = "";
	Stack<int> operand;
	Stack<char> operater;
	
	for(int i = 0; i < input.size(); i++)
	{
		char com = input[i];
		if(com != '+' && com != '-' && com != '*' && com != '/')
		{
			numS += input[i];
			if(i == input.size() - 1)
				operand.push(stoi(numS));
		}
		else
		{	
			operand.push(stoi(numS));
//			cout << "from" << endl;
//			operand.print();
//			operater.print();
//			cout << "to" << endl;
			try
			{
				while(((com == '+' || com == '-') && (operater.peek() == '+' || operater.peek() == '-' || operater.peek() == '*' || operater.peek() == '/'))
					|| ((com == '*' || com == '/') && (operater.peek() == '*' || operater.peek() == '/')))
				{
					int num1 = operand.peek();
					operand.pop();
					int num2 = operand.peek();
					operand.pop();
					switch (operater.peek())
					{
						case '+':
						{
							operand.push(num2 + num1);
							break;
						}
						case '-':
						{
							operand.push(num2 - num1);
							break;
						}
						case '*':
						{
							operand.push(num2 * num1);
							break;
						}
						case '/':
						{
							operand.push(num2 / num1);
							break;
						}
					}
					operater.pop();
				}
					operater.push(com);
			}
			catch (logic_error e)
			{
				operater.push(com);
			}
			numS.clear();
			operand.print();
//			operater.print();
		} 
	}
	
	while(!operater.isEmpty())
	{
		int num1 = operand.peek();
		operand.pop();
		int num2 = operand.peek();
		operand.pop();
		switch (operater.peek())
		{
			case '+':
			{
				operand.push(num2 + num1);
				break;
			}
			case '-':
			{
				operand.push(num2 - num1);
				break;
			}
			case '*':
			{
				operand.push(num2 * num1);
				break;
			}
			case '/':
			{
				operand.push(num2 / num1);
				break;
			}
		}
		operater.pop();
//		operater.print();
	}
	cout << operand.peek();
	
	return 0;
}
