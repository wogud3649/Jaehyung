#include "framework.h"

Sound_Manager* Sound_Manager::instance = nullptr;

Sound_Manager::Sound_Manager()
{
	_knightAttackSound = "이 검을 휘둘렀습니다.";
	_archerAttackSound = "이 활을 쐈습니다.";
	_mageAttackSound = "이 파이어볼을 사용했습니다.";
	_goblinAttackSound = "이 달려들었습니다.";
	_deadSound = "이 죽었습니다.";
	_damagedSound = "의 데미지를 입었습니다.";
	_alreadyDeadSound = "은 이미 죽어 있습니다.";
	_playerWinSound = "플레이어가 승리했습니다.";
	_playerLoseSound = "플레이어가 졌습니다.";
}

Sound_Manager::~Sound_Manager()
{
}

void Sound_Manager::CreateInstance()
{
	if (instance == nullptr)
		instance = new Sound_Manager();
}

void Sound_Manager::DeleteInstance()
{
	if (instance != nullptr)
		delete instance;
}

Sound_Manager* Sound_Manager::GetInstance()
{
	if (instance != nullptr)
		return instance;
}

void Sound_Manager::KnightAttack(class Creature* creature)
{
	cout << creature->GetName() << _knightAttackSound << endl;
}

void Sound_Manager::ArcherAttack(class Creature* creature)
{
	cout << creature->GetName() << _archerAttackSound << endl;
}

void Sound_Manager::MageAttack(class Creature* creature)
{
	cout << creature->GetName() << _mageAttackSound << endl;
}

void Sound_Manager::GoblinAttack(class Creature* creature)
{
	cout << creature->GetName() << _goblinAttackSound << endl;
}

void Sound_Manager::Damaged(Creature* creature, Creature* other)
{
	cout << creature->GetName() << "이 "<< other->GetAttack() << _damagedSound << " ("<< creature->GetName() <<"남은체력 : " << creature->GetHp() << ")" << endl;
}

void Sound_Manager::Dead(Creature* creature)
{
	cout << creature->GetName() << _deadSound << endl;
}

void Sound_Manager::AlreadyDead(Creature* creature)
{
	cout << creature->GetName() << _alreadyDeadSound << endl;
}

void Sound_Manager::PlayerWin()
{
	cout << _playerWinSound << endl;
}

void Sound_Manager::PlayerLose()
{
	cout << _playerLoseSound << endl;
}