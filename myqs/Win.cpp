#include "Win.h"


Win::Win(int winid)
{
	this->state = State::IDLE;
	this->winID = winid;
}

Win::~Win()
{
	
}

int Win::getWinState()
{
	return state;
}

int Win::getWinId()
{
	return this->winID;
}
