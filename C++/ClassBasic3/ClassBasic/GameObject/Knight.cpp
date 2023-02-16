#include "Framework.h"

Knight::Knight()
: Player()
{
}

Knight::Knight(string name, int hp, int attack)
: Player(name, hp, attack)
{
}

Knight::~Knight()
{
}

void Knight::AttackMage(Mage* mage)
{
	cout << mage->GetName() << "을" << this->_name << "이 공격했습니다." << endl;
}
