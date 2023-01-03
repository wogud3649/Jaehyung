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
    cout << attacker->GetName() << "이(가) " << victim->GetName() << "에게 검을 휘둘렀습니다." << endl;
}

void SoundManager::ArcherAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim)
{
    cout << attacker->GetName() << "이(가) " << victim->GetName() << "에게 활을 쐈습니다." << endl;
}

void SoundManager::MageAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim)
{
    cout << attacker->GetName() << "이(가) " << victim->GetName() << "에게 파이어볼을 날렸습니다." << endl;
}

void SoundManager::GoblinAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim)
{
    cout << attacker->GetName() << "이(가) " << victim->GetName() << "에게 달려들었습니다." << endl;
}

void SoundManager::GoblinKingAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim)
{
    cout << attacker->GetName() << "이(가) " << victim->GetName() << "에게 몽둥이를 휘둘렀습니다." << endl;
}

void SoundManager::TakeDamageSound(int aD, int aP, shared_ptr<Creature> victim)
{
    cout << victim->GetName() << "이(가) " << (aD+aP) << "의 데미지를 입었습니다. (남은 체력 : " << victim->GetHp() << ")" << endl;
}

void SoundManager::DeadSound(shared_ptr<Creature> victim)
{
    cout << victim->GetName() << "이(가) 죽었습니다." << endl;
}