#pragma once

class Customer
{
private:
	int arriveTime;
	int serverTime;
	int customerId;
	int waitTime;
	int customerIdentity;
	int ProRandNum();
public:
	Customer();
	int getArriveTime();
	int generArriveTime();
	int getServerTime();
	int generServerTime();
	int getCustomerId();
	int generCustomerId();
	int getCustomerIdentity();
	void setWaitTime(int wait);
	int getWaitTime();
	
	void setCustomerIdentity(int identity);
};

