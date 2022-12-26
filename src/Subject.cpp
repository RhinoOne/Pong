#include "..\include\Subject.h"

using namespace std::placeholders;

void UpdateCurrentObs(Observer* obs, Subject* sub, float dt)
{
	obs->Update(sub, dt);
}

void Subject::Attach(Observer* obs)
{
	mObserves_.push_back(obs);
}
void Subject::Detach(Observer* obs)
{
	mObserves_.remove(obs);
}
void Subject::Notify(float a)
{

	std::for_each(mObserves_.begin(),
		mObserves_.end(), std::bind(UpdateCurrentObs, _1, this, a));
}
