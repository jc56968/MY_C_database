#include<iostream>
#include<table.h>
using namespace std;
void add(vector<string> &sql)
{}
void del(vector<string>& sql) {}
void ins(vector<string>& sql) {}
void find(vector<string>& sql) {}
void alt(vector<string>& sql)
{}
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
		  }
		  if (sql[0] == "delete")
		  {
		  }
		  if (sql[0] == "update")
		  {
		  }
		  if (sql[0] == "insert")
		  {
		  }

	    }


	}
	return 0;
}