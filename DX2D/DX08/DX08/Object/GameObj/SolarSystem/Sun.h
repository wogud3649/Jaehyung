#pragma once
class Sun : public Planet
{
public:
	Sun();
	virtual ~Sun();

	virtual void Update() override;
	virtual void Render() override;

	virtual shared_ptr<Transform> GetTransform() override;

private:
	shared_ptr<Quad> _sun;
};

