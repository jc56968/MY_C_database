
#include<iostream>
#include<list>
#include<map>
#include<memory>

#include"table.h"
#include"B+tree.cpp"

#include<vector>
#include<string>

using namespace std;



template<  class key, class data>
SloT<key,data>::SloT(Bplusetree<data, key>* AA)
	{
		 
	using datapointer=data *;
		Bplusetree<data, key>* main_table = AA;
		if (main_table)
		{

			BNode<data, key>* p = main_table->root;


			S = new Bplusetree< datapointer, key>(main_table->Node_size);
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
						p->getreadp();
						for (int i = 0; i < p->index; i++)
							S->add(p->D[i], p->D[i]->id2);
						if(p->beh!=0)
				
						p = p->beh;
						p->retreadp();
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
template<  class key, class data>
void SloT<key, data>:: add(data_pointer d, key k)
	{
		S->add(d, k);
	}
template<  class key, class data>
bool SloT<key, data>::del(key k)
	{
		if (find(k))
		{
			S->del(k);
			return 1;
		}
		return 0;
	}
template<  class key, class data>
void SloT<key, data>::alt(data_pointer d, key k)
	{

		S->alter(d, k);
	}
template<  class key, class data>
data* SloT<key, data>::find(key k)
	{
		data** p = S->get_data(k);

		if (*p)
			return *p;
		else
			return 0;

	}
template<  class key, class data>
void SloT<key, data>::visit()
	{
	
			S->visit();
		
	}
template<  class key, class data>
 SloT<key, data>::~SloT()
	{
		delete S;
	}


	template<class data, class key>
	table<data,key>::table(int size)
	{
		main_table=new Bplusetree<data, key>(size);
	}
	template<class data, class key>
	table<data, key>::table(int B_size,data *d, key*k,int num)
	{
		main_table=	 new Bplusetree<data, key>(B_size)  ;
	
		for (int i = 0; i < num; i++)
			main_table->add(d[i], k[i]);
	}

	
	template<class data, class key>
	bool  table<data, key>::add_slot()
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
	
	template<class data, class key>
	  table<data, key>::~table()
	{
	//	delete main_table;
	
	}
	
	  template<class data, class key>
	  void  table<data, key>::add(data d,key k)
	{
		main_table->add( d,k);
	}
	  template<class data, class key>
	  bool  table<data, key>::del(key k)
	{
		if (find(k))
		{
			main_table->del(k);
			return 1;
		}
		return 0;
	}
	template<class data, class key>
	void table<data, key>::alt(data d, key k)
	{
		
		main_table->alter(d, k);
	}
	template<class data, class key>
	data *  table<data, key>::find(key k)
	{
		data * p=main_table->get_data(k);
		
		if (p)
			return p;
		else
			return 0;
			
	}

	template<class data, class key>
	SloT<key, data>* table<data, key>:: get_slot(string a)
	{
		
			return slot_table[a];
	}

	template<class data, class key>
	vector<data*>table<data, key>::visit()
	{
		return this->main_table->visit();

	}
	template<class data, class key>
	void table<data, key>::print_data(vector<data*>& p)
	{
		
		cout << "id" << "  " << "name" << "  " << "id2" << "  " << "score" << "  "<<endl;
		for(auto c:p)
		{
			c->pprint();
		
	}
	}

//extern struct data;

/*
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
