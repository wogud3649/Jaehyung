#pragma once
class FilterSprite : public Quad
{
public:
	FilterSprite(wstring file, Vector2 size);
	FilterSprite(wstring file, Vector2 maxFrame, Vector2 size);
	virtual ~FilterSprite();

	virtual void Update();
	virtual void Render();

	virtual void CreateMesh() override;
	virtual void CreateMaterial(wstring file) override;

	void SetReverse();
	int& GetLeftRight() { return _reverseBuffer->_data.reverse; }

	void SetCurFrame(Vector2 curFrame);
	void SetActionClip(Action::Clip clip);

	Vector2 GetClipVertexSize() { return _clipSize; }
	shared_ptr<FilterBuffer> GetFilter() { return _filterBuffer; }

private:
	shared_ptr<ActionBuffer> _actionBuffer;
	shared_ptr<ReverseBuffer> _reverseBuffer;
	shared_ptr<FilterBuffer> _filterBuffer;
	Vector2 _maxFrame;
	Vector2 _clipSize;
};

