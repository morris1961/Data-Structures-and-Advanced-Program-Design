#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <string>
using namespace std;

template <typename Item>
void print(Item& i)
{
	cout << i;
}

template <typename Item>
class TreeNode
{
private:
	Item item;
	vector<TreeNode*> children;
	bool isWord;
public:
	TreeNode(){isWord = false;}
	TreeNode(const Item& anItem) {this->item = anItem; isWord = false;}
	void setItem(const Item& anItem) {this->item = anItem;}
	void setIsWord(bool isWord) {this->isWord = isWord;}
	void setNewChild(TreeNode<Item>* nextPtr);
	void setNewChildren(vector<TreeNode<Item>*> nextPtr);
	Item getItem() const {return this->item;}
	vector<TreeNode*> getChildren() const {return this->children;}
	bool isLeaf() const {return (this->children.size() == 0);}
	bool getIsWord()const {return this->isWord;}
};

template <typename Item>
void TreeNode<Item>::setNewChild(TreeNode<Item>* nextPtr)
{
	if(this->children.size() == 0)
	{
		this->children.push_back(nextPtr);
	}
	else
	{
		bool success = false;
		for(int i = 0; i < this->children.size(); i++)
		{
			if(this->children[i]->getItem() > nextPtr->getItem())
			{
				success = true;
				children.insert(this->children.begin() + i, nextPtr);
				break;
			}
		}
		if(!success)
		{
			children.push_back(nextPtr);
		}
	}
}

template <typename Item>
void TreeNode<Item>::setNewChildren(vector<TreeNode<Item>*> nextPtr)
{
	for(int i = 0; i < nextPtr.size(); i++)
	{
		this->setNewChild(nextPtr[i]);
	}
}

template <typename Item>
class Tree
{
private:
	vector<TreeNode<Item>*> root;
	
	bool addOne(TreeNode<Item>* cur, const Item& newData);
	void preorder(void visit(Item&), vector<TreeNode<Item>*> treePtr) const;
	void preorderPrint(TreeNode<Item>* treePtr, string& ans, bool& first) const;
	vector<TreeNode<Item>*> copyTree(const vector<TreeNode<Item>*> treePtr); 
	void destroyTree(vector<TreeNode<Item>*> subTreePtr);
	bool involve(const Item& anEntry, vector<TreeNode<Item>*> subTreePtr) const;
	TreeNode<Item>* findOne(const Item& anEntry, vector<TreeNode<Item>*> subTreePtr) const;
public:
	Tree(){;}
	~Tree();
    Tree(const vector<TreeNode<Item>*>& children);
    Tree(const Tree<Item>& tree);
    
    bool isEmpty() const;
    Item getRootData(int index) const throw(logic_error);
    bool setRootData(const Item& newData);
    bool add(const Item* newData, int len); // Adds a node
//    bool remove(const Item[] data); // Removes a node
    void clear();
    bool contains(const Item& anEntry) const;
    TreeNode<Item>* contains(const Item* anEntry, int len) const;
    void findPrefix(Item* prefix) const;
    
	void preorderTraverse(void visit(Item&)) const;
};

template<class Item>
void Tree<Item>::preorderPrint(TreeNode<Item>* treePtr, string& ans, bool& first) const
{
	if(treePtr != nullptr)
	{	
//		if(treePtr->getChildren().size() > 1)
//		{
			ans += treePtr->getItem();
//			cout <<treePtr->getItem()<<" call !"<< "prefix :" << ans << endl;
//		}
        for(int i = 0; i < treePtr->getChildren().size(); i++)
        {
			Item theItem = treePtr->getChildren()[i]->getItem();
			ans += theItem;
			if(treePtr->getChildren()[i]->getIsWord())
			{
				if(first)
				{
					cout << ans;
					first = false;
				}
				else
					cout << " " << ans;
//				cout << ans << endl;
//				ans = prefix;
			}
			ans.pop_back();
	        preorderPrint(treePtr->getChildren()[i], ans, first);
		}
//		if(treePtr->getChildren().size() > 1)
//		{
			ans.pop_back();
//			cout <<treePtr->getItem()<<" call !"<< "prefix :" << ans << endl;
//		}
		
	}
}

