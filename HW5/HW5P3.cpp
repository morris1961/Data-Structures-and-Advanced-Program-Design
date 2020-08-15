#include <iostream>
#include <stdexcept>
using namespace std;

template<typename Item>
class ListInterface
{
public:
	/*
	@return if the list is empty
	*/
	virtual bool isEmpty() const = 0;
	/*
	@return the amount of items in the list
	*/
	virtual int getLenth() const = 0;
	/*
	@param positon The position at which to insert the entry 
	@param entry the entry which to insert
	@return if the insertion is successful
	@post if successful which means 1 <= position <= length + 1,
		  then the entry will at the given position in the list
	*/
	virtual bool insert(int position, const Item& entry) = 0;
	/*
    @param position  The list position of the entry to remove
    @return  if removal is successful
	@post  if successful which means 1 <= position <= length + 1,
		  then the entry at the given position in the list will be removed
	*/
//    virtual bool remove(int position) = 0;
	/*
    @post  List contains no entries and the count of items is 0.
	*/
    virtual void clear() = 0;
    /*
    @param position  The list position of the desired entry.
    @return  The entry at the given position.
	*/
    virtual Item getEntry(int position) const throw (logic_error) = 0;
    /*
	@param position  The list position of the entry to replace.
    @param newEntry  The replacement entry. 
    @post  The entry at the given position is newEntry.
    */
    virtual void setEntry(int position, const Item& newEntry) throw (logic_error) = 0;
	
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

template<typename Item>
class List : public ListInterface<Item>
{
private:
	int itemCnt;
	Node<Item>* headptr;
	Node<Item>* getNode(int position) const;
public:
	List<Item>();
	List<Item>(const List<Item>& copy);
	const List<Item>& operator = (const List<Item>& copy);
	~List<Item>();
	bool isEmpty() const;
	int getLenth() const;
	bool insert(int position, const Item& entry);
    bool remove(const Item& entry);
    bool removeByp(int position);
    void clear();
    Item getEntry(int position) const throw (logic_error);
    void setEntry(int position, const Item& entry) throw (logic_error);
    void print() const;
    void append(const Item& entry);
    int index(const Item& entry) const;
    int count(const Item& entry) const;
    void extend(const List<Item>& list);
    void reverse();
    void sort();
};

template<typename Item>
Node<Item>* List<Item>::getNode(int position) const
{
	Node<Item>* cur = this->headptr;
	for(int i = 0; i < position; i++)
		cur = cur->getNext();
	return cur;
}

template<typename Item>
List<Item>::List() : itemCnt(0), headptr(nullptr)
{
}

template<typename Item>
List<Item>::~List()
{
	this->clear();
}

template<typename Item>
List<Item>::List(const List<Item>& copy) : List()
{
	Node<Item>* cur = copy.headptr;
	for(int i = 0; i < copy.itemCnt; i++)
	{
		this->insert(i, cur->getItem());
		cur = cur->getNext();
	}
}

template<typename Item>
const List<Item>& List<Item>::operator = (const List<Item>& copy)
{
	this->clear();
	Node<Item>* cur = copy.headptr;
	for(int i = 0; i < copy.itemCnt; i++)
	{
		this->insert(i, cur->getItem());
		cur = cur->getNext();
	}
	return *this;
}

template<typename Item>
bool List<Item>::isEmpty() const 
{
	return (this->itemCnt == 0);
}

template<typename Item>
int List<Item>::getLenth() const
{
	return itemCnt;
}

template<typename Item>
bool List<Item>::insert(int position, const Item& entry)
{
	if(position >= 0)
	{
		if(position > this->itemCnt)
			position = this->itemCnt;
		Node<Item>* cur = new Node<Item>(entry);
		if(position == 0)
		{
			cur->setNext(this->headptr);
			this->headptr = cur;
		}
		else
		{
			Node<Item>* pre = this->getNode(position - 1);
			cur->setNext(pre->getNext());
			pre->setNext(cur);
		}
		this->itemCnt++;
		return true;
	}
	else
		return false;
}

template<typename Item>
bool List<Item>::remove(const Item& entry)
{
	int position = this->index(entry);
//	cout << position<<endl;
	if(position != -1)
	{
		if(position == 0)
		{
			Node<Item>* toDelete = this->headptr;
			this->headptr = headptr->getNext();
			delete toDelete;
		}
		else
		{
			Node<Item>* pre = this->getNode(position - 1);
			Node<Item>* toDelete = pre->getNext();
			pre->setNext(toDelete->getNext());
			delete toDelete;
		}
		this->itemCnt--;
		return true;
	}
	else
		return false;
}

template<typename Item>
bool List<Item>::removeByp(int position)
{
	if(position >= 0 && position <= this->itemCnt-1)
	{
		if(position == 0)
		{
			Node<Item>* toDelete = this->headptr;
			this->headptr = headptr->getNext();
			delete toDelete;
		}
		else
		{
			Node<Item>* pre = this->getNode(position - 1);
			Node<Item>* toDelete = pre->getNext();
			pre->setNext(toDelete->getNext());
			delete toDelete;
		}
		this->itemCnt--;
		return true;
	}
	else
		return false;
}

template<typename Item>
void List<Item>::clear()
{
	while(!this->isEmpty())
		this->remove(this->headptr->getItem());
}

template<typename Item>
Item List<Item>::getEntry(int position) const throw (logic_error)
{
	if(!this->isEmpty())
	{
		if(position >= 0 && position <= this->itemCnt-1)
		{
			return this->getNode(position)->getItem();
		}
		else
			throw logic_error("not the right position");
	}
	else
		throw logic_error("is empty!!");
}

template<typename Item>
void List<Item>::setEntry(int position, const Item& entry) throw (logic_error)
{
	if(position <= this->itemCnt-1 && position >= 0)
	{
		this->getNode(position)->setItem(entry);
	}
	else
		throw logic_error("not the right position");
}

template<typename Item>
void List<Item>::print() const
{
	cout << "[";
	if(!this->isEmpty())
	{
		Node<Item>* cur = this->headptr;
		cout << cur->getItem();
		while(cur->getNext() != nullptr)
		{
			cur = cur->getNext();	
			cout << "," << cur->getItem();
		}
	}
//	else
//		cout << "Empty !!\n";
	cout << "]" << endl;
}

template<typename Item>
void List<Item>::append(const Item& entry)
{
	this->insert(itemCnt, entry);
}

template<typename Item>
int List<Item>::index(const Item& entry) const
{
	int count = 0;
	if(!this->isEmpty())
	{
		Node<Item> *cur = this->headptr;
		while(cur->getNext() != nullptr)
		{
			if(cur->getItem() == entry)
				return count;
			cur = cur->getNext();
			count++;
		}
		if(cur->getItem() == entry)
			return count;
	}
	return -1;
}

template<typename Item>
int List<Item>::count(const Item& entry) const
{
	int cnt = 0;
	if(!this->isEmpty())
	{
		Node<Item> *cur = this->headptr;
		while(cur->getNext() != nullptr)
		{
			if(cur->getItem() == entry)
				cnt++;
			cur = cur->getNext();
		}
		if(cur->getItem() == entry)
			cnt++;
	}
	return cnt;
}

template<typename Item>
void List<Item>::extend(const List<Item>& list)
{
	if(!list.isEmpty())
	{
		if(&list != this)
		{
			Node<Item>* cur = list.headptr;
			while(cur->getNext() != nullptr)
			{
				this->append(cur->getItem());
				cur = cur->getNext();
			}
			this->append(cur->getItem());
		}
		else
		{
			int amount = this->itemCnt;
			Node<Item>* cur = this->headptr;
			for(int i = 0; i < amount; i++)
			{
				this->append(cur->getItem());
				cur = cur->getNext();
			}
		}
	}
}

template<typename Item>
void List<Item>::reverse()
{
	List old = *this;
	this->clear();
	Node<Item>* cur = old.headptr;
	for(int i = 0; i < old.itemCnt; i++)
	{
		this->insert(0, cur->getItem());
		cur = cur->getNext();
	}
}

template<typename Item>
void List<Item>::sort()
{
	for (int i = this->itemCnt-1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (this->getNode(j)->getItem() > this->getNode(j+1)->getItem())
			{
				Item it1 = this->getNode(j)->getItem();
				this->removeByp(j);
				this->insert(j+1, it1);
			}
		}
	}
}

