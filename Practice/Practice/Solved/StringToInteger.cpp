#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int solution(string n_str) {
    int answer = 0;

    answer = stoi(n_str);

    for (int i = 0; i < n_str.size(); i++)
    {
        answer *= 10;
        answer += n_str[i] - '0';
    }

    return answer;
}

int main()
{
    solution("10");

    return 0;
}