#pragma once
class Moon : public Planet
{
public:
	Moon();
	virtual ~Moon();

	virtual void Update() override;
	virtual void Render() override;

	virtual shared_ptr<Transform> GetTransform() override;

private:
	shared_ptr<Quad> _moon;
};

