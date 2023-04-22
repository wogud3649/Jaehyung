#pragma once
class SpriteSlider
{
	public:
		SpriteSlider();
		SpriteSlider(wstring file, Vector2 maxFrame);
		~SpriteSlider();

		void Update();
		void PostRender();

		void CreateMesh();
		void CreateMaterial(wstring file);

		void SetPos(Vector2 pos);

		void SetRatio(float value) { _sliderBuffer->_data.ratio = value; }
		void SetOpaque(float value) { _sliderBuffer->_data.opaque = value; }

		void SetCurFrame(Vector2 curFrame);

		const shared_ptr<Transform>& GetTransform() { return _transform; }

	private:
		vector<UINT> _indices;
		vector<Vertex> _vertices;

		shared_ptr<VertexBuffer> _vertexBuffer;
		shared_ptr<IndexBuffer> _indexBuffer;

		shared_ptr<VertexShader> _vs;
		shared_ptr<PixelShader> _ps;
		shared_ptr<SRV> _srv;

		shared_ptr<Transform> _transform;

		shared_ptr<ActionBuffer> _actionBuffer;
		shared_ptr<SliderBuffer> _sliderBuffer;

		Vector2 _maxFrame = Vector2 (1, 1);
		Vector2 _imageSize;
		Vector2 _size;
};