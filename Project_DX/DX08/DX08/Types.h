#pragma once

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTER_X 640
#define CENTER_Y 360
#define CENTER Vector2(CENTER_X, CENTER_Y)

#define PI 3.141592
#define GRAVITY 50

#define LERP(s, e, t) s + (e - s) * t

#define DEVICE Device::GetInstance()->GetDevice()
#define DC Device::GetInstance()->GetDeviceContext()

#define SAMPLER StateManager::GetInstance()->GetSampler()
#define ALPHA StateManager::GetInstance()->GetAlpha()
#define ADDITIVE StateManager::GetInstance()->GetAdditive()

#define MOUSE_POS InputManager::GetInstance()->GetMousePos()
#define KEY_DOWN(k) InputManager::GetInstance()->Down(k)
#define KEY_PRESS(k) InputManager::GetInstance()->Press(k)
#define KEY_UP(k) InputManager::GetInstance()->Up(k)

#define DELTA_TIME Timer::GetInstance()->GetDeltaTime()
#define RUN_TIME Timer::GetInstance()->GetRunTime()

#define SRV_ADD(k) SRVManager::GetInstance()->AddSRV(k)

#define ADD_VS(k) ShaderManager::GetInstance()->AddVS(k)
#define ADD_PS(k) ShaderManager::GetInstance()->AddPS(k)

#define CAMERA Camera::GetInstance()

#define SCENE SceneManager::GetInstance()

enum Direction
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	LEFTUP,
	RIGHTUP,
	LEFTDOWN,
	RIGHTDOWN,
	NONE
};

struct HIT_RESULT
{
	bool isHit;
	Direction dir = NONE;
};

struct BlockData
{
	int index;
	Vector2 pos;
};

struct ColliderData
{
	Vector2 size;
	Vector2 pos;
};