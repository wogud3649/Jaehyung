#pragma once
class World
{
public:
	World();
	~World();
	
	void SetPlayers();
	void SetBoss();
	void Init();

	void RaidBoss();

private:
	int _bossAttackNum;
	vector<shared_ptr<Creature>> _players;
	shared_ptr<Creature> _goblinKing;
};