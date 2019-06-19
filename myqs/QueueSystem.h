#pragma once
#include <queue>
#include <vector>
#include "Win.h"
#include "Customer.h"
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <random>
#include  <map>
#include <utility>
#include <Windows.h>
struct Event {
	int type;
	int eventOcuTime;
	int deleteFlag;
	Event(int _type,int eventQcutime) {
		type = _type;
		eventOcuTime = eventQcutime;
		deleteFlag = 0;
	}
};
class QueueSystem
{
private:
	int winnum;
	int getOptimiseWin();
	int ProRandNum();
	void runWithInterval();
	void caculatePerSize(std::vector<std::pair<int, int>> &pairs,int &averageSize);

public:
	int MaxWaitTime;
	int Interval;
	int staticTime;//�����ۼӵĵ���ʱ�� ��Ȼ������ɵ�ʱ����ܱ���һ��С ����Ҫ�����ۼ�
	std::vector<Event> eventQ;
	std::vector<Win*> vw;
	int currentTime;
	int isFriend;
	//std::queue<Customer*> customerQ;
	void init(int winnum);
	void simulate(int times);
	void run();
	int caculateWaitTime(int currentTime,int arrivetime);
	void setMaxWaitTime(int maxtime);
	void setInterval(int interval);
	
	~QueueSystem();

};

