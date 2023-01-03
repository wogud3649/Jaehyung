#include "Framework.h"

GoblinKing::GoblinKing()
: Boss()
, attackNum(3)
{
}

GoblinKing::GoblinKing(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance)
: Boss(name, hp, attackDamage, abilityPower, defense, magicResistance)
, attackNum(3)
{
}

GoblinKing::~GoblinKing()
{
}

void GoblinKing::Attack(shared_ptr<Creature> other)
{
	if (this->_isLive)
	{
		_damageTable.erase(remove_if(_damageTable.begin(), _damageTable.end(), [](const pair<shared_ptr<Creature>, int>& a)->bool
			{
				return !(a.first->IsLive());
			}), _damageTable.end());
		if (_damageTable.size() > attackNum)
		{
			std::partial_sort(_damageTable.begin(), _damageTable.begin() + attackNum, _damageTable.end(), [](const pair<shared_ptr<Creature>, int>& a, const pair<shared_ptr<Creature>, int>& b)->bool
				{
					return (a.second > b.second);
				});
			for (int i = 0; i < attackNum; i++)
				SoundManager::GetInstance()->GoblinKingAttackSound(shared_from_this(), _damageTable[i].first);
		}
		else if (_damageTable.size() == attackNum)
		{
			for (auto& player : _damageTable)
				SoundManager::GetInstance()->GoblinKingAttackSound(shared_from_this(), player.first);
		}
		else
		{
			attackNum--;
			GoblinKing::Attack(other);
		}
	}
}

void GoblinKing::TakeDamage(shared_ptr<Creature> other)
{
	if (this->_isLive)
	{
		if (other->IsLive())
		{
			int tempAd = other->GetAttackDamage() - this->_defense;
			int tempAp = other->GetAbilityPower() - this->_magicResistance;
			if (tempAd < 0)
				tempAd = 0;
			if (tempAp < 0)
				tempAp = 0;
			_damageTaken = (tempAd + tempAp);
			this->_hp -= _damageTaken;
			if (this->_hp <= 0)
			{
				_hp = 0;
				_isLive = false;
			}
			SoundManager::GetInstance()->TakeDamageSound(tempAd, tempAp, shared_from_this());

			vector<pair<shared_ptr<Creature>, int>>::iterator iter =
				find_if(_damageTable.begin(), _damageTable.end(), [other](const pair<shared_ptr<Creature>, int>& a)->bool
				{
					return (a.first == other);
				});
			if (iter == _damageTable.end())
			{
				this->_damageTable.push_back(make_pair(other, _damageTaken));
			}
			else
			{
				iter->second += _damageTaken;
			}

			if (this->_hp == 0)
			{
				SoundManager::GetInstance()->DeadSound(shared_from_this());
			}
		}
	}
}

int GoblinKing::GetAttackNum()
{
	return attackNum;
}

vector<pair<shared_ptr<Creature>, int>>& GoblinKing::GetDamageTable()
{
	return _damageTable;
}
