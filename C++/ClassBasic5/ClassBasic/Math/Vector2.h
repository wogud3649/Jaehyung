#pragma once
class Vector2
{
	public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	void PrintVector2();

	// a + b : a�� b�� ���ϰ� �� ���� ��ȯ
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const float& value) const;

	// a < b : a�� b���� ������ true, �װ� �ƴϸ� false ��ȯ
	bool operator<(const Vector2& other) const;
	bool operator>(const Vector2& other) const;
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	// ���Կ�����
	// a = b : a ���ٰ� b�� �����ϰ� a�� ���� ��ȯ
	Vector2& operator=(const Vector2& other);
	Vector2& operator+=(const Vector2& other);

	// ����������
	// ++a : a���ٰ� 1�� ���ϰ� ������ ��ȯ
	Vector2& operator++();
	
	// ����������
	// a++ : a�� ��ȯ�ϰ� a���ٰ�1�� ���Ѵ�.
	Vector2& operator++(int);

	float Length() const;

	// ����
	//float Cross(const Vector2& other) const; // ������ ��Ģ���� +/-

	// ����ȭ ���� �̱�
	//Vector2 Normal();

public:
	float x;
	float y;
};

