#include "Framework.h"

// 과제
// Vector2 a, b;
// a == b; Clear
// a != b; Clear
// a += b;
// a -= b;
// a.Dot(b); -> 내적
// a.Cross(b); -> 외적
// 정규화 벡터 뽑기 (길이가 1인 벡터)
// a.Length(b); -> a, b 사이의 거리

// 9일차 과제 변형
// 플레이어가 입력하는 것 제거
// 랜덤뽑기 제거
// Knight Archer Mage 중에 2명만 가지고 싸움
// Attack의 메시지 출력 or 동작을 다르게

// 내적 Dot
// |a| |b| cos(theta)
// x1x2 + y1y2
// cos(theta) = (a + b)/ |a| |b|

// 외적 Cross (법선벡터)
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