#pragma once
#include <deque>
#include "Observer.h"

class Subject
{
private:
	std::deque<Observer*> observers;

public:
	virtual ~Subject() {}
	void AddObserver(Observer* observerToAdd);
	void RemoveObserver(Observer* observerToRemove);
	void ClearObserverList() { observers.clear(); }

protected:
	void notify();
};