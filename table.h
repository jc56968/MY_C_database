#pragma once
#include<iostream>
#include<list>
#include<map>
#include<memory>

#include"B+tree.cpp"
//why not .h
//B+ģ��������ʵ�ַ�һ��
//why
//һ�����������Ҫ���������������躯�������Ա������cpp��C����A()����
//��ģ��Ҳ���Էֿ������붨�壬��Ҫ��д�ڡ�h�� ������������Ѷ���д��cpp���Ϊģ��
//����һ���಻ֻͬ�е���ʱ�Ż�����װ�أ���vector<int>��:A��vector<double>����A����������
//������ȷ����������ʵ��exp ��������������Σ���ֻ��һ�ζ��塣ģ�庯���������ȴ���Զ�β�ͬ�Ķ��壬
//����ٱ���ģ�塣cppʱ���������ɶ�Ӧ��.o�ļ��������ͻ�������ʱ����ģ�庯��Ҳ��ͬ��
//����ֿ�д�ٵ���.h���ļ����ڱ���Դ��cppʱԴ


//1. ģ��ʵ���޷�����Ϊ.o�ļ�, ����޷�������ʱ�����Ž���. ��·��ͨ.
//2. ����ʱ, ģ������ƥ��, ���޷��ҵ�ģ��ʵ��.��·Ҳ��ͬ.

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