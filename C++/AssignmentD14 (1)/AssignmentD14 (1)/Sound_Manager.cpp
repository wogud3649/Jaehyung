#include "framework.h"

Sound_Manager* Sound_Manager::instance = nullptr;

Sound_Manager::Sound_Manager()
{
	_knightAttackSound = "�� ���� �ֵѷ����ϴ�.";
	_archerAttackSound = "�� Ȱ�� �����ϴ�.";
	_mageAttackSound = "�� ���̾�� ����߽��ϴ�.";
	_goblinAttackSound = "�� �޷�������ϴ�.";
	_deadSound = "�� �׾����ϴ�.";
	_damagedSound = "�� �������� �Ծ����ϴ�.";
	_alreadyDeadSound = "�� �̹� �׾� �ֽ��ϴ�.";
	_playerWinSound = "�÷��̾ �¸��߽��ϴ�.";
	_playerLoseSound = "�÷��̾ �����ϴ�.";
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
	cout << creature->GetName() << "�� "<< other->GetAttack() << _damagedSound << " ("<< creature->GetName() <<"����ü�� : " << creature->GetHp() << ")" << endl;
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