#pragma once

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTER_X 640
#define CENTER_Y 360
#define CENTER Vector2(CENTER_X, CENTER_Y)

#define PI 3.141592
#define GRAVITY 40

using CONDITION = unsigned char;
#define SCAR CONDITION(1)
#define POISON CONDITION(1<<1)
#define BURN CONDITION(1<<2)
#define FREEZE CONDITION(1<<3)
#define STUN CONDITION(1<<4)
#define REVENGE CONDITION(1<<5)
#define MIRAGE CONDITION(1<<6)
#define FATALITY CONDITION(1<<7)

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

#define EFFECT EffectManager::GetInstance()

#define DATA_M DataManager::GetInstance()

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

struct ItemInfo
{
	ItemInfo() {}

	ItemInfo(UINT itemCode, ItemType itemType, UINT rare, string name, UINT price, UINT ad, UINT ap, UINT sd, UINT hp, UINT def, UINT drd, UINT as, UINT ccd,
		UINT scd, UINT crd, UINT crp, UINT od, UINT ocd, CONDITION condition, UINT frameX = 0, UINT frameY = 0)
		: itemCode(itemCode), itemType(itemType), rare(rare), name(name), price(price), ad(ad), ap(ap), sd(sd), hp(hp), def(def), drd(drd), as(as), ccd(ccd),
		scd(scd), crd(crd), crp(crp), od(od), ocd(ocd), condition(condition), frameX(frameX), frameY(frameY)
	{}

	void SetEmpty() { itemCode = 0, itemType = ItemType::NONE, rare = 0, name = "", price = 0, ad = 0, ap = 0, sd = 0, hp = 0, def = 0, drd = 0, as = 0, ccd = 0,
		scd = 0, crd = 0, crp = 0, od = 0, ocd = 0, condition = 0, frameX = 0, frameY = 0; }
	bool operator==(const ItemInfo& other)
	{
		if (itemCode != other.itemCode)
			return false;
		return true;
	}

	UINT itemCode = 0;					// ItemCode
	ItemType itemType = ItemType::NONE;	// ItemType
	UINT rare = 0;						// Rarity
	string name = "";					// Name
	UINT price = 0;						// Price
	UINT ad = 0;						// AttackDamage
	UINT ap = 0;						// AbilityPower
	UINT sd = 0;						// SkillDamage
	UINT hp = 0;						// HP
	UINT def = 0;						// Defense
	UINT drd = 0;						// DamageReduction
	UINT as = 0;						// AttackSpeed
	UINT ccd = 0;						// ChangeCooldown
	UINT scd = 0;						// SkillCooldown
	UINT crd = 0;						// CriticalDamage
	UINT crp = 0;						// CriticalPercent
	UINT od = 0;						// OrbDamage
	UINT ocd = 0;						// OrbCooldown
	CONDITION condition = 0;			// Conditions BitFlag
	UINT frameX = 0;					// FrameX
	UINT frameY = 0;					// FrameY
};