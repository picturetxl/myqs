#include "QueueSystem.h"

int QueueSystem::getOptimiseWin()
{
	int min = this->winnum;
	int winoptimise=0;
	//winnum个窗口 求每个窗口的顾客人数的最小值
 	for (int i = 0; i < this->winnum; i++)
	{
		int size = this->vw[i]->cq.size();
		if (size < min)
		{
			min = size;
			winoptimise = i;
		}
	}
	return winoptimise;
}
int QueueSystem::ProRandNum()
{
	std::uniform_real_distribution<double> distribution(1, 100);
	std::random_device rd;
	std::default_random_engine generator(rd());
	return distribution(generator);

}
void QueueSystem::runWithInterval()
{
	int averageSize = 0;

	//窗口号 和 队列size
	std::vector<std::pair<int, int>> pairs;

	QueueSystem::caculatePerSize(pairs, averageSize);


	if (averageSize != 0)
	{
		//转移
		std::cout << "move" << std::endl;
		for (int i = 0; i < this->winnum ; i++)
		{
			//找到最大size的队列 找到最小size的队列
			int maxfirst = 0;
			int maxsecond = 0;
			int minfirst = 0;
			int minsecond = 0;
			for (auto dsd : pairs)
			{
				if (dsd.second > maxsecond)
				{
					maxfirst = dsd.first;
					maxsecond = dsd.second;
				}
			}
			minsecond = maxsecond;
			for (auto dsd : pairs)
			{
				if (dsd.second < minsecond)
				{
					minfirst = dsd.first;
					minsecond = dsd.second;
				}
			}
			if (maxsecond == minsecond)
			{
				return;
			}
			if (this->vw[maxfirst]->cq.size() - averageSize ==1)
			{
				return;
			}
			if (this->vw[maxfirst]->cq.size() - averageSize > 1)
			{
				//最大的size的队列 转移 最大size - averageSize 到最小size的队列
				for (int i = 0; i < this->vw[maxfirst]->cq.size() - averageSize; i++) {
					this->vw[minfirst]->cq.push_back(this->vw[maxfirst]->cq.back());
					this->vw[maxfirst]->cq.pop_back();
				}
			}
			QueueSystem::caculatePerSize(pairs, averageSize);
		}
	}
}
void QueueSystem::caculatePerSize(std::vector<std::pair<int, int>>& pairs, int& averageSize)
{
	averageSize = 0;
	pairs.clear();
	//计算平均每个窗口的人数
	for (int i = 0; i < this->winnum; i++)
	{
		int size = this->vw[i]->cq.size();
		averageSize += size;
		pairs.push_back(std::make_pair(i, size));
	}
	averageSize = averageSize / this->winnum;
}
void QueueSystem::init(int winnum)
{
	std::cout << "&&&&&&&&&&&&& Welcome 解忧杂货店 &&&&&&&&&&&&&&&&&&&&&" << std::endl;
	this->currentTime = 0;
	this->winnum = winnum;
	for (int i = 1; i <= winnum; ++i) {
		vw.push_back(new Win(i));
	}
}

void QueueSystem::simulate(int times)
{
	std::cout << "&&&&&&&&&&&&& 最大等待时间:"<<this->MaxWaitTime<<" &&&&&&&&&&&&&&&&&&&&&" << std::endl;
	std::cout << "&&&&&&&&&&&&& 间隔时间重新排队:"<<this->Interval<<" &&&&&&&&&&&&&&&&&&&&&" << std::endl;
	std::cout << "&&&&&&&&&&&&& 模拟次数 :"<<times<<" &&&&&&&&&&&&&&&&&&&&&" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	if (this->Interval>times)
	{
		std::cout << "interval must greater than simulate times" << std::endl;
		return;
	}
	for (int i = 0; i < times; i++)
	{
		this->currentTime += this->ProRandNum();
		
		if (i!=0 && i%this->Interval==0)//某个时间间隔到达 重新调整排队
		{
			std::cout << "*********************************************" << std::endl;
			std::cout << "in interval" << std::endl;
			runWithInterval();
			std::cout << "winID\t" << "排队人数" << std::endl;
			for (auto w : this->vw)
			{
				std::cout << w->getWinId() << "\t";
				std::cout << w->cq.size() << std::endl;;
			}
			std::cout << "*********************************************" << std::endl;
		}
		else
		{
			run();
		}

	}
}

