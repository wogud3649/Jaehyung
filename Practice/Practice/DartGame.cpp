#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solution(string dartResult) {
    int answer = 0;
    vector<int> points;
    int size = dartResult.size();

    for (int i = 0, index = 0, count; i < size; i += count, index++)
    {
        count = 2;
        int num = dartResult[i] - '0';
        if (num == 1 && dartResult[i + 1] == '0')
        {
            num = 10;
            i++;
        }

        switch (dartResult[i + 1])
        {
        case 'S':
        {
            points.push_back(num);
            break;
        }
        case 'D':
        {
            points.push_back(pow(num, 2));
            break;
        }
        case 'T':
        {
            points.push_back(pow(num, 3));
            break;
        }
        }
        if (i + 2 < size)
        {
            switch (dartResult[i + 2])
            {
            case '*':
            {
                if (index == 0)
                {
                    points[index] *= 2;
                    count++;
                    break;
                }
                else
                {
                    points[index - 1] *= 2;
                    points[index] *= 2;
                    count++;
                    break;
                }
            }
            case '#':
            {
                points[index] *= -1;
                count++;
                break;
            }
            default:
                break;
            }
        }
    }

    for (int num : points)
    {
        answer += num;
    }

    return answer;
}

int main(void)
{
    solution("1D2S#10S");

    return 0;
}