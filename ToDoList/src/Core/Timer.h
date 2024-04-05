#pragma once

#include <chrono>
#include <cmath>

class Timer
{
public:
	void Start()
	{
		m_StartTime = std::chrono::system_clock::now();
	}

	long long GetMircoseconds() const
	{
		auto endTime = std::chrono::system_clock::now();
		return (long long)std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_StartTime).count();
	}

	long long GetMilliseconds() const 
	{ 
		auto endTime = std::chrono::system_clock::now();
		return (long long)std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count(); 
	}

	long long GetSeconds() const
	{
		auto endTime = std::chrono::system_clock::now();
		return (long long)std::chrono::duration_cast<std::chrono::seconds>(endTime - m_StartTime).count();
	}

private:
	std::chrono::time_point<std::chrono::system_clock> m_StartTime;
};