#pragma once
class SRVManager
{
private:
	SRVManager();
	~SRVManager();
public:
	static void Create()
	{
		if (_instance == nullptr)
		{
			_instance = new SRVManager();
		}
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static SRVManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	shared_ptr<SRV> AddSRV(wstring file);

private:
	static SRVManager* _instance;

	unordered_map<wstring, shared_ptr<SRV>> _srvTable;
};

