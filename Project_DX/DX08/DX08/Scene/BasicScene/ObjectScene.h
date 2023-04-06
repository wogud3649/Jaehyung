#pragma once
class ObjectScene : public Scene
{
public:
	ObjectScene();
	~ObjectScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Door> _door;
	shared_ptr<Chest> _chest;
	bool _chestSpawn = false;
	bool _doorSpawn = false;
};

