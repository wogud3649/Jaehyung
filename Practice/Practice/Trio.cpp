#include <iostream>
#include <vector>

using namespace std;

int trio = 0;

void dfs(const vector<int>& number, vector<bool>& visited, int index, int count, int sum)
{
    visited[index] = true;
    if (count == 3)
    {
        if (sum == 0)
            trio++;
        return;
    }

    for (int i = 0; i < number.size(); i++)
    {
        if (i <= index)
            continue;
        if (visited[i])
            continue;
        dfs(number, visited, i, count + 1, sum + number[i]);
        visited[i] = false;
    }
    return;
}

int solution(vector<int> number) {
    vector<bool> visited(number.size(), false);
    for (int i = 0; i < number.size(); i++)
    {
        int count = 1;
        dfs(number, visited, i, count, number[i]);
    }

    return trio;
}

int main(void)
{
    solution({ -2, 3, 0, 2, -5 });

    return 0;
}