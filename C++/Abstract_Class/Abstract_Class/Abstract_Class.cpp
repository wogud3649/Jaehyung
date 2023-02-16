// 과제
// 
// Creature
// Player // Monster
// Knight - Archer - Mage // Goblin
// 플레이어 하나 생성 (이름 cin 으로 직접 입력)
// Goblin 10마리 생성
// 플레이어가 10마리 한 번씩 공격
// -> Goblin 10마리가 플레이어 한 번씩 공격
// 어느 한 쪽이 다 죽으면 끝

#include<iostream>

using namespace std;

// 순수가상함수가 하나 이상이라도 포함되어있다면 ... 추상 클래스
class Bank // 은행 총괄
{
public:
	virtual void DepositMessage() abstract; // 순수가상함수 ... 인터페이스
	// -> 자식들아 나 이거 *무조건 오버라이딩* 해서 니네가 쓰는 함수로 만들어줘.

protected:
};

class KBBank : public Bank
{
public:
	virtual void DepositMessage() override
	{
		cout << "KB 뱅크 입니다." << endl;
	}
private:
};

class KakaoBank : public Bank
{
public:
	// 부모의 순수 가상함수를 오버라이딩 하지 않으면 객체화 시킬 수 없다.
	virtual void DepositMessage() override
	{
		cout << "Kakao Bank 입니다." << endl;
	}

private:
};

class ShinHan : public Bank
{
public:
	virtual void DepositMessage() override
	{
		cout << "신한 뱅크 입니다." << endl;
	}
private:
};

int main()
{
	// Bank* bank = new Bank(); -> 추상 클래스라서 객체화 시킬 수 없습니다.
	Bank* kakao = new KakaoBank();
	Bank* shinHan = new ShinHan();

	kakao->DepositMessage();
	shinHan->DepositMessage();
	 
	return 0;
}