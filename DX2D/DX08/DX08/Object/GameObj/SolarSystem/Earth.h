#pragma once
class Earth : public Planet
{
public:
	Earth();
	virtual ~Earth();

	virtual void Update() override;
	virtual void Render() override;

	virtual shared_ptr<Transform> GetTransform() override;

private:
	shared_ptr<Quad> _earth;
};

