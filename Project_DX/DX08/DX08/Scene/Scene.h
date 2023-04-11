#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() {}
	virtual void Fin() {}
	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PreRender() {}
	virtual void PostRender() {}
protected:
	virtual void SceneClear() {}
	bool _isClear = false;
};

