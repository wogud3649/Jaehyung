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

vector<int> a = { 5,6,7,0,1,8,9,8,2,3 };
vector<int> cache(10, 1);
//                        5,4,4,4,3,2,2,2,2,1

void LIS(int num)
{
    if (num > a.size() - 2)
        return;

    LIS(num + 1);

    for (int i = a.size() - 1; i > num; i--)
    {
        if (a[num] < a[i])
            cache[num] = max(cache[num], cache[i] + 1);
    }

    return;
}

int main() {
    LIS(0);

    for (int i = cache.size() - 1; i > 0; i--)
    {
        if (cache[i - 1] < cache[i])
            cache[i - 1] = cache[i];
    }

    cout << *max_element(cache.begin(), cache.end()) << endl;

    return 0;
}