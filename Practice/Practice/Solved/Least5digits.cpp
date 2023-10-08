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

vector<int> solution(vector<int> num_list)
{
    vector<int> answer;
    list<int> temp;

    for (int i = 0; i < num_list.size(); i++)
    {
        bool isInserted = false;
        int count = 0;
        for (list<int>::iterator iter = temp.begin(); iter != temp.end(); iter++)
        {
            if (count > 4)
                break;

            count++;

            if (num_list[i] < *iter)
            {
                temp.emplace(iter, num_list[i]);
                isInserted = true;
                break;
            }
        }

        if (isInserted == false && count < 5)
            temp.push_back(num_list[i]);
    }

    for (list<int>::iterator iter = temp.begin(); iter != temp.end(); iter++)
    {
        answer.push_back(*iter);

        if (answer.size() > 4)
            break;
    }

    return answer;
}

int main()
{
    solution({ 12, 4, 15, 46, 38, 1, 14 });

    return 0;
}