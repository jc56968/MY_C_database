#pragma once
#include<iostream>
#include<list>
#include<map>
#include<memory>
#include"B+tree.h"
#include<vector>
#include<string>

using namespace std;

template<  class key, class data>
class SloT
{

	using data_pointer=data *;
	template<class data, class key>
	friend class table;
public:
	SloT(Bplusetree<data, key>* AA);
		void add(data_pointer d, key k);
		bool del(key k);
		void alt(data_pointer d, key k);
		data* find(key k);
		void visit();
		~SloT();
private:
	Bplusetree<data_pointer, key>* S;
	mutable shared_mutex mutex;
	table< data, key>* m_key;
};


template<class data, class key>
class table {
public:
	table(int size = 5);
	table(int B_size, data* d, key* k, int num);

	bool add_slot();

	~table();

	void add(data d, key k);
	bool del(key k);
	void alt(data d, key k);
	data* find(key k);


	SloT<key, data>* get_slot(string a);
	vector<data*> visit();
	void print_data(vector<data*>& p);
	map<  string, SloT<  key, data   >*> slot_table;
private:
	string m_key="";
	//vector<pair<int, Bplusetree<data, key>*> > key_slot;
	//n is the key index of(data) innodb
	Bplusetree<data, key>* main_table;
	//map<  string, SloT<  key, data   >*> slot_table;
	


};