#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring file, Vector2 maxFrame);
	virtual ~Sprite();

	virtual void Update();
	virtual void Render();

	virtual void CreateMesh() override;
	virtual void CreateMaterial(wstring file) override;

	void SetReverse();

	void SetCurFrame(Vector2 curFrame) { _spriteBuffer->_data.curFrame = curFrame; }
	void SetActionClip(Action::Clip clip);

private:
	shared_ptr<SpriteBuffer> _spriteBuffer;
	shared_ptr<ReverseBuffer> _reverseBuffer;
	Vector2 _maxFrame;
};

