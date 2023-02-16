#pragma once

// 1. 소리를 출력
// 2. 단 한개만 존재
// 3. 어디서든 접근
// 4. 생성주기를 내가 마음대로

// -> SingleTon 디자인 패턴

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
	static void CreateInstance() // 정적함수... 지역에서 static 변수만 쓸 수 있음
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
	static Sound_Manager* instance; // -> SoundManager::instance는 전체 프로그램에서 단 하나

	string _warriorSound;
	string _mageSound;
	string _archerSound;
};