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

void EffectManager::Play(string name, Vector2 pos)
{
	if (_effectTable.count(name) == 0)
		return;

	auto iter = std::find_if(_effectTable[name].begin(), _effectTable[name].end(), [](const shared_ptr<Effect>& effect)->bool
		{
			return effect->IsActive() == false;
		});

	if (iter != _effectTable[name].end())
	{
		(*iter)->Play(pos);
	}
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
