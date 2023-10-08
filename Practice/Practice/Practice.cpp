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

string solution(vector<string> participant, vector<string> completion)
{
    map<string, int> answer;

    for (string name : participant)
        answer[name]++;

    for (string name : completion)
        answer[name]--;

    for (const pair<string, int> pair : answer)
    {
        if (pair.second == 1)
            return pair.first;
    }

    return "";
}

int main()
{
    vector<string> Participant = {"leo","kiki","eden"};
    vector<string> Completion = {"eden","kiki"};
    solution(Participant, Completion);

    return 0;
}