#pragma once
class Camera
{
private:
	Camera();
	~Camera();

public:
	static void Create()
	{
		if (_instance == nullptr)
		{
			_instance = new Camera();
		}
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Camera* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();
	void PostRender();

	void ShakeStart(float magnitude, float duration, float reduceDamping = 1.0f);

	void SetViewPort(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void SetProjectBuffer(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void SetCameraWorldBuffer() { _transform->SetBuffer(1); }
	void UICameraBuffer() { _uiCameraBuffer->SetVSBuffer(1); }

	void SetTarget(shared_ptr<Transform> target) { _target = target; }
	void SetLeftBottom(Vector2 value) { _leftBottom = value; }
	void SetRightTop(Vector2 value) { _rightTop = value; }
	void SetOffset(Vector2 value) { _offset = value; }

	Vector2 GetWorldMousePos();

private:
	void Shake();
	void FreeMode();
	void FollowMode();

	shared_ptr<Transform> _transform;
	Vector2 _moveVector;

	shared_ptr<MatrixBuffer> _projection;
	shared_ptr<MatrixBuffer> _uiCameraBuffer;

	float _speed = 2048.0f;

	shared_ptr<Transform> _target = nullptr;
	Vector2 _offset;

	Vector2 _leftBottom;
	Vector2 _rightTop;

	float _duration = 0.0f;
	float _magnitude = 0.0f;
	float _reduceDamping = 0.0f;

	Vector2 _originPos = { 0.0f,0.0f };

	Vector2 win_size;

	static Camera* _instance;
};

