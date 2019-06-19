#include "Customer.h"
#include <cstdlib>
#include <time.h>
#include <random>

int Customer::ProRandNum()
{
	std::uniform_real_distribution<double> distribution(1, 100);
	std::random_device rd;
	std::default_random_engine generator(rd());
	return distribution(generator);

}

Customer::Customer()
{
	this->arriveTime = this->generArriveTime();
	this->serverTime = this->generServerTime();
	this->customerId = this->generCustomerId();
	this->waitTime = 0;
}

int Customer::getArriveTime()
{
	return this->arriveTime;
}

int Customer::generArriveTime()
{
	return ProRandNum();
}
int Customer::getServerTime()
{
	return this->serverTime;
}
int Customer::generServerTime()
{
	return ProRandNum();
}

int Customer::getCustomerId()
{
	return this->customerId;
}

int Customer::generCustomerId()
{
	return ProRandNum();
}

int Customer::getCustomerIdentity()
{
	return this->customerIdentity;
}

void Customer::setWaitTime(int wait)
{
	this->waitTime = wait;
}

int Customer::getWaitTime()
{
	return this->waitTime;
}

void Customer::setCustomerIdentity(int identity)
{
	this->customerIdentity = identity;
}
