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

vector<int> a = { 5,6,7,0,1,8,9,2,3 };

int LIS(int num) {
    int n = a.size();
    vector<int> d(n, 1);

    for (int i = num + 1; i < n; i++)
    {
        for (int j = num; j < i; j++)
        {
            if (a[j] < a[i])
            {
                d[i] = max(d[i], d[j] + 1);
            }
        }
    }

    int max_length = *max_element(d.begin(), d.end());

    return max_length;
}

int main() {
    int max_length = LIS(4);
    cout << max_length << endl;

    return 0;
}