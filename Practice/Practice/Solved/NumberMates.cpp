#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string solution(string X, string Y) {
    string answer = "";
    sort(X.begin(), X.end(), greater<char>());
    sort(Y.begin(), Y.end(), greater<char>());

    int xIndex = 0;
    int yIndex = 0;

    while (xIndex < X.size() && yIndex < Y.size())
    {
        if (X[xIndex] > Y[yIndex])
            xIndex++;
        else if (X[xIndex] < Y[yIndex])
            yIndex++;
        else
        {
            answer.push_back(X[xIndex]);
            xIndex++;
            yIndex++;
        }
    }
    if (answer == "")
        answer = "-1";
    else if (answer[0] == '0')
        answer = "0";

    return answer;
}

int main(void)
{
    solution("100", "203045");

    return 0;
}