#include <iostream>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    bool check;
    for (int i = 2; i <= n; i++)
    {
        check = true;
        for (int j = 2; j * j < i; j++)
        {
            if (i % j == 0)
            {
                check = false;
                break;
            }
        }
        if (check)
            answer++;
    }
    return answer;
}

int main(void)
{
    solution(10);

    return 0;
}