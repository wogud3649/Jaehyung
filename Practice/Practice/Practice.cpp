#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

int solution(int n) {
    int answer = 0;
    vector<int> v;

    for (int count = 0; n != 0; n /= 3, count++)
    {
        v.push_back(n % 3);
    }

    for (int i = v.size() - 1, j = 0; i >= 0; i--, j++)
    {
        answer += v[i] * pow(3, j);
    }
    return answer;
}

int main(void)
{
    solution(45);
    return 0;
}