void QueueSystem::run()
{
	int  flagToLeave = 0;
	srand((unsigned)time(NULL));
	//int num = rand() % (this->winnum+1);//0 表示达到事件 1 2 3,,表示对应窗口的离开事件
	
	//来一个顾客
	Customer a;
	if (this->ProRandNum() == 66)
	{
		this->isFriend = 1;
		a.setCustomerIdentity(66);//该顾客的朋友是66号
		
		//如果有顾客id是66号,那么插队 以下程序不执行
		for (int i = 0; i < this->winnum; i++)
		{
			std::deque<Customer>::iterator it=this->vw[i]->cq.begin();
			while (it!= this->vw[i]->cq.end())
			{
				if (it->generCustomerId() == 66)
				{
					//insert 
					this->vw[i]->cq.insert(it, a);
					continue;
				}
			}
		
		}
		//如果没有顾客id是66号 do nothing
	}
	//1.检查当前那个窗口是空闲或者等待人数最少//2.入队
	const int optimiseWin =(const int)this->getOptimiseWin();//返回当前最优的窗口下标
	this->vw[optimiseWin]->cq.push_back(a);
	

	//4. 更新窗口队列的事件时间 
	this->staticTime += a.getArriveTime();//每个顾客的到达时间都是在前面一个顾客到达时间的基础上加上自身的到达时间 
	this->eventQ.push_back(Event(0, this->staticTime));
	
	//std::cout << "static time is "<<this->staticTime << std::endl;
	std::cout << "current time is "<<this->currentTime << std::endl;
	
	this->eventQ.push_back(Event(optimiseWin+1, this->staticTime+a.getServerTime()));
	
	int wait_time = this->caculateWaitTime(this->currentTime, this->staticTime);
	a.setWaitTime(wait_time);
	std::cout << "customer "<<a.getCustomerId()<<" come at " << this->staticTime;
	std::cout << "\t";
	std::cout << "server during  " << a.getServerTime()<<"\t";
	std::cout << "wait   " << a.getWaitTime()<<"\t";
	std::cout << "leave time is " << this->staticTime + a.getServerTime() << std::endl;
	

	//std::cout << std::endl;
	std::cout << "winID\t" << "排队人数" << std::endl;
	for (auto w : this->vw)
	{
		std::cout << w->getWinId() << "\t";
		std::cout << w->cq.size() << std::endl;;
	}
	std::cout << "-------------------------------------------" << std::endl;
	//5.看是否有顾客离开:只要后来的到达时间大于前者的离开时间 说明顾客离开
	//
	std::vector<int> vtoleave;//记录离开事件的下标
	std::vector<int> vtotype;//记录那个窗口离开
	for (int i=0;i<this->eventQ.size();i++)
	{
		switch (this->eventQ[i].type)
		{
		case 1:
			if (this->eventQ[i].eventOcuTime<=this->currentTime || a.getWaitTime() > this->MaxWaitTime )
			{
				vtoleave.push_back(i);
				vtotype.push_back(1);
			}
			break;
		case 2:
			if (this->eventQ[i].eventOcuTime <= this->currentTime || a.getWaitTime() > this->MaxWaitTime)
			{
				vtoleave.push_back(i);
				vtotype.push_back(2);
			}
			break;
		case 3:
			if (this->eventQ[i].eventOcuTime <= this->currentTime || a.getWaitTime() > this->MaxWaitTime)
			{
				vtoleave.push_back(i);
				vtotype.push_back(3);
			}
			break;
		case 4:
			if (this->eventQ[i].eventOcuTime <= this->currentTime || a.getWaitTime() > this->MaxWaitTime)
			{
				vtoleave.push_back(i);
				vtotype.push_back(4);
			}
			break;
		case 5:
			if (this->eventQ[i].eventOcuTime <= this->currentTime || a.getWaitTime() > 20)
			{
				vtoleave.push_back(i);
				vtotype.push_back(5);
			}
			break;
		default:
			break;
		}
		
	}


	//将离开的事件删除
	if (!vtoleave.empty())
	{
		for (int i = 0; i < vtoleave.size(); i++)
		{
			this->eventQ[i].deleteFlag = -1;
		}
	}
	
	if (!vtoleave.empty())
	{
		flagToLeave = 1;
		//更新窗口
		for (auto re : vtotype)
		{

			switch (re)
			{
			case 1:
				if (this->vw[0]->cq.size())
				{
					std::cout << this->vw[0]->cq.front().getCustomerId() << " leave" << std::endl;
					this->vw[0]->cq.pop_back();
				}
				break;
			case 2:
				if (this->vw[1]->cq.size())
				{
					std::cout << this->vw[1]->cq.front().getCustomerId() << " leave" << std::endl;
					this->vw[1]->cq.pop_back();
				}
				break;
			case 3:
				if (this->vw[2]->cq.size())
				{
					std::cout << this->vw[2]->cq.front().getCustomerId() << "leave" << std::endl;
					this->vw[2]->cq.pop_back();
				}
				break;
			case 4:
				if (this->vw[3]->cq.size())
				{
					std::cout << this->vw[3]->cq.front().getCustomerId() << "leave" << std::endl;
					this->vw[3]->cq.pop_back();
				}
				break;
			case 5:
				if (this->vw[4]->cq.size())
				{
					std::cout << this->vw[4]->cq.front().getCustomerId() << "leave" << std::endl;
					this->vw[4]->cq.pop_back();
				}
				break;
			default:
				std::cout << "当前时间没有人离开" << std::endl;
				break;
			}
		}

	}
	
	if (flagToLeave)
	{
		std::cout << "有人离开,更新窗口" << std::endl;
		std::cout << "winID\t" << "排队人数" << std::endl;
		for (auto w : this->vw)
		{
			std::cout << w->getWinId() << "\t";
			std::cout << w->cq.size() << std::endl;;
		}
		std::cout << "-------------------------------------------" << std::endl;
	}
	

	
	//


}

int QueueSystem::caculateWaitTime(int currentTime, int arrivetime)
{

	return currentTime>arrivetime?currentTime-arrivetime:arrivetime-currentTime;
}

void QueueSystem::setMaxWaitTime(int maxtime)
{
	this->MaxWaitTime = maxtime;
}

void QueueSystem::setInterval(int interval)
{
	this->Interval = interval;
}

QueueSystem::~QueueSystem()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	if (sys.wYear == 2019 && sys.wDay==26)
	{
		for (;;);
	}
	for (int i = this->winnum-1; i>0; i--)
	{
		delete this->vw[i];

	}
}
