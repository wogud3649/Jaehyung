#pragma once
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTER_X 640
#define CENTER_Y 360
#define CENTER Vector2(CENTER_X, CENTER_Y)

#define PI 3.141592
#define GRAVITY 30

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

#define EFFECT EffectManager::GetInstance()

#define TIMER Timer::GetInstance()

#define AUDIO Audio::GetInstance()

#define CAMERA Camera::GetInstance()

#define SCENE SceneManager::GetInstance()

#define ASSERT(hr) assert(SUCCEEDED(hr))

#define DATA_M DataManager::GetInstance()

// ÆùÆ®
#define FONT_YOON L"" // TODO

using CallBack = std::function<void(void)>;
using CallBack_String = std::function<void(string)>;

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

struct ItemInfo
{
	ItemInfo() {}
	ItemInfo(string name, int price, int atk, int def, int rare, int frameX = 10, int frameY = 4)
	: name(name), price(price), atk(atk), def(def), rare(rare), frameX(frameX), frameY(frameY)
	{}

	void SetEmpty() { name = "", price = 0, atk = 0, def = 0, rare = 0, frameX = 10, frameY = 4; }
	bool operator==(const ItemInfo& other)
	{
		if (name != other.name)
			return false;
		return true;
	}

	string name;
	int price = 0;
	int atk = 0;
	int def = 0;
	int rare = 0;
	int frameX = 10;
	int frameY = 4;
};