template<class Item>
TreeNode<Item>* Tree<Item>::findOne(const Item& anEntry, vector<TreeNode<Item>*> subTreePtr) const
{
	if (subTreePtr.size() != 0)
	{
   		for(int i = 0; i < subTreePtr.size(); i++)
   		{
   			if(subTreePtr[i]->getItem() == anEntry)
   				return subTreePtr[i];
		}
	}
	return nullptr;
}

template<class Item>
bool Tree<Item>::involve(const Item& anEntry, vector<TreeNode<Item>*> subTreePtr) const
{
	if (subTreePtr.size() != 0)
	{
   		for(int i = 0; i < subTreePtr.size(); i++)
   		{
   			if(subTreePtr[i]->getItem() == anEntry)
   				return true;
   			else 
   				return this->involve(anEntry, subTreePtr[i]->getChildren());
		}
	}
	return false;
}

template<class Item>
void Tree<Item>::destroyTree(vector<TreeNode<Item>*> subTreePtr)
{
	if (subTreePtr.size() != 0)
	{
   		for(int i = 0; i < subTreePtr.size(); i++)
   		{
   			this->destroyTree(subTreePtr[i]->getChildren());
   			delete subTreePtr[i];
		}
	}
}

template <typename Item>
vector<TreeNode<Item>*> Tree<Item>::copyTree(vector<TreeNode<Item>*> treePtr)
{
	vector<TreeNode<Item>*> newTree;
    if (treePtr.size() != 0)
    {
	   for(int i = 0; i < treePtr.size(); i++)
	   {
	   		TreeNode<Item>* newTreePtr = new TreeNode<Item>(treePtr[i]->getItem());
	   		newTree.push_back(newTreePtr);
	   		newTree[i]->setNewChildren(this->copyTree(treePtr[i]->getChildren()));
	   }
    }
    return newTree;
}

template <typename Item>
void Tree<Item>::preorder(void visit(Item&), vector<TreeNode<Item>*> treePtr) const
{
	if (treePtr.size() != 0)
    {	
        for(int i = 0; i < treePtr.size(); i++)
        {
			Item theItem = treePtr[i]->getItem();
			if(treePtr[i]->getIsWord())
				visit(theItem);
	        preorder(visit, treePtr[i]->getChildren());
		}
    }	
}

template <typename Item>
bool Tree<Item>::addOne(TreeNode<Item>* cur, const Item& newData)
{
	TreeNode<Item>* newChild = new TreeNode<Item>(newData);
	cur->setNewChild(newChild);
}

template <typename Item>
Tree<Item>::~Tree()
{
	this->destroyTree(this->root);
}

template <typename Item>
Tree<Item>::Tree(const vector<TreeNode<Item>*>& newChildren)
{
	for(int i = 0; i < newChildren.size(); i++)
	{
		this->setRootData(newChildren[i]->getItem());
	}
}

template <typename Item>
Tree<Item>::Tree(const Tree<Item>& tree)
{
	this->root = this->copyTree(tree.root);
}

template <typename Item>
bool Tree<Item>::isEmpty() const
{
	return (this->root.size() == 0);
}

template <typename Item>
Item Tree<Item>::getRootData(int index) const throw(logic_error)
{
	if(isEmpty())
		throw logic_error("Empty!!");
	return root[index]->getItem();
}

