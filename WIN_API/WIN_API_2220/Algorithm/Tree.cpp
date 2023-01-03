#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// 트리
// 1. 계층적 구조를 나타내기 최적화된 자료구조
// 2. Root와 Leaf로 되어있다.
// 3. 서브트리가 존재한다. (중요)
// -> 트리는 잘라도 트리이다.

struct Node
{
	Node() {}
	Node(const string data) : _data(data) {}

	vector<Node*> _children;
	string _data;
};

Node* CreateTree()
{
	Node* node = new Node("개발팀");
	{
		Node* node1 = new Node("프로그래밍팀");
		node->_children.push_back(node1);
		{
			Node* node2 = new Node("클라이언트");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("서버");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("엔진");
			node1->_children.push_back(node2);
		}
	}

	{
		Node* node1 = new Node("기획팀");
		node->_children.push_back(node1);
		{
			Node* node2 = new Node("스토리");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("레벨 디자인");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("컨텐츠");
			node1->_children.push_back(node2);
		}
	}

	{
		Node* node1 = new Node("아트팀");
		node->_children.push_back(node1);
		{
			Node* node2 = new Node("일러스트");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("배경");
			node1->_children.push_back(node2);
		}
		{
			Node* node2 = new Node("모델");
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