#pragma once
class Vector2
{
	public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	void PrintVector2();

	// a + b : a와 b를 더하고 그 값을 반환
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const float& value) const;

	// a < b : a가 b보다 작으면 true, 그게 아니면 false 반환
	bool operator<(const Vector2& other) const;
	bool operator>(const Vector2& other) const;
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	// 대입연산자
	// a = b : a 에다가 b를 대입하고 a의 원본 반환
	Vector2& operator=(const Vector2& other);
	Vector2& operator+=(const Vector2& other);

	// 전위연산자
	// ++a : a에다가 1을 더하고 원본을 반환
	Vector2& operator++();
	
	// 후위연산자
	// a++ : a를 반환하고 a에다가1을 더한다.
	Vector2& operator++(int);

	float Length() const;

	// 외적
	//float Cross(const Vector2& other) const; // 오른손 법칙으로 +/-

	// 정규화 벡터 뽑기
	//Vector2 Normal();

public:
	float x;
	float y;
};

