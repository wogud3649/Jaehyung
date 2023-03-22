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
	void Play(string name, Vector2 pos, bool isRight = false);
	void PlayAndMove(string name, bool isLeftRight = false);
	void Stop(string name);

	void SetMidCallBack(string name, function<void(void)> event, UINT index);
	void SetCallBack(string name, function<void(void)> event);

	void SetParent(string name, shared_ptr<Transform> parent);

	void Update();
	void Render();

private:
	static EffectManager* _instance;

	unordered_map<string, vector<shared_ptr<Effect>>> _effectTable;
};

