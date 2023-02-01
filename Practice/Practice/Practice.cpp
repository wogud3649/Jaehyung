#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

void CreateGraph()
{
    
}

string solution(vector<int> numbers, string hand) {
    string answer = "";
    vector<vector<int>> distance(10, vector<int>(10, 10));
    distance[2][5] = distance[5][8] = distance[8][0];
    for (int i = 2; i < 9; i += 3)
    {
        distance[i - 1][i] = distance[i][i+1] = 1;
    }
    
    // 1 2 3 4 5 6 7 8 9
    // 1 2 0 1 2 0 1 2 0
    for (int number : numbers)
    {
        if (number == 0)
        {
            //TODO
            break;
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