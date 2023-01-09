#include <iostream>
#include <vector>

using namespace std;

int Cross(vector<int> a, vector<int> b)
{
    return a[0] * b[1] - a[1] * b[0];
}

int solution(vector<vector<int>> dots) {
    vector<vector<int>> lines1(dots.size() - 1);
    vector<vector<int>> lines2(dots.size() - 1);

    for (int i = 1, j = 0; i < dots.size(); i++, j++)
    {
        lines1[j].push_back(dots[0][0] - dots[i][0]);
        lines1[j].push_back(dots[0][1] - dots[i][1]);
    }
    for (int i = 1, k = 0; i < dots.size() - 1; i++)
    {
        for (int j = i + 1; j < dots.size(); j++, k++)
        {
            lines2[k].push_back(dots[i][0] - dots[j][0]);
            lines2[k].push_back(dots[i][1] - dots[j][1]);
        }
    }

    for (int i = 0; i < lines1.size(); i++)
    {
        if (Cross(lines1[i], lines2[2 - i]) == 0)
            return 1;
    }
    return 0;
}

int main()
{
    vector<vector<int>> dots = { {3, 5}, {4, 1}, {2, 4}, {5, 10} };
    int answer = solution(dots);
    return 0;
}