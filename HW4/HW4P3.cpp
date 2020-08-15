#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
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
	int numPos;
	int num;
	vector<int> deno;
	vector<int> cor;
	vector<string> var;
	string fin;
	void set(int num)
	{
		this->num = num;
		this->fin = to_string(num);
	}
	void set(vector<int> cor, vector<string> var, vector<int> deno)
	{
		bool first_appear = false;
		this->cor = cor;
		this->var = var;
		this->deno = deno;
		fin = "";
		if(numPos == -1)
		{
			if(var.size() == 0)
			{
				fin += "0";
			}
			else
			{
				if(cor[0] != 0)
				{
					first_appear = true;
					if(this->cor[0] != 1)
					{
						if(this->cor[0] == -1)
							fin += "-"; 
						else
							fin += to_string(cor[0]);
					}	
					fin += this->var[0];
					if(this->deno[0] != 1)
					{
						fin += "/";
						fin += to_string(deno[0]);
					}
				}
				
				
				for(int i = 1; i < cor.size(); i++)
				{	
					if(cor[i] != 0)
					{
						if(cor[i] > 0 && first_appear)
							fin += "+";
						if(this->cor[i] != 1)
						{
							if(this->cor[i] == -1)
								fin += "-"; 
							else
								fin += to_string(cor[i]);
						}
						fin += this->var[i];
						if(this->deno[i] != 1)
						{
							fin += "/";
							fin += to_string(deno[i]);
						}
						first_appear = true;
					}
				}
			}
		}
		else if(this->numPos == 0)
		{
//			cout << "!!" << endl;
			if(num != 0)
			{
				first_appear = true;
				fin += to_string(this->num);
			}
				
				
			for(int i = 0; i < cor.size(); i++)
			{
				if(cor[i] != 0)
				{
					if(cor[i] > 0 && first_appear)
						fin += "+";
					if(this->cor[i] != 1)
					{
						if(this->cor[i] == -1)
							fin += "-"; 
						else
							fin += to_string(cor[i]);
					}
					fin += this->var[i];
					if(this->deno[i] != 1)
					{
						fin += "/";
						fin += to_string(deno[i]);
					}
					first_appear = true;
				}
			}
		}
		else
		{
//			cout << "haha" << endl;
			if(cor[0] != 0)
			{
				first_appear = true;
				if(this->cor[0] != 1)
				{
					if(this->cor[0] == -1)
						fin += "-"; 
					else
						fin += to_string(cor[0]);
				}
				fin += this->var[0];
				if(this->deno[0] != 1)
				{
					fin += "/";
					fin += to_string(deno[0]);
				}
			}
			
		
			bool put = false;
			for(int i = 1; i < cor.size(); i++)
			{	
				if(i == this->numPos && this->num != 0 && !put)
				{	
					if(this->num > 0 && first_appear)
					{
						fin += "+";
					}
					fin += to_string(num);
					i--;
					put = true;
					first_appear = true;
					continue;
				}
				if(cor[i] != 0)
				{
					if(cor[i] > 0 && first_appear)
						fin += "+";
					if(this->cor[i] != 1)
					{
						if(this->cor[i] == -1)
							fin += "-"; 
						else
							fin += to_string(cor[i]);
					}
					fin += this->var[i];
					if(this->deno[i] != 1)
					{
						fin += "/";
						fin += to_string(deno[i]);
					}
					first_appear = true;
				}
			}
			if(this->numPos == cor.size())
			{
				if(this->num != 0)
				{
					if(this->num > 0 && first_appear)
					{
						fin += "+";
					}
					fin += to_string(num);
					first_appear = true;
				}
				
			}
		}
		if(!first_appear)
			fin += "0";
	}
	void set(int num, vector<int> cor, vector<string> var, vector<int> deno, bool toSetPos)
	{
		if(toSetPos)
			this->numPos = var.size();
		this->num = num;
		this->set(cor, var, deno);
	}
	void setPos(int numPos)
	{
		this->numPos = numPos;
	}
public:
	Variable();
	Variable(int num);
	Variable(string str);
	Variable operator+(const Variable& var) const;
	Variable operator-(const Variable& var) const;
	Variable operator*(const Variable& var) const;
	Variable operator/(const Variable& var) const;	
	friend ostream &operator<<( ostream &output, const Variable &var);
};

