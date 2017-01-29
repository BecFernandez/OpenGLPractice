#pragma once
#include <deque>
#include "Observer.h"

class Subject
{
private:
	std::deque<Observer*> observers;

public:
	void AddObserver(Observer* observerToAdd);
	void RemoveObserver(Observer* observerToRemove);

protected:
	void notify();
};