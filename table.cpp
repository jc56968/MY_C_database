
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

template<  class key,class data>
class SloT
{

	using data_pointer=data *;
	template<class data, class key>
	friend class table;
public:
	SloT(Bplusetree<data, key>* AA)
	{
		 
		
		Bplusetree<data, key>* main_table = AA;
		if (main_table)
		{

			BNode<data, key>* p = main_table->root;


			S = new Bplusetree<data_pointer, key>(main_table->Node_size);
			while (p)
			{
				if (p->isBpluse)
				{
					p = p->Slot[0];
				}
				else
				{

					while (p != 0)
					{

						for (int i = 0; i < p->index; i++)
							S->add(p->D[i], p->D[i]->id2);
						p = p->beh;
					}

				}
			}
		}
		else
		{
			cout << "there is no main_slot";
			exit(-1);
		}
	}
	void add(data_pointer d, key k)
	{
		S->add(d, k);
	}
	bool del(key k)
	{
		if (find(k))
		{
			S->del(k);
			return 1;
		}
		return 0;
	}
	void alt(data_pointer d, key k)
	{

		S->alter(d, k);
	}
	data* find(key k)
	{
		data* p = S->get_data(k);

		if (p)
			return p;
		else
			return 0;

	}
	void visit()
	{
	
			S->visit();
		
	}
	~SloT()
	{
		delete S;
	}
private:
	Bplusetree<data_pointer, key>* S;

	table< data,  key> *m_key;



	
};


template<class data,class key>
class table{
public:
	table(int size=5)
	{
		main_table=new Bplusetree<data, key>(size);
	}
	table(int B_size,data *d, key*k,int num)
	{
		main_table=	 new Bplusetree<data, key>(B_size)  ;
	
		for (int i = 0; i < num; i++)
			main_table->add(d[i], k[i]);
	}

	
	
	bool add_slot()
	{
		SloT<key,data> *D=new SloT< key,data>(this->main_table);
		if (D)
		{
			slot_table["id2"] = D;
			return 1;
		}
		else
			return 0;
	}
	
	~table()
	{
	//	delete main_table;
	
	}
	
	void add(data d,key k)
	{
		main_table->add( d,k);
	}
	bool del(key k)
	{
		if (find(k))
		{
			main_table->del(k);
			return 1;
		}
		return 0;
	}
	void alt(data d, key k)
	{
		
		main_table->alter(d, k);
	}
	data * find(key k)
	{
		data * p=main_table->get_data(k);
		
		if (p)
			return p;
		else
			return 0;
			
	}

	
	SloT<key,data>* get_slot(string a)
	{
		
			return slot_table[a];
	}
	vector<data*> visit()
	{
		return this->main_table->visit();

	}
	void print_data(vector<data*>& p)
	{
		
		cout << "id" << "  " << "name" << "  " << "id2" << "  " << "score" << "  "<<endl;
		for(auto c:p)
		{
			c->pprint();
		
	}
	}
private:
	
	//vector<pair<int, Bplusetree<data, key>*> > key_slot;
	//n is the key index of(data) innodb
	Bplusetree<data, key>  *main_table;
	
	map<  string, SloT<  key ,data   >*> slot_table;


};
//extern struct data;
struct data1
{
	int id;
	int id2;
	int score;
	string name;

	data1() :id(0), score(0),id2(0),name("")
	{
		
	}
	data1(int id,int id2, int score, string name):id(id), score(score), id2(id2), name(name)
	{
	
	}
	~data1()
	{}
	void pprint()
	{
		cout << id << "  " << name << "  " << id2 << "  " << score << "  "<<endl;
	}

};

int main()
{

	data1 *D = new data1(1,1, 80, "k");
	table<data1, int> A(5);
	int* p = new int(1);
	table<data1, int> A1();
	
	for (int i = 1; i <= 21; i++)
	{
		A.add(data1(i,i*i+10,(i*i)%100+50,to_string(i)+"class"),i);
	}
	vector<data1*> all = A.visit();
	A.print_data(all);
	all.clear();
	data1 *c = A.find(20);
	A.alt(data1(20,5 ,468, "no_that"),20);
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