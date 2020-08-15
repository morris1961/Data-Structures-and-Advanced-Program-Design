#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
using namespace std;

template <typename Key, typename Item>
class Entry
{
private:
   	Item item;
   	Key searchKey;
	Entry* next;
public:
   	Entry(){this->next = nullptr;}
   	Entry(Item newEntry, Key searchKey);
   	Entry(Item newEntry, Key searchKey, Entry* nextPtr);
   	Item getItem() const{return this->item;}
   	Key getKey() const{return this->searchKey;}
	Entry* getNext(){return this->next;} 
   	void setKey(const Key& searchKey){this->searchKey = searchKey;}
   	void setItem(const Item& newEntry){this->item = newEntry;}
   	void setNext(Entry* newNext){this->next = newNext;}
   	void print(){cout << this->searchKey << " : " << this->item;}
};

template <typename Key, typename Item>
Entry<Key, Item>::Entry(Item newEntry, Key searchKey)
{
	this->item = newEntry;
	this->searchKey = searchKey;
	this->next = nullptr;
}

template <typename Key, typename Item>
Entry<Key, Item>::Entry(Item newEntry, Key searchKey, Entry* nextPtr)
{
	this->item = newEntry;
	this->searchKey = searchKey;
	this->next = nextPtr;
}

template<class Key, class Item>
class HashedEntry
{
private:
	int size;
	int count;
  	Entry<Key, Item>** table;
   	
   	int Hash(const Key& searchkey) const;  
public:
   	HashedEntry(const int &size);
	~HashedEntry();
	   	
   	void add(const Item& newItem, const Key& searchKey) throw (logic_error);
//    void remove(const Key& searchKey);
    Item search(const Key& searchKey) const throw (logic_error);
    void print() const;
};

template<class Key, class Item>
int HashedEntry<Key, Item>::Hash(const Key& searchkey) const
{
	double A = 0.6180339887;
    double frac = static_cast<int>(searchkey[0])*A-floor(static_cast<int>(searchkey[0])*A);
    int fin = floor(this->size*frac);
    if(fin >= size)
    	fin %= size;
    return fin;
}

template<class Key, class Item>
HashedEntry<Key, Item>::HashedEntry(const int& size)
{
	this->size = size;
	this->count = 0;
	this->table = new Entry<Key, Item>*[size]; 
	for(int i = 0; i < size; i++)
		this->table[i] = nullptr;
}

template<class Key, class Item>
HashedEntry<Key, Item>::~HashedEntry()
{
	for(int i = 0; i < this->size; i++)
	{
		while(this->table[i] != nullptr)
		{
			Entry<Key, Item>* toDelete = this->table[i];
			this->table[i] = this->table[i]->getNext();
			delete toDelete;
		}
	}
}

template<class Key, class Item>
void HashedEntry<Key, Item>::add(const Item& newItem, const Key& searchKey) throw (logic_error)
{
//	if(count == size)
//		throw logic_error("full!");
	this->count++;
	int index = this->Hash(searchKey);
//	cout << searchKey << " index:" << index << endl;
	Entry<Key, Item>* entry = new Entry<Key, Item>(newItem, searchKey);
	if(this->table[index] != nullptr)
		entry->setNext(this->table[index]);
	this->table[index] = entry;

}

template<class Key, class Item>
Item HashedEntry<Key, Item>::search(const Key& searchKey) const throw (logic_error)
{
	int index = this->Hash(searchKey);
	Entry<Key, Item>* cur = this->table[index];
//	cout << searchKey << " index:" << index << endl;
	while(cur != nullptr)
	{
		if(cur->getKey() == searchKey)
			return cur->getItem();
		cur = cur->getNext();
	}
	throw logic_error("not defined");
}

template<class Key, class Item>
void HashedEntry<Key, Item>::print() const
{
	
	if(this->count != 0)
	{
		bool f = true;
		for(int i = 0; i < this->size; i++)
		{
			
			Entry<Key, Item>* cur = this->table[i];
			while(cur != nullptr)
			{
				if(!f)
				{
					cout << endl;
					f = false;
				}
				cur->print();
				cout << ",";
				cur = cur->getNext();
			}
		}
	}
	else
		cout << "empty";
}

int main()
{
	HashedEntry<string, string> h(10000);
	string input;
	while(getline(cin, input))
	{
		if(input.find(" ") == string::npos)
		{
			try
			{
				cout << h.search(input) << endl;
			}
			catch (logic_error e)
			{
				cout << e.what() << endl;
			}
		}
		else
		{
			string item = input.substr(0, input.rfind(" "));
			string key = input.substr(input.rfind(" ")+1, input.size()-item.size()-2);
//			cout << item << " " << key << endl;
			try
			{
				h.add(item, key);
			}
			catch (logic_error e)
			{
				cout << "fuckQ!";
			}
//			h.print();
//			cout << "\n--------------------------\n";
		}
	}
	return 0;
}

