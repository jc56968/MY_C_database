#pragma
#include<iostream>
#include<table.h>
#include<table.cpp>
#include<set>
#include<map>
#include<string>
#include<sstream>
#include<algorithm>
#include <functional>
#include<algorithm>
using namespace std;
struct data2
{
	static void creat_table(vector<string>& A, string m_k)
	{
		creat_data2(A, m_k);
	}
	data2(string A)
	{
		if (name.size() == 0)
		{
			cout << "not define date" << endl;
		}
		else
		{
			string c;
			replace(A.begin(), A.end(), ',', ' ');
			stringstream S(A);
			while (S >> c)
			{
				d.push_back(c);
			}
			while (d.size() < name.size())
			{
				d.push_back("");
			}
		}
	}
	data2(vector<string> A)
	{
		if (name.size() == 0)
		{
			cout << "not define date" << endl;
		}
		else if (A.size() == 0)
		{
			cout << "not input date" << endl;
			throw 0;
		}
		else
		{
			swap(A, d);
		}
	}
	data2()
	{

	}
	static int find_col(string a)
	{
		if (name.size() == 0)
		{
			cout << "not define date" << endl;
		}
		else
		{
			for (int i = 0; i < name.size(); i++)
				if (name[i] == a)
					return i;
			return -1;
		}
	}
	void pprint_name()
	{
		for (int i = 0; i < name.size(); i++)
			cout << name[i] << "    " << endl;
	}
	void pprint()
	{
		for (int i = 0; i < name.size(); i++)
			cout << d[i] << " " << endl;
	}
	static string getmkey()
	{
		return mkey;
	}
	vector<string> d;
	static int get_size()
	{
		return size;
	}

private:
	static string mkey;
	static int size;
	static vector<string> name;
	static void creat_data2(vector<string> A, string m_k)
	{
		if (name.size() == 0)
		{

			swap(name, A);
			mkey = m_k;
			size = name.size();
		}
		else
		{
			cout << "the data is defined" << endl;
		}
	}


};
map<string, table<data2, string>> set_table;
struct SELECT
{
	SELECT(string a)
	{
		stringstream s(a);
		while (s >> a)
		{
			if (a == "SELECT")
			{
				s >> a;
				select_what = a;
			}
			else if (a == "FROM")
			{
				s >> a;
				table = a;
			}
			else if (a == "WHERE")
			{
				s >> a;
			
				string con(a, 0, condition.find("=")-1);
				condition = con;
			   con=(a, condition.find("=") + 1, condition.size()-1);
				cv = con;
			}
			
		}
		if(check())
		
		 T=print( exesql() );
		

	}
	bool check()
	{
		//check table
		if (set_table.find(table) == set_table.find(table))
		{
			cout << "there is no input table" << endl;
			return 0;
		}
		//check condition
	
		if (data2::find_col(condition) == -1)
		{
			cout << "there is no input condition" << endl;
			return 0;
		}
		//check selectwhat
		string con = select_what;
		con.replace(con.begin(),con.end(), ',', ' ');
		stringstream s(con);
		while (s >> con)
		{
			if (data2::find_col(con) == -1)
			{
				cout << "there is no input select_aim" << endl;
				return 0;
			}
		}
		return 1;
		
		
	}
	vector<data2*>  exesql()
	{
		vector<data2*> T;
		if (condition == ""&&select_what=="*")
		{
			T = set_table[table].visit();
			return T;
		}
		else
		{
			if (set_table[table].slot_table.find(condition)!= set_table[table].slot_table.end()
				|| condition==data2::getmkey())
			{
				cout << " using slot" << endl;
				if (condition == data2::getmkey())
				{
					
					T.push_back(set_table[table].find(cv));
				}
				else 
				{
					
					T.push_back(    set_table[table].get_slot(condition)->find(cv) );
				}
				if (T[0] == 0)
				{
					cout << "NOT FIND" << endl;
					return T;
				}
				else
				{
					return T;
				}
			}
			else
			{
				vector<data2*> W;
				cout << "no hit slot using visit" << endl;
				T = set_table[table].visit();
				int i;
				for (i = 0; i < T.size(); i++)
				{
					int ind = data2::find_col(condition);
					if (T[i]->d[ind] == cv);
					{
						W.push_back(T[i]);
						break;
					}
				}
				swap(T, W);
				if (i != T.size())
				{
					return T;
				}
				else
				{
					cout << "NOT FIND" << endl;
					return T;
				}
					

			}
		}

	}
	vector<data2*> print(vector<data2*> T)
	{
		if (T.size() == 0 || T[0] == 0)
			return T;
		else
		{
			T[0]->pprint_name();
			if (select_what == "*")
				for(int i=0;i<T.size();i++)
					if(T[0]!=0)
				   T[0]->pprint();
		}
		return T;
	}
	string select_what="";
	string table="";
	string where;
	string having;
	string limit;
	string condition="";
	string cv = "";
	vector<data2*> T;

};
struct INSERT
{
	vector<string> insert_what ;
	string table = "";
	vector<string> insert_cond ;
	
