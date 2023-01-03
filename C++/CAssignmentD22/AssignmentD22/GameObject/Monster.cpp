#include "Framework.h"

Monster::Monster()
: Creature()
{
}

Monster::Monster(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance)
: Creature(name, hp, attackDamage, abilityPower, defense, magicResistance)
{
}

Monster::~Monster()
{
}