#pragma once
class SolarSystemScene :public Scene
{
public:
	SolarSystemScene();
	virtual ~SolarSystemScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

private:
	// ����
	// Planet Ŭ���� �����
	// - ������� Quad
	
	// 1. �¾� ����
	// 2. ���� ����, ����
	// 3. �� ����, ����

	// extra
	// 1. �¾� ������ �� ������ 2�� ����
	// 2. ���� ������ �� ���� 2�� ����
};