	/*
	INSERT INTO table_name
		VALUES(value1, value2, value3, ...);
	第二种形式需要指定列名及被插入的值：

		INSERT INTO table_name(column1, column2, column3, ...)
		VALUES(value1, value2, value3, ...);
		*/
	INSERT(string a)
	{
		stringstream s(a);
		while (s >> a)
		{
			if (a == "VALUES")
			{
				s >> a;
				replace(a.begin(), a.end(), ',', ' ');
				replace(a.begin(), a.end(), '(', ' ');
				replace(a.begin(), a.end(), ')', ' ');
				s.clear();
				s << a;
				while (s >> a)
				{
					insert_what.push_back(a);

				}


			}
			else if (a == "INTO")
			{
				s >> a;
				table = a;
				if (a.find(','))
				{
					table = (a, 0, a.find('('));

					string e(a, a.find('('), a.size() - 1);
					replace(e.begin(), e.end(), ',', ' ');
					s.clear();
					s << e;
					while (s >> a)
					{
						insert_cond.push_back(a);
					}
				}
			}


		}
		if (check())
			exeq();
	}
	bool check()
	{
		//check table
		if (set_table.find(table) == set_table.find(table))
		{
			cout << "there is no input table" << endl;
			return 0;
		}
		//check condition
		for(string condition: insert_cond)
		if (data2::find_col(condition) == -1)
		{
			cout << "there is no input condition" << endl;
			return 0;
		}
		//check selectwhat
		
	
		if (insert_what.size()>data2::get_size())
		{
				cout << "there is more input value" << endl;
				return 0;
		}
		
		return 1;


	}
	vector<data2*>exeq()
	{
		if (insert_cond.size() == 0)
		{
			string v;
			if ( data2::find_col(data2::getmkey()) == -1)
			{
				cout << "lack the main_key" << endl;
					throw -1;
			}
			
			vector<string> rr(data2::get_size(), "");
			int q = 0;
			for (string et : insert_cond)
			{
				rr[data2::find_col(et)] = insert_what[q];
				if (et == data2::getmkey())
					v = insert_what[q];
				q++;
			}
			if (q != insert_what.size())
				cout << "wrong flecte conditong and value" << endl;
			data2 tt(rr);
			set_table[table].add(tt, v);
		}
		else
		{
			string va = insert_what[ data2::find_col((data2::getmkey())) ];
			data2 tt(insert_what);
			set_table[table].add(tt, va);
		}

	}
		//	print(exesql());


	


};
struct UPDATE
{
	UPDATE(string a)
	{
		stringstream s(a);
		while (s >> a)
		{
			if (a == "UPDATE")
			{
				s >> a;
				table = a;
			}
			else if (a == "SET")
			{
				string con(a, 0, condition.find(",") - 1);
				condition = con;
				con = (a, condition.find("=") + 1, condition.size() - 1);
				cv = con;
			}
			else if (a == "WHERE")
			{
				s >> a;

				string con(a, 0, condition.find("=") - 1);
				condition = con;
				con = (a, condition.find("=") + 1, condition.size() - 1);
				cv = con;
			}

		}
		if (check())
			pre_print(exesql());


	}
	vector<string> pre_print(vector<data2*>T)
	{
		T[0]->pprint_name();
		for (int i = 0; i < T.size(); i++)
			if (T[i] != 0)
				T[i]->pprint();
	}
	bool check()
	{
		//check table
		if (set_table.find(table) == set_table.find(table))
		{
			cout << "there is no input table" << endl;
			return 0;
		}
		//check condition

		if (data2::find_col(condition) == -1)
		{
			cout << "there is no input condition" << endl;
			return 0;
		}
		//check selectwhat
		string con = update_what;
		con.replace(con.begin(), con.end(), ',', ' ');
		stringstream s(con);
		while (s >> con)
		{
			if (data2::find_col(con) == -1)
			{
				cout << "there is no input select_aim" << endl;
				return 0;
			}
		}
		return 1;


	}
	vector<data2*> exesql()
	{
		vector<data2*> T;
		if (condition == "" && update_what == "*")
		{
			T = set_table[table].visit();
			return T;
		}
		else
		{
			if (set_table[table].slot_table.find(condition) != set_table[table].slot_table.end()
				|| condition == data2::getmkey())
			{
				cout << " using slot" << endl;
				if (condition == data2::getmkey())
				{

					T.push_back(set_table[table].find(cv));
				}
				else
				{

					T.push_back(set_table[table].get_slot(condition)->find(cv));
				}
				if (T[0] == 0)
				{
					cout << "NOT FIND" << endl;
					return T;
				}
				else
				{
					return T;
				}
			}
			else
			{
				vector<data2*> W;
				cout << "no hit slot using visit" << endl;
				T = set_table[table].visit();
				int i;
				for (i = 0; i < T.size(); i++)
				{
					int ind = data2::find_col(condition);
					if (T[i]->d[ind] == cv);
					{
						W.push_back(T[i]);
						break;
					}
				}
				swap(T, W);
				if (i != T.size())
				{
					return T;
				}
				else
				{
					cout << "NOT FIND" << endl;
					return T;
				}


			}
		}

	}
	string update_what = "";
	string table = "";
	string where;
	string having;
	string alter_name = "";
	string alter_value = "";
	string limit;
	string condition = "";
	string cv = "";
};
struct CREATE
{
	/*
	CREATE TABLE 表名称
	(
		列名称1 数据类型,
		列名称2 数据类型,
		列名称3 数据类型,
		....
	)
	*/
	CREATE(string A)
	{
		
		stringstream s(A);
		while (s >> A);
		{
			if (A == "TABLE")
			{
				s >> A;
				tablename = A;
			}
		}
		string B;
		string C;
		do 
		{
			cin >> A;
			if (A != "(")
			{
				cin >> B;
				if (A == "primary_key")
				{
					cin >> C;
					if(m_k=="")
					m_k = B;
					else
					{
						cout << "only one primary key" << endl;
						throw;
					}
					col.push_back(B);
					col_type.push_back(C);
				}
				else
				{
					col.push_back(A);
					col_type.push_back(B);
				}
			}
		} while (A == ")");
		data2::creat_table(col, m_k);
	   table<data2, string> tt(5);
		set_table[tablename] = tt;
	}

