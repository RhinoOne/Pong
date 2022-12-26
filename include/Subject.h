#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <list>
#include <algorithm>
#include <functional>


class Subject
{
public:
	virtual void Attach(Observer*);
	virtual void Detach(Observer*);
	virtual void Notify(float);
	virtual ~Subject() {}

protected:
	Subject() {}

private:
	std::list<Observer*> mObserves_;
};
#endif

