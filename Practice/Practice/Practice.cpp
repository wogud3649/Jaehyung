#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int solution(vector<int> numbers) {
    int answer = 0;
    unordered_map<int, int> uMap;

    for (int num : numbers)
    {
        uMap[num]++;
    }
    
    for (int i = 1; i < 10; i++)
    {
        if (uMap[i] == 0)
            answer += i;
    }

    return answer;
}

int main()
{
    solution({ 1, 2, 3, 4, 6, 7, 8, 0 });

    return 0;
}