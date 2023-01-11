#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

int trio = 0;

void dfs(const vector<int>& number, vector<bool>& visited, int index, int count, int sum)
{
    // 기저
    visited[index] = true;
    if (count == 3)
    {
        if (sum == 0)
            trio++;
        return;
    }

    // 캐시
    
    // 구하기
    for (int i = 0; i < number.size(); i++)
    {
        if (i == index)
            continue;
        if (visited[i])
            continue;
        dfs(number, visited, i, ++count, sum + number[i]);
        visited[i] = false;
    }
    return;
}

int solution(vector<int> number) {
    vector<bool> visited(number.size(), false);
    int answer = 0;
    for (int i = 0; i < number.size(); i++)
    {
        int count = 1;
        dfs(number, visited, i, count, number[i]);
    }

    return answer;
}

int main(void)
{
    solution({ -2, 3, 0, 2, -5 });

    return 0;
}