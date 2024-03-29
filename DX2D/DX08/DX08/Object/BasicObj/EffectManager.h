#pragma once
class EffectManager
{
private:
	EffectManager();
	~EffectManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new EffectManager();
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static EffectManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
	}

	void AddEffect(wstring file, Vector2 maxFrame, Vector2 size, float speed = 0.1f, Action::Type type = Action::Type::END, UINT poolCount = 15);
	void Play(string name, Vector2 pos);

	void Update();
	void Render();

private:
	static EffectManager* _instance;

	unordered_map<string, vector<shared_ptr<Effect>>> _effectTable;
};

