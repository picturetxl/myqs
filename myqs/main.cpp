
#include <iostream>
#include "QueueSystem.h"
#include <ctime>
#include <Windows.h>
using namespace std;

void initCustomerInfo(vector<Customer> &customers)
{
	for (int i = 0; i < 20; i++)
	{
		Customer a;
		customers.push_back(a);
	}
}
int main()
{
	vector<Customer> initCus;
	//initCustomerInfo(initCus);
	/*for (auto a : initCus)
	{
		cout << a.getCustomerId() << endl;
	}*/



	

 	QueueSystem qs;
	qs.init(5);
	qs.setMaxWaitTime(200);
	qs.setInterval(10);
	qs.simulate(100);
	return 0;
}