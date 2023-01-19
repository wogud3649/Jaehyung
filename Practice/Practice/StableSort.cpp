#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    unordered_map<int, int> clear;
    unordered_map<int, int> reach;
    vector<pair<int, float>> percent;
    for (int i = 1; i < N + 1; i++)
    {
        percent.push_back(make_pair(i, 0));
        for (int j = 0; j < stages.size(); j++)
        {
            if (stages[j] == i)
            {
                reach[i]++;
            }
            if (stages[j] > i)
            {
                clear[i]++;
            }
        }
        if (clear[i] == 0 && reach[i] == 0)
        {
            percent[i - 1].second = 0;
            continue;
        }
        percent[i - 1].second = float(reach[i]) / float(reach[i] + clear[i]);
    }
    stable_sort(percent.begin(), percent.end(), [](const pair<int, float>& a, const pair<int, float>& b)->bool
        {
            return a.second > b.second;
        });

    for (int i = 0; i < percent.size(); i++)
    {
        answer.push_back(percent[i].first);
    }

    return answer;
}

int main(void)
{
    solution(5, { 2,1,2,4,3,3 });

    return 0;
}