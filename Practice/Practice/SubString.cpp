#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int solution(string t, string p) {
    vector<string> enables;
    int size = p.size();
    int answer = 0;

    for (int i = 0; i < t.size() - size + 1; i++)
    {
        enables.push_back(t.substr(i, size));
    }
    sort(enables.begin(), enables.end());

    for (int i = 0; i < enables.size(); i++)
    {
        if (p < enables[i])
            break;
        answer++;
    }

    return answer;
}

int main(void)
{
    solution("10203", "15");

    return 0;
}