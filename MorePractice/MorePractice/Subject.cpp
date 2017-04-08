#include "Subject.h"
#include <iostream>

void Subject::AddObserver(Observer* observerToAdd)
{
	observers.push_back(observerToAdd);
}

void Subject::RemoveObserver(Observer* observerToRemove)
{
	std::deque<Observer*>::iterator it;
	for (it = observers.begin(); it != observers.end(); it++)
	{
		if (*it == observerToRemove)
		{
			observers.erase(it);
			break;
		}
	}
}

void Subject::notify()
{
	for (unsigned int i = 0; i < observers.size(); i++)
	{
		observers[i]->OnNotify(this);
	}
}