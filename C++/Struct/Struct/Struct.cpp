#include <iostream>

using namespace std;

// 구조체
// 자료들의 묶음
// 코딩 컨벤션 : 코딩 약속
// 멤버변수 앞에 _, m_, m

// 구조체의 크기 : 안에 있는 멤버변수에 의해 결정된다.
// 비슷한 위치에 읽는 순서대로 같이 저장이 된다.

struct Player
{
    float _hp; // Player 의 멤버변수
    int _level;
    string _name;
};

int main()
{
    // Stack
    Player p;
    p._hp = 0.0f;
    p._level = 1;
    p._name = "hanil";

    // . : 멤버 연산자

    cout << p._hp << endl;
    cout << p._level << endl;
    cout << p._name << endl;

    return 0;
}