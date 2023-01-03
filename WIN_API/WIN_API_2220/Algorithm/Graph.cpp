#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> adjacent2; // ���� ����Ʈ
// 0 : 1, 2, 4
// 1 : 0, 6
// 2 : 0, 3, 5
// 3 : 2
// 4 : 0
// 5 : 2
// 6 : 1
vector<vector<bool>> adjacent; // ���� ���

void CreateGraph()
{
	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));

	//     0   1   2   3   4   5   6
	// 0   X   O   O   X   O   X   X
	// 1   O   X   X   X   X   X   O
	// 2   O   X   X   O   X   O   X
	// 3   X   X   O   X   X   X   X
	// 4   O   X   X   X   X   X   X
	// 5   X   X   O   X   X   X   X
	// 6   X   O   X   X   X   X   X
	
	adjacent[0][1] = true;
	adjacent[0][2] = true;
	adjacent[0][4] = true;

	adjacent[1][0] = true;
	adjacent[1][6] = true;

	adjacent[2][0] = true;
	adjacent[2][3] = true;
	adjacent[2][5] = true;

	adjacent[3][2] = true;

	adjacent[4][0] = true;

	adjacent[5][2] = true;

	adjacent[6][1] = true;
}
void CreateGraph2()
{
	adjacent2.resize(7);
	adjacent2[0].push_back(1);
	adjacent2[0].push_back(2);
	adjacent2[0].push_back(4);

	adjacent2[1].push_back(0);
	adjacent2[1].push_back(6);

	adjacent2[2].push_back(0);
	adjacent2[2].push_back(3);
	adjacent2[2].push_back(5);

	adjacent2[3].push_back(2);

	adjacent2[4].push_back(0);

	adjacent2[5].push_back(2);

	adjacent2[6].push_back(1);
}

int main()
{
	// ���� ����Ʈ
	//CreateGraph2();
	// 0�̶� 1�̶� ������ �ֽ��ϱ�?
	//for (auto value : adjacent[0])
	//{
	//	if (value == 1)
	//	{
	//		cout << "����Ǿ� �ֽ��ϴ�." << endl;
	//		break;
	//	}
	//}
	//auto iter = std::find(adjacent2[0].begin(), adjacent2[0].end(), 1);
	//if (iter != adjacent2[0].end())
	//	cout << "ã�ҽ��ϴ�." << endl;

	// ���� ���
	// �޸𸮸� �ְ� �ӵ��� ���Ѵ�.
	CreateGraph();
	// 2�� 5�� �������ֽ��ϱ�?
	if (adjacent[2][5])
		cout << "�������ֽ��ϴ�." << endl;

	return 0;
}