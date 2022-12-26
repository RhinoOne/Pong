#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer
{
public:
	virtual void Update(Subject*, float) = 0;
	virtual ~Observer() {}
protected:
	Observer() {}
};

#endif
