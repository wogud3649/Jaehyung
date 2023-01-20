#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

int solution(int k, int m, vector<int> score) {
    int answer = 0;
    sort(score.begin(), score.end(), greater<int>());

    for (int i = m - 1; i < score.size(); i += m)
    {
        answer += score[i] * m;
    }

    return answer;
}

int main(void)
{
    solution(3, 4, { 1, 2, 3, 1, 2, 3, 1 });

    return 0;
}