int main()
{
	List<int>** list = new List<int>*[30];
	string name[30] = {""};
	int listCount = 0;
	string input;
	
	while(getline(cin,input))
	{
		size_t dot = input.find(".");
		size_t paraR = input.find("(");
		size_t paraL = input.find(")");
		if(dot != string::npos)
		{
			string listName = input.substr(0, dot);
//			cout << listName;
			string command = input.substr(dot+1, paraR-listName.size()-1);
//			cout << command;
			
			List<int>* cur;
			for(int i = 0; i < listCount; i++)
			{
				if(listName == name[i])
				{
					cur = list[i];
					break;
				}
			}
			
			if(command == "append")
			{
				int num = stoi(input.substr(paraR+1, paraL-paraR-1));
				cur->append(num);
			}
			else if(command == "insert")
			{
				size_t com = input.find(",");
				int fir = stoi(input.substr(paraR+1, com-paraR-1));
				int sec = stoi(input.substr(com+1, paraL-com-1));
				cur->insert(fir, sec);
			}
			else if(command == "remove")
			{
				int num = stoi(input.substr(paraR+1, paraL-paraR-1));
				cur->remove(num);
			}
			else if(command == "index")
			{
				int num = stoi(input.substr(paraR+1, paraL-paraR-1));
				cout << cur->index(num) << endl;
			}
			else if(command == "count")
			{
				int num = stoi(input.substr(paraR+1, paraL-paraR-1));
				cout << cur->count(num) << endl;
			}
			else if(command == "extend")
			{
				string exName = input.substr(paraR+1, paraL-paraR-1);
				List<int>* ex;
				bool noSuchList = true;
				for(int i = 0; i < listCount; i++)
				{
					if(exName == name[i])
					{
						ex = list[i];
						noSuchList = false;
						break;
					}
				}
				if(noSuchList)
					;
				else
					cur->extend(*ex);
			}
			else if(command == "reverse")
			{
				cur->reverse();
			}
			else if(command == "sort")
			{
				cur->sort();
			}
		}
		else
		{
			size_t newListName = input.find("=");
			if(newListName != string::npos)
			{
				name[listCount] = input.substr(0, newListName-1);
				list[listCount] = new List<int>;
				listCount++;
			}
			else
			{
				List<int>* cur;
				bool noSuchList = true;
				for(int i = 0; i < listCount; i++)
				{
					if(input == name[i])
					{
						cur = list[i];
						noSuchList = false;
						break;
					}
				}
				if(noSuchList)
					;
				else
					cur->print();
			}
		}
//		for(int i = 0; i < listCount; i++)
//		{
//			cout << name[i] << ":";
//			list[i]->print();
//		}
	}
	
	return 0;
}
