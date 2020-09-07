#pragma once
#include<iostream>
#include<list>
#include<map>
#include<memory>

#include"B+tree.cpp"
//why not .h
//B+模板类声明实现放一起
//why
//一般类的声明需要在声明中声明所需函数和类成员，再在cpp中C：：A()定义
//类模板也可以分开声明与定义，但要都写在。h里 问题在于如果把定义写在cpp里，因为模板
//类与一般类不同只有调用时才会生成装载，如vector<int>：:A和vector<double>：：A是两个函数
//并不能确定函数具体实例exp 函数可以声明多次，但只有一次定义。模板函数声明多次却可以多次不同的定义，
//因而再编译模板。cpp时并不会生成对应的.o文件，这样就会在连接时报错，模板函数也是同理
//如果分开写再调用.h的文件。在编译源。cpp时源


//1. 模板实现无法编译为.o文件, 因此无法在链接时做符号解析. 此路不通.
//2. 编译时, 模板特例匹配, 有无法找到模板实现.此路也不同.

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
private:

	//vector<pair<int, Bplusetree<data, key>*> > key_slot;
	//n is the key index of(data) innodb
	Bplusetree<data, key>* main_table;

	map<  string, SloT<  key, data   >*> slot_table;


};
//extern struct data;
struct data1
{
	int id;
	int id2;
	int score;
	string name;

	data1() :id(0), score(0), id2(0), name("")
	{

	}
	data1(int id, int id2, int score, string name) :id(id), score(score), id2(id2), name(name)
	{

	}
	~data1()
	{}
	void pprint()
	{
		cout << id << "  " << name << "  " << id2 << "  " << score << "  " << endl;
	}

};
/*
int main()
{

	data1* D = new data1(1, 1, 80, "k");
	table<data1, int> A(5);
	int* p = new int(1);
	table<data1, int> A1();

	for (int i = 1; i <= 21; i++)
	{
		A.add(data1(i, i * i + 10, (i * i) % 100 + 50, to_string(i) + "class"), i);
	}
	vector<data1*> all = A.visit();
	A.print_data(all);
	all.clear();
	data1* c = A.find(20);
	A.alt(data1(20, 5, 468, "no_that"), 20);
	all = A.visit();
	A.print_data(all);
	all.clear();
	A.del(20);
	all = A.visit();
	A.print_data(all);
	all.clear();
	c = A.find(20);
	A.visit();

	A.add_slot();
	auto DD = A.get_slot("id2");




	//del alter change only for main key
	 //anthor change bu main_slot
	//SLot must be int 
	return 0;

}
*/