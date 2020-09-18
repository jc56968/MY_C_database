#pragma
#include<iostream>
#include<table.h>
#include<set>
#include<map>

using namespace std;
struct data1
{
	int id;
	int id2;
	int score;
	string name;
	static int find_col(string a)
	{
		if (a == "id")
			return 0;
		if (a == "id2")
			return 1;
		if (a == "score")
			return 2;
		if (a == "name")
			return 3;
		return -1;
	}
	data1() :id(0), score(0), id2(0), name("")
	{

	}
	data1(int id, int id2, int score, string name) :id(id), score(score), id2(id2), name(name)
	{

	}
	data1(vector<string>& d, int i, int j)
	{
		if (i + 3 > j)
		{
			cerr << "wrong input data" << endl;
			throw "wro";
		}
		id = stoi(d[i]);
			id2= stoi(d[i+1]);
			score= stoi(d[i+2]);
			name = d[i+3];
			
	}
	~data1()
	{}
	void pprint()
	{
		cout << id << "  " << name << "  " << id2 << "  " << score << "  " << endl;
	}

};
map<string, table<data1, int>> set_table;
void add(vector<string> &sql)
{
	if (set_table.find(sql[2]) != set_table.end())
	{
		try
		{
			data1 t(sql, 4, sql.size());
			set_table[sql[2]].add(t, stoi(sql[4]));
			cout << "insert scuess" << endl;
		}
		catch (string a)
		{
			if (a == "wro")
				return;
		}
		
	}
	else
	{
		cout << "invalid table" << endl;
	}

}
void del(vector<string>& sql)
{
	if (set_table.find(sql[2]) != set_table.end())
	{	
		set_table[sql[2]].del(stoi(sql[6]));
		cout << "delete scuess"<<endl;
	}
	else
	{
		cout << "invalid table" << endl;
	}
}
void ins(vector<string>& sql) 
{
	add(sql);
}
void find(vector<string>& sql)
{
	if (set_table.find(sql[3]) != set_table.end())
	{
		if (data1::find_col(sql[5]))
		{
			if (set_table[sql[3]].slot_table.find(sql[5]) != set_table[sql[3]].slot_table.end())
			{
				cout << "search by index " << sql[5] << endl;
				set_table[sql[3]].find(stoi(sql[5]));
				cout << "search scuess" << endl;
			}
			else
			{
				cout << "search by number " << endl;
				auto A = set_table[sql[3]].visit();
				for (int i = 0; i < A.size(); i++)
				{
					//
					//visut find(A)
					//

				}
			}		
			
		}
		else
		{
			cout << "wrong find col";
		}

		
	}
	else
	{
		cout << "invalid table" << endl;
	}
}
void alt(vector<string>& sql)
{
	if (set_table.find(sql[2]) != set_table.end())
	{
		set_table[sql[2]].alt(data1(), stoi(sql[sql.size()-1]));
		cout << "alt scuess" << endl;
	}
	else
	{
		cout << "invalid table" << endl;
	}
}
/*
int main()
{
	vector<string> sql;
	while (1)
	{
		sql.clear();
		cout << "please input sql" << endl;

		string C;
		if (C == "exit()")
			exit(0);
		else
		{
		
		  while (cin >> C)
		  {
			sql.push_back(C);

		  }
		  if (sql[0] == "select")
		  {
			  find(sql);
		  }
		  if (sql[0] == "delete")
		  {
			  del(sql);
		  }
		  if (sql[0] == "update")
		  {
			  alt(sql);
		  }
		  if (sql[0] == "insert")
		  {
			  ins(sql);
		  }
		  cout << "wrong input sql" <<endl;

	    }


	}
	return 0;
}
*/