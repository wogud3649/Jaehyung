#include <iostream>

using namespace std;

#include "BinarySearchTree.h"

void BinarySearchTree::Insert(int key)
{
    Node* newNode = new Node(key);
    if (_root == nullptr)
    {
        _root = newNode;
        return;
    }

    Node* node = _root;
    Node* parent = nullptr;

    while (true)
    {
        if (node == nullptr)
            break;
        parent = node;
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    newNode->parent = parent;
    if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;
}

void BinarySearchTree::PrintTree(Node* node)
{
    // 전위 순회 : 루트 - 왼쪽 - 오른쪽
    // 중위 순회 : 왼쪽 - 루트 - 오른쪽
    // 후위 순회 : 왼쪽 - 오른쪽 - 루트
    if (node == nullptr)
        return;
    cout << node->key << endl;
    PrintTree(node->left);
    PrintTree(node->right);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
    if (node == nullptr)
        return node;

    if (key == node->key)
        return node;

    if (key < node->key)
        return Search(node->left, key);
    
    if (key > node->key)
        return Search(node->right, key);
    
    return nullptr;
}

Node* BinarySearchTree::Min(Node* node)
{
    if (node->left == nullptr)
        return node;

    if (node->left != nullptr)
        return Min(node->left);

    return node;
}

Node* BinarySearchTree::Max(Node* node)
{
    if (node->right == nullptr)
        return node;

    if (node->right != nullptr)
        return Max(node->right);
    return node;
}

Node* BinarySearchTree::Previous(Node* node)
{
    if (node == nullptr)
        return node;

    if (node->left != nullptr)
        return Max(node->left);
}

Node* BinarySearchTree::Next(Node* node)
{
    if (node == nullptr)
        return node;

    if (node->right != nullptr)
        return Min(node->right);
}

void BinarySearchTree::Replace(Node* node1, Node* node2)
{
    // node1이 루트일 때
    if (node1->parent == nullptr)
        _root = node2;
    else if (node1 == node1->parent->left)
        node1->parent->left = node2;
    else
        node1->parent->right = node2;

    if (node2 != nullptr)
        node2->parent = node1->parent;

    delete node1;

}

void BinarySearchTree::Delete(Node* node)
{
    if (node == nullptr)
        return;

    if (node->left == nullptr)
        Replace(node, node->right);
    else if (node->right == nullptr)
        Replace(node, node->left);
    else
    {
        Node* prev = Previous(node);
        node->key = prev->key;
        node->data = prev->data;
        Delete(prev);

    }
}