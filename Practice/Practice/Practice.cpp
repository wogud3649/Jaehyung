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

int solution(int number, int n, int m) {
    return number % n == 0 && number % m == 0;
}

int main()
{
    solution(60, 2, 3);

	return 0;
}