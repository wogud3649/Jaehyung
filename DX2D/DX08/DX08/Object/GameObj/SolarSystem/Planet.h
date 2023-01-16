#pragma once
class Planet
{
public:
	Planet();
	virtual ~Planet();

	virtual void Update() abstract;
	virtual void Render() abstract;

	virtual shared_ptr<Transform> GetTransform() abstract;

private:
};

