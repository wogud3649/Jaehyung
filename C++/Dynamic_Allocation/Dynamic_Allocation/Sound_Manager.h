#pragma once

// 1. �Ҹ��� ���
// 2. �� �Ѱ��� ����
// 3. ��𼭵� ����
// 4. �����ֱ⸦ ���� �������

// -> SingleTon ������ ����

class Sound_Manager
{
private:
	Sound_Manager()
	{
		_warriorSound = "Warrior_Attack!";
		_mageSound = "Mage Attack!";
		_archerSound = "Archer Attack!";
	}
	~Sound_Manager() {}

public:
	static void CreateInstance() // �����Լ�... �������� static ������ �� �� ����
	{
		if (instance == nullptr)
			instance = new Sound_Manager();
	}

	static void DeleteInstance()
	{
		if (instance != nullptr)
			delete instance;
	}

	static Sound_Manager* GetInstance()
	{
		if (instance != nullptr)
			return instance;
	}

	void WarriorAttack()
	{
		cout << _warriorSound << endl;
	}


private:
	static Sound_Manager* instance; // -> SoundManager::instance�� ��ü ���α׷����� �� �ϳ�

	string _warriorSound;
	string _mageSound;
	string _archerSound;
};