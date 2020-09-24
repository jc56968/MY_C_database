#pragma once
#include<iostream>
#include<list>
#include<map>
#include<deque>
#include<math.h>
#include<stack>
#include<vector>
#include<thread>
#include <mutex>    //unique_lock
#include <shared_mutex> //shared_mutex shared_lock
using namespace std;
template <class data, class value>
 class table;
template <class data, class value>
  class SloT;
template <class data, class value>
 class Bplusetree;
 template <class data, class value>
 class BNode;
 template <class data, class value>
 class BNode
{
	
	friend  class table<data, value>;
	
	friend   class SloT<value,data>;
	
	friend  class Bplusetree<data, value>;
public:
	int getsize()
	{
		
			return index;
	}
	BNode* getreadp()
	{
		mutex.lock_shared();
		return this;
	}
	BNode* retreadp()
	{
		mutex.unlock_shared();
		return this;
	}
	BNode* getwritep()
	{
		mutex.lock();
		return this;
	}
	BNode* retwritep()
	{
		mutex.unlock();
		return this;
	}
	bool merge_bro_bpluse(BNode<data, value>* p, bool left);
	bool merge_fa_bpluse();
	bool merge_bro(BNode<data, value>* p, bool left);
	bool merge_fa();
	BNode(int Node_size = 5, bool is = 0);
	BNode(BNode& A);
	BNode& operator=(BNode& A);
	int get_insert_index(value v);
	bool add_node(data d, value v);
	bool add_slot_node(value v, BNode* p, BNode* q);
	~BNode();
	BNode* divide();
private:
	data** D;
	value* V;
	BNode** Slot;
	int index;
	int Node_size;
	BNode* father;
	bool isBpluse;
	BNode* fro;
	BNode* beh;
	mutable	shared_mutex  mutex;

	
};

template <class data, class value>
class Bplusetree
{

	friend  class table<data, value>;

	friend   class SloT<value, data>;

	friend  class Bplusetree<data, value>;
	// friend   table:: add_clust_slot(int );
public:
	
	pair<BNode<data, value>*, int> find_for_del(value v);
	Bplusetree(int Node_size);
	~Bplusetree();
	Bplusetree(Bplusetree& T);
	data* get_data(BNode<data, value>* p, int ind);
	data* get_data(value v);
	pair<BNode<data, value>*, int> find(value v);
	bool add(data d, value v);
	vector<data*>  visit();
	void pprint();
	bool alter(data d, value v);
	bool del(value v);
private:
	int Node_size;
	BNode<data, value>* root;
	BNode<data, value>* fro;

	BNode<data, value>* beh;



};
