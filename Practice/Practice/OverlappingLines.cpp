#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<int>> lines) {
    unordered_map<int, int> uMap;
    int left = 100;
    int right = -100;

    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = lines[i][0]; j < lines[i][1]; j++)
        {
            uMap[j]++;
            if (j < left)
                left = j;
            if (j > right)
                right = j;
        }
    }

    int answer = 0;
    for (int i = left; i < right + 1; i++)
    {
        if (uMap[i] > 1)
            answer++;
    }
    return answer;
}

int main()
{
    vector<vector<int>> lines = { {0, 1}, {2, 5}, {3, 9} };
    int answer = solution(lines);
    return 0;
}