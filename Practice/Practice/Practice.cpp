#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

int solution(int n, int m, vector<int> section) {
    int answer = 0;
    int start;

    if (section.size() > 0)
    {
        start = section[0];
        answer++;
    }

    for (int i = 0; i < section.size(); i++)
    {
        if (start + m - 1 < section[i])
        {
            start = section[i];
            answer++;
        }
    }

    return answer;
}

int main(void)
{
    int n = 8;
    int m = 4;
    vector<int> section = { 2, 3, 6 };

    solution(n, m, section);

    return 0;
}