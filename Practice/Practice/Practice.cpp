#include <iostream>
#include <vector>

using namespace std;

struct Line
{
    Line(int x1, int x2) : x1(x1), x2(x2) {}
    int x1;
    int x2;
};

int solution(vector<vector<int>> lines) {
    vector<Line> v;
    for (int i = 0; i < lines.size(); i++)
        v.push_back(Line(lines[i][0],lines[i][1]));
    int answer = 0;

    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = i + 1; j < v.size(); j++)
        {
            int temp;
            if (v[i].x1 < v[j].x1)
            {
                if (v[i].x2 > v[j].x2)
                {
                     temp = v[i].x2 - v[j].x1;
                }
            }
        }
    }
}

int main()
{

    return 0;
}