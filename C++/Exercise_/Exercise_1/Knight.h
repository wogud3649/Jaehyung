#pragma once

class Knight
{
public:
	Knight();
	Knight(int hp, int attack);
	~Knight();

	void PrintInfo();

public:
	int _hp;
	int _attack;
};

