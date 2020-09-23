#include<shared_mutex>
#include<mutex>
#include<thread>
#include<iostream>
using namespace std;
class ATX
{
public:
	int a = 0; int b = 0; int v = 0;
	shared_mutex mutex;
	
	ATX* getreadp()
	{
		mutex.lock_shared();
		return this;
	}
	ATX* retreadp()
	{
		mutex.unlock_shared();
		return this;
	}
	ATX* getwritep()
	{
		mutex.lock();
		return this;
	}
	ATX* retwritep()
	{
		mutex.unlock();
		return this;
	}
	void ppr()
	{

		for (int i = 0; a< 5000; i++)
		{
			a++;
			getwritep();
			cout << a<<" "<<i<<endl;
			

		}
		
		cout << endl;
		retwritep();
	}
};

int main()
{
	ATX l;
	
	thread a1(&ATX::ppr,&l);
	thread a2(&ATX::ppr, &l);
	thread a3(&ATX::ppr, &l);
	a1.join();
	a2.join();
	a3.join();
	return 0;


}