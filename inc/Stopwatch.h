#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch
{
private:
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point stopTime;

public:
	Stopwatch(void);
	~Stopwatch(void);

	void Start(void);
	void Stop(void);
	int32_t GetTimestep(void);
};

#endif