ostream& operator<<( ostream &output, const Variable &var)
{
	output << var.fin;
}

Variable::Variable()
{
	this->numPos = -1;
	this->num = 0;
	this->fin = "empty !";
}

Variable::Variable(int num) : Variable()
{
	this->numPos = 0;
	this->num = num;
	this->fin = to_string(num);
}

Variable::Variable(string str) : Variable()
{
	this->numPos = -1;
	this->var.push_back(str);
	this->cor.push_back(1);
	this->deno.push_back(1);
	this->fin = str;
}

Variable Variable::operator+(const Variable& var) const
{
	Variable k;
	k.setPos(this->numPos);
	int num = 0;
	vector<int> corF;
	vector<int> denoF;
	vector<string> varF;
	for(int i = 0; i < this->cor.size(); i++)
	{
		corF = this->cor;
		denoF = this->deno;
		varF = this->var;
	}
	num = this->num + var.num;
	if(var.num == 0 && var.var.size() > 0)
	{
		
		bool found = false;
		for(int i = 0; i < varF.size(); i++)
		{
			if(varF[i] == var.var[0])
			{
				found = true;
				corF[i] = corF[i] * var.deno[0] + denoF[i] * var.cor[0];
				denoF[i] *= var.deno[0];
				int g = Gcd(abs(corF[i]), denoF[i]);
				corF[i] /= g;
				denoF[i] /= g;
				break;
			}
		}
		if(!found)
		{
			corF.push_back(var.cor[0]);
			varF.push_back(var.var[0]);
			denoF.push_back(var.deno[0]);
		}
	}
	bool toSetPos = (k.numPos == -1 && var.var.size() == 0);
//	for(int i = 0; i < corF.size(); i++)
//	{
//		cout << num << " " << corF[i] << " " << varF[i] << " " << denoF[i] << " " << toSetPos << endl;
//	}
	k.set(num, corF, varF, denoF, toSetPos);
	return k;
}

Variable Variable::operator-(const Variable& var) const
{
	Variable k;
	k.setPos(this->numPos);
	int num = 0;
	vector<int> corF;
	vector<int> denoF;
	vector<string> varF;
	for(int i = 0; i < this->cor.size(); i++)
	{
		corF = this->cor;
		denoF = this->deno;
		varF = this->var;
	}
	num = this->num - var.num;
	
	if(var.num == 0 && var.var.size() > 0)
	{
		bool found = false;
		for(int i = 0; i < varF.size(); i++)
		{
			if(varF[i] == var.var[0])
			{
				found = true;
				corF[i] = corF[i] * var.deno[0] - denoF[i] * var.cor[0];
				denoF[i] *= var.deno[0];
				int g = Gcd(abs(corF[i]), denoF[i]);
				corF[i] /= g;
				denoF[i] /= g;
				break;
			}
		}
		if(!found)
		{
			corF.push_back(-var.cor[0]);
			varF.push_back(var.var[0]);
			denoF.push_back(var.deno[0]);
		}
	}
	
	bool toSetPos = (k.numPos == -1 && var.var.size() == 0);
//	cout << "!!" << k.numPos << endl;
//	for(int i = 0; i < corF.size(); i++)
//	{
//		cout << num << " " << corF[i] << " " << varF[i] << " " << denoF[i] << endl;
//	}
	k.set(num, corF, varF, denoF, toSetPos);
	return k;
}

Variable Variable::operator*(const Variable& var) const
{
	Variable k;
	k.setPos(this->numPos);
	if(this->var.size() == 0 && var.var.size() == 0)
	{
		int numF = this->num * var.num;
		k.set(numF);
	}
	else
	{
		vector<int> corF;
		vector<int> denoF;
		vector<string> varF;
		int c;
		int d;
		if(this->var.size() != 0 && var.var.size() != 0)
		{
			c = this->cor[0] * var.cor[0];
			varF.push_back(this->var[0] + var.var[0]);
			d = this->deno[0];
		}
		else if(this->var.size() != 0)
		{
			c = this->cor[0] * var.num;
			varF.push_back(this->var[0]);
			d = this->deno[0];
		}
		else if(var.var.size() != 0)
		{
			c = this->num * var.cor[0];
			varF.push_back(var.var[0]);
			d = var.deno[0];
		}
		int g = Gcd(abs(c), abs(d));
		c /= g;
		d /= g;
		corF.push_back(c);
		denoF.push_back(d);
//		cout << corF[0] << " " << varF[0] << " " << denoF[0] << endl;
		k.set(corF, varF, denoF);
	} 
	return k;
}

