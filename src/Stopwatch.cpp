#include "inc/Stopwatch.h"

#include <chrono>

Stopwatch::Stopwatch(void)
{

}

Stopwatch::~Stopwatch(void)
{

}

void Stopwatch::Start(void)
{
	this->startTime = std::chrono::high_resolution_clock::now();
}

void Stopwatch::Stop(void)
{
	this->stopTime = std::chrono::high_resolution_clock::now();
}

int32_t Stopwatch::GetTimestep(void)
{
	this->Stop();
	return std::chrono::duration_cast<std::chrono::milliseconds>(this->stopTime - this->startTime).count();
}
