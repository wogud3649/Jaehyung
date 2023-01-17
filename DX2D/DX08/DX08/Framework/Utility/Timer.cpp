#include "framework.h"
#include "Timer.h"

Timer* Timer::_instance = nullptr;

Timer::Timer()
{
	// Update : x축으로 1만큼 이동
	// A : 1초 동안 300번 Update -> x : 300 * (한번 업데이트 하는데 걸리는 시간 : 1 / 300) -> 1
	// B : 1초 동안 100번 Update -> x : 100 * (한번 업데이트 하는데 걸리는 시간 : 1 / 100) -> 1
	
	// 1초 동안 CPU의 진동수를 반환
	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency);

	// 현재 진동수
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
		// frameRate : FPS;
		// FPS : Frame Per Second

		_frameCount = 0;
	}

	_runTime += _deltaTime;
}
