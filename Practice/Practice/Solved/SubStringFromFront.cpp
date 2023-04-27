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

string solution(string my_string, int n) {
    string answer = "";

    answer = my_string.substr(0, n);

    for (int i = 0; i < n; i++)
        answer.push_back(my_string[i]);

    return answer;
}

int main()
{
    solution("ProgrammerS123", 11);

    return 0;
}