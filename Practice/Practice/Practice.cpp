#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

vector<int> solution(string s) {
    vector<int> answer;
    unordered_map<char, int> uMap;

    for (int i = 0; i < s.size(); i++)
    {
        int beforeIndex = uMap[s[i]]-1;
        if (beforeIndex != -1)
        {
            answer.push_back(i-beforeIndex);
        }
        else
        {
            answer.push_back(-1);
        }
        uMap[s[i]] = i+1;
    }

    return answer;
}

int main(void)
{
    solution("bananaaaaaaaaaab");

    return 0;
}