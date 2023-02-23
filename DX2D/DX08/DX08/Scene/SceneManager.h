#pragma once
class SceneManager
{
private:
	SceneManager();
	~SceneManager();
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new SceneManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static SceneManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();
	void Render();
	void PreRender();
	void PostRender();

	void Init();

	void SetScene(string name);

private:
	static SceneManager* _instance;

	unordered_map<string, shared_ptr<Scene>> _sceneTable;
	shared_ptr<Scene> _curScene;
};

