#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Quad> _quad;

	shared_ptr<MatrixBuffer> _view;
	shared_ptr<MatrixBuffer> _projection;
};