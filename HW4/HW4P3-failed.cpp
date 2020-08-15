#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int Gcd(int a, int b)
{
    while(b > 0)
	{
    	int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

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

class Variable
{
private:
	
public:
	int deno;
	int cor;
	string x;
	Variable() {this->cor = 0; this->x = "n"; this->deno = 1;}
	Variable(const Variable& var){this->cor = var.cor; this->x = var.x; this->deno = var.deno;}
	Variable(int num, int deno = 1){this->cor = num; this->x = "n"; this->deno = deno;}
	Variable(int num, string y, int deno){this->cor = num; this->x = y; this->deno = deno;}
	Variable(string y){this->cor = 1; this->x = y; this->deno = 1;}
	void set(int num, int deno = 1){this->cor = num; this->x = "n"; this->deno = deno;}
	void set(int num, string y, int deno){this->cor = num; this->x = y; this->deno = deno;}
	void set(string y){this->cor = 1; this->x = y; this->deno = 1;}
	Variable operator+(const Variable& var) const;
	Variable operator-(const Variable& var) const;
	Variable operator*(const Variable& var) const;
	Variable operator/(const Variable& var) const;	
//	void print() const {cout << cor << x;}
	friend ostream &operator<<( ostream &output, const Variable &var)
	{
		if(var.x != "n")
		{
			string old = var.x;
			int found = var.x.find("n");
			if(found != string::npos)
			{
				old.erase(found, 3);
			}
			if(var.cor == -1)
				output << "-" << old;
			else if(var.cor == 0)
				output << 0;
			else if(var.cor == 1)
				output << old;
			else
				output << var.cor << old;
			if(var.deno != 1)
				output << "/" << var.deno;
		}
		else
		{
			output << var.cor;
		}
	}
};

Variable Variable::operator+(const Variable& var) const
{
	Variable k;
	int found = this->x.find(var.x);
	if(this->x == var.x)
	{
		int num = var.cor + this->cor;
		k.set(num, this->x, 1); 
	}
	else if(found != string::npos)
	{
		string oldS = this->x;
		int found = oldS.find(var.x);
		char a = '+';
		if(found != 0)
			a = oldS[found-1];
		int i = 1;
		string numS = "";
		bool isOne = true;
		while(a != '+' && a != '-')
		{
			isOne = false;
			numS += a;
			i++;
			if(found - i == -1)
				break;
			a = oldS[found - i];
		}
		if(isOne)
			numS = "1";
		reverse(numS.begin(), numS.end());
		
		if(found+1 != oldS.size())
		{
			a = oldS[found + 1];
			if(a == '/')
			{
				string denoS = "";
				i = 2;
				a = oldS[found + i];
				while(a != '+' && a != '-')
				{
					denoS += a;
					i++;
					if(found + i == oldS.size())
						break;
					a = oldS[found + i];
				}
				int num = var.cor * stoi(denoS) + stoi(numS);
				string toInsert = to_string(num);
				if(numS != "1" || var.x == "n")
				{
					oldS.erase(oldS.begin() + found - numS.size(), oldS.begin() + found);
					oldS.insert(found - numS.size(), toInsert);
				}
				else
					oldS.insert(found - numS.size() + 1, toInsert);
				if(oldS.find("-+") != string::npos)
				{
					oldS.erase(oldS.find("-+"),1);
				}
				else if(oldS.find("+-") != string::npos)
				{
					oldS.erase(oldS.find("+-"),1);
				}
				k.set(oldS);
			}
			else
			{
				int num = var.cor + stoi(numS);
				string toInsert = to_string(num);
				if(numS != "1" || var.x == "n")
				{
					oldS.erase(oldS.begin() + found - numS.size(), oldS.begin() + found);
					oldS.insert(found - numS.size(), toInsert);
				}
				else
					oldS.insert(found - numS.size() + 1, toInsert);
				if(oldS.find("-+") != string::npos)
				{
					oldS.erase(oldS.find("-+"),1);
				}
				else if(oldS.find("+-") != string::npos)
				{
					oldS.erase(oldS.find("+-"),1);
				}
				k.set(oldS);
			}
		}
		else
		{
			
			int num = var.cor + stoi(numS);
			string toInsert = to_string(num);
			if(numS != "1" || var.x == "n")
			{
				oldS.erase(oldS.begin() + found - numS.size(), oldS.begin() + found);
				oldS.insert(found - numS.size(), toInsert);
			}
			else
				oldS.insert(found - numS.size() + 1, toInsert);
			if(oldS.find("-+") != string::npos)
			{
				oldS.erase(oldS.find("-+"),1);
			}
			else if(oldS.find("+-") != string::npos)
			{
				oldS.erase(oldS.find("+-"),1);
			}
			k.set(oldS);
		}	
	}
	else
	{
		int num1 = this->cor, num2 = var.cor;
		string y = "";
		if(num1 != 1 || this->x == "n")
			y += to_string(num1);
		y += this->x;
		if(this->deno != 1)
		{
			y += "/";
			y += to_string(this->deno);
		}
		y += "+";
		if(num2 != 1 || var.x == "n")
			y += to_string(num2);
		y += var.x;
		if(var.deno != 1)
		{
			y += "/";
			y += to_string(var.deno);
		}
		k.set(y);		
	}
	
	return k;
}

Variable Variable::operator-(const Variable& var) const
{
	Variable k;
	int found = this->x.find(var.x);
	if(this->x == var.x)
	{
		int num = var.cor - this->cor;
		k.set(num, this->x, 1); 
	}
	else if(found != string::npos)
	{
		string oldS = this->x;
		int found = oldS.find(var.x);
		char a = '+';
		if(found != 0)
			a = oldS[found-1];
		int i = 1;
		string numS = "";
		bool isOne = true;
		while(a != '+' && a != '-')
		{
			isOne = false;
			numS += a;
			i++;
			if(found - i == -1)
				break;
			a = oldS[found - i];
		}
		if(isOne)
			numS = "1";
		reverse(numS.begin(), numS.end());
		
		if(found+1 != oldS.size())
		{
			a = oldS[found + 1];
			if(a == '/')
			{
				string denoS = "";
				i = 2;
				a = oldS[found + i];
				while(a != '+' && a != '-')
				{
					denoS += a;
					i++;
					if(found + i == oldS.size())
						break;
					a = oldS[found + i];
				}
				int num = stoi(numS) - var.cor * stoi(denoS);
				string toInsert = to_string(num);
				if(numS != "1" || var.x == "n")
				{
					oldS.erase(oldS.begin() + found - numS.size(), oldS.begin() + found);
					oldS.insert(found - numS.size(), toInsert);
				}
				else
					oldS.insert(found - numS.size() + 1, toInsert);
				 
				if(oldS.find("-+") != string::npos)
				{
					oldS.erase(oldS.find("-+"), 1);
				}
				else if(oldS.find("+-") != string::npos)
				{
					oldS.erase(oldS.find("+-"), 1);
				}
					
				k.set(oldS);
			}
			else
			{
				int num = stoi(numS) - var.cor;
				string toInsert = to_string(num);
				
				if(numS != "1" || var.x == "n")
				{
					oldS.erase(oldS.begin() + found - numS.size(), oldS.begin() + found);
					oldS.insert(found - numS.size(), toInsert);
				}
				else
					oldS.insert(found - numS.size() + 1, toInsert);
				if(oldS.find("-+") != string::npos)
				{
					oldS.erase(oldS.find("-+"), 1);
				}
				else if(oldS.find("+-") != string::npos)
				{
					oldS.erase(oldS.find("+-"), 1);
				}
				k.set(oldS);
			}
		}
		else
		{
			
			int num = var.cor + stoi(numS);
			string toInsert = to_string(num);
			if(numS != "1" || var.x == "n")
			{
				oldS.erase(oldS.begin() + found - numS.size(), oldS.begin() + found);
				oldS.insert(found - numS.size(), toInsert);
			}
			else
				oldS.insert(found - numS.size() + 1, toInsert);
			if(oldS.find("-+") != string::npos)
			{
				oldS.erase(oldS.find("-+"), 1);
			}
			else if(oldS.find("+-") != string::npos)
			{
				oldS.erase(oldS.find("+-"), 1);
			}
			k.set(oldS);
		}	
	}
	else
	{
		int num1 = var.cor, num2 = this->cor;
		string y = "";
		if(num1 != 1 || this->x == "n")
			y += to_string(num1);
		y += this->x;
		if(this->deno != 1)
		{
			y += "/";
			y += to_string(this->deno);
		}
		y += "-";
		if(num2 != 1 || var.x == "n")
			y += to_string(num2);
		y += var.x;
		if(var.deno != 1)
		{
			y += "/";
			y += to_string(var.deno);
		}
		k.set(y);		
	}
	return k;
}

Variable Variable::operator*(const Variable& var) const
{
	Variable k;
	int num = this->cor * var.cor;
	int deno = this->deno * var.deno;
	int gcdNum = Gcd(num, deno);
	num /= gcdNum;
	deno /= gcdNum;
	if(this->x == var.x)
		k.set(num, this->x, deno);
	else
	{
		string y = this->x + var.x;
		k.set(num, y, deno);
	}
	return k;
}

Variable Variable::operator/(const Variable& var) const
{
	Variable k;
	if(this->x == "n" && var.x == "n")
	{
		int num = this->cor / var.cor;
		k.set(num, this->x, 1);
	}
	else
	{
		int num = this->cor;
		int deno = this->deno * var.cor;
		int gcdNum = Gcd(num, deno);
		num /= gcdNum;
		deno /= gcdNum;
		k.set(num, this->x, deno);
	}
	
	return k;
}

int main()
{
	Variable a(1,"a-2b+c+1n",1);
	Variable b(6,"b",1);
	Variable c(1,"c",2);
	Variable d(2,1);
	
	cout << a-b;
	
//	string input;
//	cin >> input;
//	
//	string numS = "";
//	Stack<Variable> operand;
//	Stack<char> operater;
//	
//	for(int i = 0; i < input.size(); i++)
//	{
//		char com = input[i];
//		if(com != '+' && com != '-' && com != '*' && com != '/')
//		{
//			numS += input[i];
//			if(i == input.size() - 1)
//			{
//				try
//				{
//					Variable k(stoi(numS));
//					operand.push(k);
//				}
//				catch(invalid_argument o)
//				{
//					Variable k(numS);
//					operand.push(k);
//				}
//			}
//		}
//		else
//		{	
//			try
//			{
//				Variable k(stoi(numS));
//				operand.push(k);
//			}
//			catch(invalid_argument o)
//			{
//				Variable k(numS);
//				operand.push(k);
//			}
//			
//			try
//			{
//				while(((com == '+' || com == '-') && (operater.peek() == '+' || operater.peek() == '-' || operater.peek() == '*' || operater.peek() == '/'))
//					|| ((com == '*' || com == '/') && (operater.peek() == '*' || operater.peek() == '/')))
//				{
//					Variable num1 = operand.peek();
//					operand.pop();
//					Variable num2 = operand.peek();
//					operand.pop();
//					switch (operater.peek())
//					{
//						case '+':
//						{
//							Variable toPush = num2 + num1;
//							operand.push(toPush);
//							break;
//						}
//						case '-':
//						{
//							Variable toPush = num2 - num1;
//							operand.push(toPush);
//							break;
//						}
//						case '*':
//						{
//							Variable toPush = num2 * num1;
//							operand.push(toPush);
//							break;
//						}
//						case '/':
//						{
//							Variable toPush = num2 / num1;
//							operand.push(toPush);
//							break;
//						}
//					}
//					operater.pop();
//				}
//					operater.push(com);
//			}
//			catch (logic_error e)
//			{
//				operater.push(com);
//			}
//			numS.clear();
//			operand.print();
//			operater.print();
//		} 
//	}
//	cout << "====================" << endl;
//	while(!operater.isEmpty())
//	{
//		Variable num1 = operand.peek();
//		operand.pop();
//		Variable num2 = operand.peek();
//		operand.pop();
//		switch (operater.peek())
//		{
//			case '+':
//			{
//				Variable toPush = num2 + num1;
//				operand.push(toPush);
//				break;
//			}
//			case '-':
//			{
//				Variable toPush = num2 - num1;
//				operand.push(toPush);
//				break;
//			}
//			case '*':
//			{
//				Variable toPush = num2 * num1;
//				operand.push(toPush);
//				break;
//			}
//			case '/':
//			{
//				Variable toPush = num2 / num1;
//				operand.push(toPush);
//				break;
//			}
//		}
//		operater.pop();
//		operand.print();
//		operater.print();
//	}
//	cout << operand.peek();
	
	return 0;
}