	string tablename="";
	string m_k="";
	vector<string> col;
	vector<string> col_type;

};
struct DELETE
{
	DELETE(string A)
	{
		SELECT S(A);

		vector<data2*>T = S.T;
		if (T[0] != 0)
			
			set_table[S.table].del(T[0]->d[    T[0]->find_col(T[0]->getmkey())  ]);
	}
};




/*
void add(vector<string> &sql)
{
	if (set_table.find(sql[2]) != set_table.end())
	{
		try
		{
			data2 t(sql[sql.size()-1]);
			set_table[sql[2]].add(t, sql[4]);
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
		set_table[sql[2]].del((sql[6]));
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
		if (data1::find_col(sql[5])>=0)
		{
			if (set_table[sql[3]].slot_table.find(sql[5]) != set_table[sql[3]].slot_table.end()
				|| data1::find_col(sql[5])==0)
			{
				cout << "search by index " << sql[5] << endl;
				if (data1::find_col(sql[5]) != 0)
				{
					//(set_table[sql[3]].slot_table[sql[5]]).find(stoi(sql[5]));
				}
				else
					//set_table[sql[3]].find(stoi(sql[sql.size() - 1]))->pprint();

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
		set_table[sql[2]].alt(data2(),sql[sql.size()-1]);
		cout << "alt scuess" << endl;
	}
	else
	{
		cout << "invalid table" << endl;
	}
}
void creat(string sql)
{

}
*/
int main()
{

	vector<string> sql;
	table<data2, string> A(5);
	set_table["A"] = A;
	while (1)
	{
		sql.clear();
		cout << "please input sql" << endl;
		
		string C;
		getline(cin, C);
		if (C == "exit()")
			exit(0);
		stringstream S(C);
		while (S >> C)
		{
			sql.push_back(C);
		}
	
		if (0)
		{
		}
		else
		{
			if (sql[0] == "CREATE")
			{
				//creat(sql);
				//select * FROM A where id = 1
			}
		
			if (sql[0] == "select")
			{
				//find(sql);
				//select * FROM A where id = 1
			}
			else if (sql[0] == "delete")
			{
				//del(sql);
			}
			else if (sql[0] == "update")
			{
				//alt(sql);
			}
			else if (sql[0] == "insert")
			{
				//ins(sql);
				//insert INTO A VALUES 1 1 25 asdasd
			}
			else
			cout << "wrong input sql" << endl;

		}


	}
	return 0;
}