template <typename Item>
bool Tree<Item>::setRootData(const Item&newData)
{
	for(int i = 0; i < root.size(); i++)
	{
		if(root[i]->getItem() == newData)
		{
			return false;
		}
	}
	
	TreeNode<Item>* newChild = new TreeNode<Item>(newData);
	if(this->isEmpty())
	{
		root.push_back(newChild);
	}
	else
	{
		bool success = false;
		for(int i = 0; i < root.size(); i++)
		{
			if(root[i]->getItem() > newData)
			{
				success = true;
				root.insert(root.begin() + i, newChild);
				break;
			}
		}
		if(!success)
			root.push_back(newChild);
		
	}
	return true;
}

template <typename Item>
bool Tree<Item>::add(const Item* newData, int len)
{
	this->setRootData(newData[0]);
	TreeNode<Item>* cur = nullptr;
	for(int j = 0; j < this->root.size(); j++)
		if(this->getRootData(j) == newData[0])
			cur = root[j];
	if(len == 1)
		cur->setIsWord(true);
	for(int i = 1; i < len; i++)
	{
//		cout << i << " ";
		bool hasBeen = false;
		for(int j = 0; j < cur->getChildren().size(); j++)
		{
			if(cur->getChildren()[j]->getItem() == newData[i])
			{
				cur = cur->getChildren()[j];
				hasBeen = true;
				break;
			}
		}
		if(!hasBeen)
		{
//			cout << "? ";
			this->addOne(cur, newData[i]);
			for(int j = 0; j < cur->getChildren().size(); j++)
			{
				if(cur->getChildren()[j]->getItem() == newData[i])
				{
					cur = cur->getChildren()[j];
					break;
				}
			}
		}
		if(i == len - 1)
		{
			cur->setIsWord(true);
		}
	}
}

template <typename Item>
void Tree<Item>::clear()
{
	this->destroyTree(this->root);
}

template <typename Item>
void Tree<Item>::preorderTraverse(void visit(Item&)) const
{
	this->preorder(visit, this->root);
}

template <typename Item>
bool Tree<Item>::contains(const Item& anEntry) const
{
	return this->involve(anEntry, this->root);
}

template <typename Item>
TreeNode<Item>* Tree<Item>::contains(const Item* anEntry, int len) const
{
	TreeNode<Item>* cur = this->findOne(anEntry[0], this->root);
//	cout << cur->getItem() << endl;
	for(int i = 1 ; i < len; i++)
	{
		if (cur != nullptr)
		{
			cur = this->findOne(anEntry[i], cur->getChildren());
		}
		else
			break;
	} 
	
	return cur;
}

template <typename Item>
void Tree<Item>::findPrefix(Item* prefix) const
{
	TreeNode<Item>* cur = this->contains(prefix, strlen(prefix));
	string ans = prefix;
	bool first = true;
	if(cur != nullptr)
	{
		if(cur->getChildren().size() == 0 && cur->getIsWord())
			cout << ans;
		else
		{
			if(cur->getIsWord())
			{
				cout << ans;
				first = false;
			}
			ans.pop_back();
			this->preorderPrint(cur, ans, first);
		}
	}
}

int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	string p;
	char **input = new char* [n];
	char **search = new char* [m];
	for(int i = 0; i < n; i++)
	{
		cin >> p;
		input[i] = new char[p.size()+1];
		strcpy(input[i], p.c_str());
	}
	for(int i = 0; i < m; i++)
	{
		cin >> p;
		search[i] = new char[p.size()+1];
		strcpy(search[i], p.c_str());
	}
	
	Tree<char> t;
	for(int i = 0; i < n; i++)
	{
		t.add(input[i], strlen(input[i]));
	}
//	t.preorderTraverse(print);
	t.findPrefix(search[0]);
	for(int i = 1; i < m; i++)
	{
		cout << endl;
		t.findPrefix(search[i]);
	}
	
	for(int i = 0; i < n; i++)
	{
		delete [] input[i];
	} 
	delete [] input;
	
	for(int i = 0; i < m; i++)
	{
		delete [] search[i];
	} 
	delete [] search;
	
	return 0;
}
