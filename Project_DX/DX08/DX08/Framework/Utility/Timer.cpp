#include "framework.h"
#include "Timer.h"

Timer* Timer::_instance = nullptr;

Timer::Timer()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

	_timeScale = 1.0 / (double)_periodFrequency;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	
	_deltaTime = (double)(_curTime - _lastTime) * _timeScale;

	if (_lockFPS != 0)
	{
		while (_deltaTime < (1.0 / _lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			_deltaTime = (double)(_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;

	_frameCount++;
	_oneSecCount += _deltaTime;

	// 1초 마다 갱신해야 되는 정보
	if (_oneSecCount >= 1)
	{
		_oneSecCount = 0;
		_frameRate = _frameCount;

		_frameCount = 0;
	}

	_runTime += _deltaTime;
}
