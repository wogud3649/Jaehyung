#include <iostream>

using namespace std;

enum Num
{
	ZERO,
	ONE,
	TWO,
	THREE
};

// 분기문
// if - else if - else
// if (조건문)
// {
// 조건문이 true 일때 실행
// }
// else if (조건문)
// {
// }
// else
// {
// 모든 조건이 false 일 때 실행
// }

// switch 문
// switch(data) data는 정수형
// {
//  case : 1
//  {
//		data가 1일 때 실행
//		break;
//  }
// }

// 반복문
// while (조건식)
// {
//		명령문
//		제어식
//		탈출문 break;
// }

// do - while

// for (초기식; 조건식; 제어식)
// {
//		명령문
//		탈출문 break;
//		continue;
// }

int main()
{
	int aInt = 3;
	if (aInt < 3)
	{
		cout << "aInt가 3보다 작습니다." << endl;
	}
	else if (aInt > 3)
	{
		cout << "aInt가 3보다 큽니다." << endl;
	}
	else
	{
		cout << "aInt는 3입니다." << endl;
	}
	switch (aInt)
	{
		case 1:
		{
			cout << "aInt는 1입니다." << endl;
			break;
		}
		case 3:
		{
			cout << "aInt는 3입니다." << endl;
			break;
		}
		default:
		{
			cout << "aInt는 알 수 없습니다." << endl;
			break;
		}
	}
	Num data = Num::THREE;

	switch (data)
	{
	case ZERO:
		break;
	case ONE:
		break;
	case TWO:
		break;
	case THREE:
		break;
	default:
		break;
	}

	int count = 0;
	while (count < 10)
	{
		/*if (count >= 10)
		{
			break;
		}*/
		cout << count << endl;
		count++; // 제어식
	}

	// do - while
	count = 0;
	do
	{
		cout << "do while" << endl;
		cout << count << endl;
		count++;

		if (count >= 10)
			break;
	} while (true);

	cout << "for 문" << endl;
	for(int i = 0; i < 10; i++)
	{
		if (i == 3)
			continue;

		if (i == 5)
			break;
		cout << i << endl;
	}

	return 0;
}