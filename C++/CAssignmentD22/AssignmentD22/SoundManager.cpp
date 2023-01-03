#include "Framework.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::CreateInstance()
{
    if (instance == nullptr)
        instance = new SoundManager();
}

void SoundManager::DeleteInstance()
{
    if (instance != nullptr)
        delete instance;
}

SoundManager* SoundManager::GetInstance()
{
    if (instance != nullptr)
        return instance;
}

void SoundManager::KnightAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim)
{
    cout << attacker->GetName() << "��(��) " << victim->GetName() << "���� ���� �ֵѷ����ϴ�." << endl;
}

void SoundManager::ArcherAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim)
{
    cout << attacker->GetName() << "��(��) " << victim->GetName() << "���� Ȱ�� �����ϴ�." << endl;
}

void SoundManager::MageAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim)
{
    cout << attacker->GetName() << "��(��) " << victim->GetName() << "���� ���̾�� ���Ƚ��ϴ�." << endl;
}

void SoundManager::GoblinAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim)
{
    cout << attacker->GetName() << "��(��) " << victim->GetName() << "���� �޷�������ϴ�." << endl;
}

void SoundManager::GoblinKingAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim)
{
    cout << attacker->GetName() << "��(��) " << victim->GetName() << "���� �����̸� �ֵѷ����ϴ�." << endl;
}

void SoundManager::TakeDamageSound(int aD, int aP, shared_ptr<Creature> victim)
{
    cout << victim->GetName() << "��(��) " << (aD+aP) << "�� �������� �Ծ����ϴ�. (���� ü�� : " << victim->GetHp() << ")" << endl;
}

void SoundManager::DeadSound(shared_ptr<Creature> victim)
{
    cout << victim->GetName() << "��(��) �׾����ϴ�." << endl;
}