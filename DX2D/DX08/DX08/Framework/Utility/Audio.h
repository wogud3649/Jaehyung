#pragma once
class Audio
{
private:
	struct SoundInfo
	{
		FMOD::Sound* _sound = nullptr;
		FMOD::Channel* _channel = nullptr;

		SoundInfo() {}
		~SoundInfo() {}
	};

	Audio();
	~Audio();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Audio();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Audio* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();
	void Add(string key, string file, bool bgm = false);
	void Play(string key, float volume = 1.0f);
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);
	void SetVolume(string key, float volume);
	
	bool IsPlaySound(string key);

private:
	static Audio* _instance;

	FMOD::System* _soundSystem = nullptr;

	unordered_map<string, shared_ptr<SoundInfo>> _soundMap;
	const int MAX_CHANNEL = 15;
};

