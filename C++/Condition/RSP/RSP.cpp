#include <iostream>

using namespace std;

// 과제

// 가위바위보 게임만들기
// - 1 (가위), 2 (바위), 3 (보) 중에 하나를 입력받는다.
// - 컴퓨터는 1, 2, 3 중에 하나 수 (가위바위보 중 하나)를 갖는다.
// - 둘이 가위바위보 게임을 10번 반복

int main()
{
	int player, computer, count = 0, pwcount = 0, cwcount = 0;
	/*while (true)
	{
		computer = rand() % 3;
		cout << computer << endl;
	}*/
	while(true)
	{
		if (count >= 10)
			break;
		// 입력
		cin >> player;
		cout << "플레이어 : " << player << endl;

		// 난수 생성
		srand((unsigned int)time(nullptr)); // 난수 씨드
		computer = rand() % 3;
		cout << "컴퓨터 : " << computer << endl;

		if (player == computer)
		{
			cout << "무승부 입니다." << endl;
		}
		else if (player > computer)
		{
			if ((player - computer) == 1)
			{
				cout << "플레이어 승" << endl;
				pwcount++;
			}
			else
			{
				cout << "컴퓨터 승" << endl;
			}
		}
		cout << "플레이어 : " << pwcount << "승" << endl;
		cout << "컴퓨터 : " << cwcount << "승" << endl;
		count++;
	}

	return 0;
}