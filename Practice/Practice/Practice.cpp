#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

void dfs(vector<vector<int>>& distance, vector<bool>& visited, int startIndex, int here, int depth)
{
    visited[here] = true;
    distance[startIndex][here] = depth;

    for (int there = 0; there < 10; there++)
    {
        if (here == there)
            continue;
        if (visited[there])
            continue;
        if (distance[here][there] == -1)
            continue;
        if (distance[startIndex][there] != -1 && distance[startIndex][there] < depth + distance[here][there])
            continue;
        dfs(distance, visited, startIndex, there, depth + distance[here][there]);
    }
}

void CreateGraph(vector<vector<int>>& distance)
{
    for (int i = 1; i < 8; i += 3)
    {
        distance[i][i + 1] = distance[i+2][i+1] = 1;
    }
    distance[10][0] = distance[11][0] = 1;
    distance[2][5] = distance[5][2] = 1;
    distance[5][8] = distance[8][5] = 1;
    distance[8][0] = distance[0][8] = 1;
}

string solution(vector<int> numbers, string hand) {
    string answer = "";
    int leftIndex = 10;
    int rightIndex = 11;
    vector<vector<int>> distance(12, vector<int>(12, -1));
    vector<bool> visited(12, false);
    CreateGraph(distance);
    for (int i = 0; i < 12; i++)
    {
        dfs(distance, visited, i, i, 0);
        for (int i = 0; i < visited.size(); i++)
            visited[i] = false;
    }
    
    // 1 2 3 4 5 6 7 8 9
    // 1 2 0 1 2 0 1 2 0
    for (int number : numbers)
    {
        if (number == 0)
        {
            //TODO
            continue;
        }

        switch (number % 3)
        {
        case 0:
            answer.push_back('R');
            break;
        case 1:
            answer.push_back('L');
            break;
        case 2:

            break;
        default:
            break;
        }
    }

    return answer;
}

int main(void)
{
    solution({ 1, 3, 4, 5, 8, 2, 1, 4, 5, 9, 5 }, "right");

    return 0;
}