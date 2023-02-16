#pragma once
class World
{
public:
	World();
	~World();

	void SetTypeAndName();
	void Init();

private:
	int _type;
	string _name;
	Creature* _player;
	Creature* _goblins[10];
};