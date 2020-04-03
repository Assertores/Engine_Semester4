#include <chrono>

#include "helper/Clock.h"

GE_DEFINE_SINGLETON(Clock);

using namespace std::chrono;

void Clock::Initialize()
{
	auto currentTimePoint = duration_cast<milliseconds>(
		high_resolution_clock::now().time_since_epoch()
	);

	this->miLastFrameTime = static_cast<u64>(currentTimePoint.count());
	this->miEngineStartTime = this->miLastFrameTime;
}

u64 Clock::GetElapsedTime(void)
{
	auto currentTimePoint = duration_cast<milliseconds>(
		high_resolution_clock::now().time_since_epoch()
	);

	auto elapsedTime = currentTimePoint.count() - this->miLastFrameTime;
	this->miLastFrameTime = static_cast<u64>(currentTimePoint.count());
	return static_cast<u64>(elapsedTime);
}

real Clock::GetTimeScale(void) const
{
	return this->mfTimeScale;
}

u64 Clock::GetTimeSinceStart(void) const
{
	auto currentTimePoint = duration_cast<milliseconds>(
		high_resolution_clock::now().time_since_epoch()
	);

	return (currentTimePoint.count() - this->miEngineStartTime);
}

void Clock::SetTimeScale(real timeScale)
{
	this->mfTimeScale = timeScale;
}
