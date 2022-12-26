#ifndef FRAME_TIME_H
#define FRAME_TIME_H

#include<chrono>
#include "Subject.h"

class FrameTime : public Subject
{
public:
	typedef std::chrono::steady_clock::time_point Time;
	Time StartTime() { return std::chrono::high_resolution_clock::now(); }
	Time StopTime() { return std::chrono::high_resolution_clock::now(); }
};

#endif