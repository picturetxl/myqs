#pragma once

#include <queue>
#include <deque>
#include "Customer.h"
enum State
{
	SERVICE,
	IDLE,
};
class Win
{
private:
	State state;//���ڵ�ҵ��״̬ 
	int winID;
public:
	Win(int winid);
	~Win();
	int getWinState();
	int getWinId();
	std::deque<Customer> cq;
};

