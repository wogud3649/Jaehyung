#include <iostream>

using namespace std;

// 카멜표기법
int aInt = 1;
int bInt = 2;

float aFloat = 10.0f;
float bFloat = 3.0f;

// 연산자
// 사칙연산 (이형연산자)
// + - * / %
// + : a + b
// - : a - b
// * : a * b
// / : a / b
// -> 정수 / 정수 : 몫
// -> 실수 / 실수 : 값
// % : a % b => 나머지
// -> 순환하는 구조에서 많이 쓰인다.

// = : 대입연산자
// a = b : a에다가 b를 대입하고 a를 반환한다.
// a = a + b => a += b
// a = a - b => a -= b
// a = a * b => a *= b
// a = a / b => a /= b

// 증감연산자
// ++ --
// ++a : 전위연산자 : a의 원본에 1을 더하고 a의 원본을 반환
// a++ : 후위연산자 : a의 원본을 반환하고 a의 원본에 1을 더함

// bool : 0이면 false, 0이 아닌 다른수가 오면 true
// 비교연산자
// == != < > <= >=
// a == b : a와 b가 같으면 true, 다르면 false
// a != b : a와 b가 다르면 true, 같으면 false
// a > b : a가 b보다 크면 true, 그렇지 않으면 false
// a < b : a가 b보다 작으면 true, 그렇지 않으면 false
// a >= b : a가 b보다 크거나 같으면 true, 그렇지 않으면 false
// a <= b : a가 b보다 작거나 같으면 true, 그렇지 않으면 false

// 논리연산자
// ! && ||
// ! : not (true면 false로 false면 true로)
// a && b : and (a와 b가 모두 true면 true 아니면 false)
// a || b : or (a, b 둘 중 하나라도 true면 true, 아니면 false)

// 비트연산
// & | ^ >> <<
// a & b : 비트의 각 자릿수를 and 처리
// a | b : 비트의 각 자릿수를 or
// a ^ b : xor (비트가 서로 같지 않을 때 1, 같으면 0)
// a ^ b ^ b == a
// << : 왼쪽 shift 연산
// -> *2가 된다.
// -> 오른쪽은 항상 0으로 채워진다. (부호가 바뀔 수 있음)
// >> : 오른쪽 shift 연산
// -> 맨 오른쪽 비트는 버려짐
// -> 부호비트가 있을 경우 음수면 1, 양수면 0
__int64 t = (1 << 63) | (1 << 62);

// 비트플래그
// [기절]