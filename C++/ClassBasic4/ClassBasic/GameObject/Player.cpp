#include "Framework.h"

Player::Player()
: _name("")
, _hp(0)
, _attack(0)
{

}

Player::Player(string name, int hp, int attack)
: _name(name)
, _hp(hp)
, _attack(attack)
{
}

// :: 범위지정연산자 ... 소속연산자
void Player::Attack()
{
}
