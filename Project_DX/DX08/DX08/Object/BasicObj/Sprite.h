#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring file, Vector2 size);
	Sprite(wstring file, float maxFrame, Vector2 size);
	Sprite(wstring file, Vector2 maxFrame, Vector2 size);
	virtual ~Sprite();

	virtual void Update();
	virtual void Render();

	virtual void CreateMesh() override;
	virtual void CreateMaterial(wstring file) override;

	void SetReverse();
	void SetDirection(Direction direction);
	int GetDirection() { return _reverseBuffer->_data.reverse; }

	void SetCurFrame(Vector2 curFrame);
	void SetActionClip(Action::Clip clip);

	Vector2 GetClipSize() { return _imageSize; }

private:
	shared_ptr<ActionBuffer> _actionBuffer;
	shared_ptr<ReverseBuffer> _reverseBuffer;
	Vector2 _maxFrame;
	Vector2 _imageSize;
};

