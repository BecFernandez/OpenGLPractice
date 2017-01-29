#pragma once
class Subject;

class Observer
{
public:
	virtual ~Observer() {}
	virtual void OnNotify(Subject* subject) = 0;
};