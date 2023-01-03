#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// Ʈ��
// 1. ������ ������ ��Ÿ���� ����ȭ�� �ڷᱸ��
// 2. Root�� Leaf�� �Ǿ��ִ�.
// 3. ����Ʈ���� �����Ѵ�. (�߿�)
// -> Ʈ���� �߶� Ʈ���̴�.

struct Node
{
	Node() {}
	Node(const string data) : _data(data) {}

	vector<Node*> _children;
	string _data;
};

Node* CreateTree()
{
	Node* node = new Node("������");
	{
		Node* node1 = new Node("���α׷�����");
		node->_children.push_back(node1);
		{
			Node* node2 = new Node("Ŭ���̾�Ʈ");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("����");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("����");
			node1->_children.push_back(node2);
		}
	}

	{
		Node* node1 = new Node("��ȹ��");
		node->_children.push_back(node1);
		{
			Node* node2 = new Node("���丮");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("���� ������");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("������");
			node1->_children.push_back(node2);
		}
	}

	{
		Node* node1 = new Node("��Ʈ��");
		node->_children.push_back(node1);
		{
			Node* node2 = new Node("�Ϸ���Ʈ");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("���");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("��");
			node1->_children.push_back(node2);
		}
	}

	return node;
}

void PrintTree(Node* root, int deepth)
{
	for (int i = 0; i < deepth; i++)
	{
		cout << "-";
	}

	cout << root->_data << endl;

	for (auto& node : root->_children)
	{
		PrintTree(node, deepth + 1);
	}
}

int main()
{
	Node* root = CreateTree();
	PrintTree(root, 0);

	return 0;
}