#include "Framework.h"
// �̸� �����ϵ� ���
// 1. framework Ŭ���� �߰�
// 2. framework.h �� ���� �������� h�� include ���ֱ�
// 3. framework.cpp -> �Ӽ� -> �̸������ϵ� ���(���) -> �̸� �����ϵ� ��� : framework.h
// 4. ������Ʈ -> �Ӽ� -> �̸������ϵ� ���(�����) -> �̸� �����ϵ� ��� : framework.h

// ����
// 1. ���� �Է��� ���� ��� Ŭ���� ����, ��ǻ�ʹ� �������� �ϳ��� ���� ���� ( ex)1. Knight, 2. Mage, 3. Archer )
// 2. ���� ������ ��ü�� ��ǻ���� ��ü�� ����
// 3. ���� ���� ������ �ο� �ݺ�

int main()
{
	Player p("hanil", 100, 10);
	Knight k("Knight", 200, 15);
	Mage m("Mage", 80, 30);

	k.AttackMage(&m);
	m.AttackKnight(&k);

	return 0;
}