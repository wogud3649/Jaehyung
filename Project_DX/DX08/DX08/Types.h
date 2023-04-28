#pragma once

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTER_X 640
#define CENTER_Y 360
#define CENTER Vector2(CENTER_X, CENTER_Y)

#define PI 3.141592
#define GRAVITY 40

using ATTRIBUTE = unsigned char;
#define SCAR ATTRIBUTE(1)
#define POISON ATTRIBUTE(1<<1)
#define BURN ATTRIBUTE(1<<2)
#define FREEZE ATTRIBUTE(1<<3)
#define STUN ATTRIBUTE(1<<4)
#define REVENGE ATTRIBUTE(1<<5)
#define MIRAGE ATTRIBUTE(1<<6)
#define FATALITY ATTRIBUTE(1<<7)

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

#define ASSERT(hr) assert(SUCCEEDED(hr))

#define EFFECT EffectManager::GetInstance()

#define DATA_M DataManager::GetInstance()

#define UI GameManager::GetInstance()->GetCharacterUI()
#define INVENTORY GameManager::GetInstance()->GetInventory()
#define BACKGROUND GameManager::GetInstance()->GetBackground()
#define PLAYER GameManager::GetInstance()->GetPlayer()
#define STORE GameManager::GetInstance()->GetStore()
#define YGGDRASIL GameManager::GetInstance()->GetYggdrasil()
#define FADEPANEL GameManager::GetInstance()->GetFadePanel()

#define INTERACTOBJ InteractObjManager::GetInstance()

#define SOUND SoundManager::GetInstance()

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

enum class ItemType
{
	NONE,
	HEAD,
	EQUIPMENT,
	ORB,
	POTION
};

enum class Rarity
{
	NONE,
	NORMAL,
	RARE,
	UNIQUE,
	LEGENDARY,
	RARITYSIZE
};

struct HIT_RESULT
{
	bool isHit = false;
	Direction dir = Direction::NONE;
	Vector2 distance = { 0,0 };
};

struct BlockData
{
	Vector2 pos;
	Vector2 curFrame;
};

struct ColliderData
{
	Vector2 size;
	Vector2 pos;
};

struct StatAttributes
{
	StatAttributes() {}
	StatAttributes& operator+=(const StatAttributes& other)
	{
		this->ad = this->ad + other.ad;
		this->ap = this->ap + other.ap;
		this->hp = this->hp + other.hp;
		this->def = this->def + other.def;
		this->ccd = this->ccd + other.ccd;
		this->scd = this->scd + other.scd;
		this->crp = this->crp + other.crp;
		this->attribute = this->attribute | other.attribute;
		
		return (*this);
	}

	UINT ad = 0;						// AttackDamage
	UINT ap = 0;						// AbilityPower
	UINT hp = 0;						// HP
	UINT def = 0;						// Defense
	UINT ccd = 0;						// ChangeCooldown
	UINT scd = 0;						// SkillCooldown
	UINT crp = 0;						// CriticalPercent
	ATTRIBUTE attribute = 0;			// Attribute BitFlag
};

struct ItemInfo
{
	ItemInfo() {}

	ItemInfo(UINT itemCode, ItemType itemType, Rarity rarity, string name, UINT price, UINT ad, UINT ap, UINT hp,
		UINT def, UINT ccd, UINT scd, UINT crp, ATTRIBUTE attribute, UINT frameX = 0, UINT frameY = 0)
		: itemCode(itemCode), itemType(itemType), rarity(rarity), name(name), price(price), frameX(frameX), frameY(frameY)
	{
		statAttributes.ad = ad;
		statAttributes.ap = ap;
		statAttributes.hp = hp;
		statAttributes.def = def;
		statAttributes.ccd = ccd;
		statAttributes.scd = scd;
		statAttributes.crp = crp;
		statAttributes.attribute = attribute;
	}

	void SetEmpty() {
		itemCode = 0;
		itemType = ItemType::NONE;
		rarity = Rarity::NONE;
		name = "";
		price = 0;
		statAttributes.ad = 0;
		statAttributes.ap = 0;
		statAttributes.hp = 0;
		statAttributes.def = 0;
		statAttributes.ccd = 0;
		statAttributes.scd = 0;
		statAttributes.crp = 0;
		statAttributes.attribute = 0;
		frameX = 0;
		frameY = 0;
	}

	bool operator==(const ItemInfo& other)
	{
		if (itemCode != other.itemCode)
			return false;
		return true;
	}

	UINT itemCode = 0;					// ItemCode
	string name = "";					// Name
	ItemType itemType = ItemType::NONE;	// ItemType
	Rarity rarity = Rarity::NONE;						// Rarity
	UINT price = 0;						// Price
	StatAttributes statAttributes = StatAttributes();		// StatAttributes
	UINT frameX = 0;					// FrameX
	UINT frameY = 0;					// FrameY
};