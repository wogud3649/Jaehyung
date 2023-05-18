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

int solution(int a, int b) {
    int answer = 0;

    string aString = to_string(a);
    string bString = to_string(b);

    string tempS1 = aString + bString;
    string tempS2 = bString + aString;

    int temp1 = stoi(tempS1);
    int temp2 = stoi(tempS2);

    if (temp1 > temp2)
        return temp1;
    else
        return temp2;
}

int main() {
    solution(112, 113);

    return 0;
}