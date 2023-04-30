#pragma once
class SoundManager
{
private:
	struct SoundInfo
	{
		FMOD::Sound* _sound = nullptr;
		FMOD::Channel* _channel = nullptr;

		SoundInfo() {}
		~SoundInfo() {}
	};

	SoundManager();
	~SoundManager();
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new SoundManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static SoundManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();
	void Add(string key, string file, bool bgm = false);
	void Play(string key, bool bgm = false, float volume = 0.05f);
	void StopBgm();
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);
	void SetVolume(string key, float volume);

	bool IsPlaySound(string key);

private:
	void AddSounds();

	static SoundManager* _instance;

	FMOD::System* _soundSystem = nullptr;

	unordered_map<string, shared_ptr<SoundInfo>> _soundMap;
	const int MAX_CHANNEL = 15;

	string _curBgm = "";
};