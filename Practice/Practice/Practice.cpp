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

bool solution(vector<string> phone_book)
{
    sort(phone_book.begin(), phone_book.end());

    for (int i = 0; i < phone_book.size() - 1; i++)
    {
        for (int j = i + 1; j < phone_book.size(); j++)
        {
            if (phone_book[i][phone_book[i].size() - 1] != phone_book[j][phone_book[i].size() - 1])
                break;
            if (phone_book[j].find(phone_book[i]) == string::npos)
                return false;
        }
    }

    return true;
}

int main()
{
    vector<string> phone_book = { "119", "97674223", "1195524421" };
    solution(phone_book);

    return 0;
}