#include <iostream>

// std 클래스에 정의된 함수들을 사용하겠다고 선언 (std::cout 등을 사용할 때 std::를 생략할 수 있음)
using namespace std;

// 컴파일 :
// - 인간이 이해할 수 있는 소스코드를 컴퓨터(CPU)가 이해할 수 있는 언어로 번역하는 작업
// - 크게 4가지(전처리, 컴파일,어셈블리, 링크)로 나뉜다
// 1. 전처리 :
// - 전처리기를 통해 소스코드를 변환시켜준다
// -> 주석 제거 : 주석은 컴퓨터에겐 필요없는 내용이기 때문에 모두 제거
// -> # 처리 :
// --> 헤더파일 삽입 : #include 헤더파일의 모든 내용을 소스코드내에 복사
// --> 매크로 치환 및 적용 : #define된 내용 치환
// 2. 컴파일 :
// - 컴파일러를 통해 전처리 된 소스코드 파일의 오류를 검사하고 고수주언어(C++)를 저수준언어(어셈블리어)로 변환한다
// 3. 어셈블리 :
// - 어셈블리어를 오브젝트파일(기계어)로 변환
// 4. 링크 :
// - 오브젝트파일과 라이브러리 파일(프로그래밍을 위해 미리 만들어진 함수나 변수)을 연결하여 실행파일로 변환한다.

// bit : 0, 1로 표시되는 가장 작은 단위 수
// byte : 8개의 bit로 표시되는 단위

// 변수
// 변수 선언 방법
// (자료형)(변수이름) = (초기화);
int a = 5;
int b = 5.1f; // 소수점아래는 버리고 5만 저장

// DataType -> 자료형
// 정수형 자료형 : 
// - int
// 크기 : 4바이트 (32비트 환경), 8바이트 (64비트 환경)
// 나타낼 수 있는 수 : 2^32 (2^31-1 ~ -2^31) (약 21억 ~ -21억)
int aInt = 5;

// - short
// 크기 : 2바이트
// 나타낼 수 있는 수 : 2^16 (2^15-1 ~ -2^15) (32767 ~ -32768)
short aShort = 123;

// - long long, __int64 (64비트 환경 : long long, __int64) 
// 크기 : 8바이트
// 나타낼 수 있는 수 : 2^64 (2^63-1 ~ -2^63) (약 900경 ~ -900경)
long long aLongLong = 123456;
__int64 a__Int64 = 123456;

// 2 보수법 (음의 정수로 바꾸는 방법)
// 1. 모든 비트를 반대로 바꿔준다.
// 2. + 1비트

// 부호가 없는 정수형(자연수)
unsigned short aUshort; // (2^16 ~ 0)
unsigned int aUint; // (2^32 ~ 0)
unsigned long aUlong; // (2^64 ~ 0)

// 정수형 오버플로우 : 자료형의 최댓값보다 큰 값이 저장될 때 넘친 값 만큼 최솟값부터 다시 계산하여 저장되는 경우
// 정수형 언더플로우 : 자료형의 최솟값보다 작은 값이 저장될 경우 넘친 값 만큼 최댓값부터 다시 계산하여 저장되는 경우

// 실수형 (소수가 포함된)
// - float
// 크기 : 4바이트
float aFloat = 2.125f; // float 자료형은 뒤에 숫자 뒤에 f가 붙어야 숫자가 제대로 인식된다

// 실수 저장하는 방법
// 부동소수점
// 111.12
// 1.1112 * 10^2

// 2.125
// 0b 10.001
// 0b 1.0001 * 2^1
// 부호 : 0
// 지수부 : 1 + 127 -> 128 => 1000 0000
// 유효숫자 : 0001
// 부호(1) + 지수(8) + 유효숫자(23) -> 32비트
// 0 1000 0000 00010000 ... 0000

// - double
// 크기 : 8바이트
double aDouble = 2.222;

// 논리형
// 크기 : 1바이트
bool aBool = 0;

// 문자형
// 크기 : 1바이트
char aChar = 'a'; // 아스키코드 ASCII
// 유니코드 (wchar)
// - UTF-8 : 알파벳, 숫자 : 1바이트/ 한글, 중국어 : 3바이트
// - UTF-16 : 알파벳, 숫자, 한글, 중국어 : 2바이트/ 고대문자 : 4바이트

// Escape Sequence
// \n : 줄바꿈
// \t : Tab
// \' : '표시
// \0 : NULL 표시

// 사용자 정의 자료형
struct Pos
{
	int x;
	int y;

	Pos operator+(const Pos& other) // Pos의 +연산자 오버로딩
	{
		Pos result;
		result.x = x + other.x;
		result.y = y + other.y;

		return result;
	}
};

int main()
{
	// 자료형과 크기
	cout << "aInt : " << aInt << endl;
	cout << "aInt의 크기 : " << sizeof(aInt) << endl;

	// short
	cout << "aShort : " << aShort << endl;
	cout << "aShort의 크기 : " << sizeof(aShort) << endl;

	// long long
	cout << "aLongLong : " << aLongLong << endl;
	cout << "aLongLong의 크기 : " << sizeof(aLongLong) << endl;

	// __int64
	cout << "a__Int : " << a__Int64 << endl;
	cout << "a__Int64의 크기 : " << sizeof(a__Int64) << endl;

	// float
	cout << "aFloat : " << aFloat << endl;
	cout << "aFloat의 크기 : " << sizeof(aFloat) << endl;

	// double
	cout << "aDouble : " << aDouble << endl;
	cout << "aDouble의 크기 : " << sizeof(aDouble) << endl;

	// bool
	cout << "aBool : " << aBool << endl;
	cout << "aBool의 크기 : " << sizeof(aBool) << endl;

	// char
	cout << "aChar : " << aChar << endl;
	cout << "aChar의 크기 : " << sizeof(aChar) << endl;

	cout << "\"Hello World!\"" << endl;

	int bInt = 5;
	int cInt = aInt + bInt;
	Pos pos;
	pos.x = 5;
	pos.y = 5;

	Pos pos2;
	pos2.x = 1;
	pos2.y = 1;
	
	Pos pos3 = pos + pos2;

	cout << "pos3.x : " << pos3.x << ", pos3.y : " << pos3.y << endl;
	cout << "pos3의 크기 : " << sizeof(pos3) << endl;

	return 0;
}