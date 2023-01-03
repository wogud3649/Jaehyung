#include <iostream> // input : 입력 / output : 출력

// library : 도서관
// sln : solution
// - 책장
//
// project :
// - 구역

// bit : 0, 1을 나타낼 수 있는 최소 단위
// x86 : 32비트 운영체제 -> 2^32
// x64 : 64비트 운영체제 -> 2^64

// CPU, 메모리, HDD(SSD)
// CPU : 
// - 제어장치
// - 산술/ 연산 장치
// - 캐시 : 메모리 주소를 잠깐 저장해놓는 곳 (임시 세이브)
// - 레지스터 :
// -> 32비트 운영체제 : 32비트만큼 등록하고 처리
// -> 64비트 운영체제 : 64비트만큼 등록하고 처리
// RAM :
// - 저장 용량 : 8GB, 16GB, 32GB, ...
// - 휘발성 메모리
// - CPU와의 거리 : 상대적으로 가깝다
// -> 접근하는 속도가 상대적으로 빠르다
// => 폰노이만의 병목현상 : 아무리 계산을 빨리해도 메모리에 접근하고 데이터를 가져오는 속도는 더 빨라질 수 없다.
// HDD
// - 저장용량 : 1TB, 2TB, ...
// - 반영구적 메모리
// - CPU와의 거리 : 상대적으로 멀다
// -> 접근하는 속도가 상대적으로 느리다

// 전역(global) 변수
int a = 10; // Data 영역에 저장.

// 메인 함수 :
// - 프로그램의 시작점
// - 하나만 존재
// - main이 없으면 프로그램을 시작할 수 없음.
int main()
{
	// std:: -> standard library
	// std::cout : standardlibrary->cout (console out)
	// std::endl : standardlibrary->endl (end line)
	// ; : 줄 끝남 처리. (컴퓨터에게 해당 줄이 끝났음을 알려주는 것)
	std::cout << "Hello World!"; // Hello World 출력
	std::cout << "안녕하세요" << std::endl; // 안녕하세요 출력 후 다음 줄로 이동

	return 0; // 0을 반환.
}
// 프로그램 종료