#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    vector<bool> attend(n, true);

    for (int lostNum : lost)
    {
        attend[lostNum - 1] = false;
    }

    for (int i = 0; i < reserve.size(); i++)
    {
        int curNum = reserve[i] - 1;
        if (attend[curNum] == false)
        {
            attend[curNum] = true;
            continue;
        }
        if (curNum == 0)

    }

    return answer;
}

int main(void)
{
    solution(5, { 2,4 }, { 1, 2, 3, 5 });

    return 0;
}