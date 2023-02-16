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
	cout << mage->GetName() << "��" << this->_name << "�� �����߽��ϴ�." << endl;
}