Variable Variable::operator/(const Variable& var) const
{
	Variable k;
	k.setPos(this->numPos);
	if(this->var.size() == 0 && var.var.size() == 0)
	{
		int numF = this->num / var.num;
		k.set(numF);
	}
	else
	{
		vector<int> corF;
		vector<int> denoF;
		vector<string> varF;
		int c;
		int d;
		if(this->var.size() != 0 && var.var.size() != 0)
		{
			//do nothing
		}
		else if(this->var.size() != 0)
		{
			c = this->cor[0];
			varF.push_back(this->var[0]);
			d = this->deno[0] * var.num;
		}
		else if(var.var.size() != 0)
		{
			//do nothing
		}
		int g = Gcd(abs(c), abs(d));
		c /= g;
		d /= g;
		corF.push_back(c);
		denoF.push_back(d);
//		cout << corF[0] << " " << varF[0] << " " << denoF[0] << endl;
		k.set(corF, varF, denoF);
	} 
	return k;
}

int main()
{	
//	Variable a("a");
//	Variable b("a");
//	Variable c("c");
//	Variable x = a/b;
//	Variable y = x/b;
//	cout << a - b << endl;
//	cout << "!!";
	
	string input;
	cin >> input;
	
	string numS = "";
	Stack<Variable> operand;
	Stack<char> operater;
	
	for(int i = 0; i < input.size(); i++)
	{
		char com = input[i];
		if(com != '+' && com != '-' && com != '*' && com != '/')
		{
			numS += input[i];
			if(i == input.size() - 1)
			{
				try
				{
					Variable k(stoi(numS));
					operand.push(k);
				}
				catch(invalid_argument o)
				{
					Variable k(numS);
					operand.push(k);
				}
			}
		}
		else
		{	
			try
			{
				Variable k(stoi(numS));
				operand.push(k);
			}
			catch(invalid_argument o)
			{
				Variable k(numS);
				operand.push(k);
			}
			
			try
			{
				while(((com == '+' || com == '-') && (operater.peek() == '+' || operater.peek() == '-' || operater.peek() == '*' || operater.peek() == '/'))
					|| ((com == '*' || com == '/') && (operater.peek() == '*' || operater.peek() == '/')))
				{
					Variable num1 = operand.peek();
					operand.pop();
					Variable num2 = operand.peek();
					operand.pop();
					switch (operater.peek())
					{
						case '+':
						{
							Variable toPush = num2 + num1;
							operand.push(toPush);
							break;
						}
						case '-':
						{
							Variable toPush = num2 - num1;
							operand.push(toPush);
							break;
						}
						case '*':
						{
							Variable toPush = num2 * num1;
							operand.push(toPush);
							break;
						}
						case '/':
						{
							Variable toPush = num2 / num1;
							operand.push(toPush);
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
//	cout << "====================" << endl;
	while(!operater.isEmpty())
	{
		Variable num1 = operand.peek();
		operand.pop();
		Variable num2 = operand.peek();
		operand.pop();
		switch (operater.peek())
		{
			case '+':
			{
				Variable toPush = num2 + num1;
				operand.push(toPush);
				break;
			}
			case '-':
			{
				Variable toPush = num2 - num1;
				operand.push(toPush);
				break;
			}
			case '*':
			{
				Variable toPush = num2 * num1;
				operand.push(toPush);
				break;
			}
			case '/':
			{
				Variable toPush = num2 / num1;
				operand.push(toPush);
				break;
			}
		}
		operater.pop();
//		operand.print();
//		operater.print();
	}
	cout << operand.peek();
	
	return 0;
}
