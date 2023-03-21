#pragma once
class MonsterScene : public Scene
{
public:
	enum State
	{
		IDLE,
		WALK,
		ATTACK
	};
	MonsterScene();
	~MonsterScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<MushroomEnt> _mushroomEnt;
};

