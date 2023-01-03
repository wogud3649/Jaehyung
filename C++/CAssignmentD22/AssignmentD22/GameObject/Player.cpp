#include "Framework.h"

Player::Player()
: Creature()
, _type(PLAYER)
{
}

Player::Player(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance)
: Creature(name, hp, attackDamage, abilityPower, defense, magicResistance)
, _type(PLAYER)
{
}

Player::~Player()
{
}