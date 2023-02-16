#include "Framework.h"

// ����
// Vector2 a, b;
// a == b; Clear
// a != b; Clear
// a += b;
// a -= b;
// a.Dot(b); -> ����
// a.Cross(b); -> ����
// ����ȭ ���� �̱� (���̰� 1�� ����)
// a.Length(b); -> a, b ������ �Ÿ�

// 9���� ���� ����
// �÷��̾ �Է��ϴ� �� ����
// �����̱� ����
// Knight Archer Mage �߿� 2�� ������ �ο�
// Attack�� �޽��� ��� or ������ �ٸ���

// ���� Dot
// |a| |b| cos(theta)
// x1x2 + y1y2
// cos(theta) = (a + b)/ |a| |b|

// ���� Cross (��������)
// |a||b| sin(theta)
// (0,0,x1y2-x2y1)



int main()
{
	Vector2 v1(1,1);
	Vector2 v2(1.0f, 1.0f);
	Vector2 v3 = v1;

	v3 = v1 + v2;

	v3 = v3 * 5;

	cout << (v1 == v2) << endl;
	cout << (v1 != v3) << endl;

	return 0;
}