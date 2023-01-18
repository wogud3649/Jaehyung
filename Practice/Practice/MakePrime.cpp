#include <iostream>
#include <vector>

using namespace std;

bool PrimeCheck(int num)
{
    bool check = true;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            check = false;
            break;
        }
    }
    return check;
}

void MakePrime(const vector<int>& nums, int count, int index, int sum, int& answer)
{
    if (count == 3)
    {
        if (PrimeCheck(sum))
            answer++;
        return;
    }

    for (int i = index + 1; i < nums.size(); i++)
    {
        MakePrime(nums, count + 1, i, sum + nums[i], answer);
    }
}

int solution(vector<int> nums) {
    int answer = 0;
    int numSize = nums.size();
    for (int i = 0; i < numSize - 2; i++)
    {
        MakePrime(nums, 1, i, nums[i], answer);
    }
    return answer;
}

int main(void)
{
    solution({ 1,2,7,6,4 });

    return 0;
}