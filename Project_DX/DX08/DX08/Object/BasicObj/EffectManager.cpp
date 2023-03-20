#include "framework.h"
#include "EffectManager.h"

EffectManager* EffectManager::_instance = nullptr;
EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::AddEffect(wstring file, Vector2 maxFrame, Vector2 size, float speed, Action::Type type, UINT poolCount)
{
	string name = string(file.begin(), file.end());
	name = name.substr(name.find_last_of("/") + 1);
	name = name.substr(0, name.find_last_of("."));

	if (_effectTable.count(name) > 0)
		return;

	for (int i = 0; i < poolCount; i++)
	{
		shared_ptr<Effect> effect = make_shared<Effect>(file, maxFrame, size, speed, type);
		effect->End();
		_effectTable[name].push_back(effect);
	}
}

void EffectManager::Play(string name, Vector2 pos, bool isLeftRight)
{
	if (_effectTable.count(name) == 0)
		return;

	vector<shared_ptr<Effect>>& v = _effectTable[name];
	auto iter = std::find_if(v.begin(), v.end(),
		[](const shared_ptr<Effect>& effect)-> bool
		{
			if (effect->IsActive() == false)
				return true;
			return false;
		});

	if (iter != v.end())
	{
		(*iter)->SetLeftRight(isLeftRight);
		(*iter)->Play(pos);
	}
}

void EffectManager::SetMidCallBack(string name, function<void(void)> event)
{
	vector<shared_ptr<Effect>>& v = _effectTable[name];

	for (auto effect : v)
		effect->SetMidCallBack(event);
}

void EffectManager::SetCallBack(string name, function<void(void)> event)
{
	vector<shared_ptr<Effect>>& v = _effectTable[name];
	
	for (auto effect : v)
		effect->SetCallBack(event);
}

void EffectManager::SetParent(string name, shared_ptr<Transform> parent)
{
}

void EffectManager::Update()
{
	for (auto pair : _effectTable)
	{
		for (auto effect : pair.second)
		{
			effect->Update();
		}
	}
}

void EffectManager::Render()
{
	for (auto pair : _effectTable)
	{
		for (auto effect : pair.second)
		{
			effect->Render();
		}
	}
}
