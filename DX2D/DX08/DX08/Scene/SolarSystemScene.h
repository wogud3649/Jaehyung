#pragma once
class SolarSystemScene :public Scene
{
public:
	SolarSystemScene();
	virtual ~SolarSystemScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

private:
	// 과제
	// Planet 클래스 만들기
	// - 멤버변수 Quad
	
	// 1. 태양 자전
	// 2. 지구 공전, 자전
	// 3. 달 공전, 자전

	// extra
	// 1. 태양 자전할 때 지구는 2번 공전
	// 2. 지구 자전할 때 달은 2번 공전
};

