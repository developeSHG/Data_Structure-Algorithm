#include "BinarySearchTree.h"
#include <iostream>
#include <windows.h>
using namespace std;

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

// Tree ������ ���������� ���� ���� �ӽ������� ���� �Լ�
void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr)
		return;

	SetCursorPosition(x, y);

	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);
}

void BinarySearchTree::Print_Inorder(Node* node)
{
	// ���� ��ȸ (preorder traverse)
	// ���� ��ȸ (inorder)
	// ���� ��ȸ (postorder)
	if (node == nullptr)
		return;

	//   [��]
	// [��][��]
	// ���� : [��]�� �տ� �´� (�� -> �� -> ��)
	// ���� : [��]�� �߰��� �´� (�� -> �� -> ��)
	// ���� : [��]�� �������� �´�. (�� -> �� -> ��)
	cout << node->key << endl;
	Print_Inorder(node->left);
	Print_Inorder(node->right);
}

// 1. ��� ���� 
// ���������� ������������ �����ϰ�, �Լ��� ȣ���ϱ� ������ ���ѷ��� ������ ������
// �������� ��� ������ ����.
Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr || key == node->key)
		return node;

	if (key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);
}

// 2. ���ѷ��� ����
Node* BinarySearchTree::Search2(Node* node, int key)
{
	while (node && key != node->key)
	{
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	return node;
}

Node* BinarySearchTree::Min(Node* node)
{
	while (node->left)
		node = node->left;

	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node->right)
		node = node->right;

	return node;
}

// ���� node���� �������� ū ��
Node* BinarySearchTree::Next(Node* node)
{
	// node�� right node���� ������ left node�� ���� node���� �������� ū ���̴� Min ȣ��
	if (node->right)
		return Min(node->right);

	// ���� right�� node�� ���� ���, 
	// ���� Ʈ������ 26�� �����ߴ� �����غ���. ���� 30�� ���;��Ѵ�.
	//     [20]
	// [10]    [30]
	//      [25]  [40]
	//        [26]  [50]

	Node* parent = node->parent;

	// left node�� ���� �ڵ带 ���� ���ѷ����� ��Ÿ �ٷ� �ڽź��� ū parent�� ��ȯ������
	// right node�� �ڽ��� �θ𺸴� ũ��.
	// �׷��� parent�� parent�� ��ȯ�Ѵ�. (������ ū �ּ����� ù���� node)

	while (parent && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr;

	while (node)
	{
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

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	//     [20]
	// [10]    [30]
	//      [25]  [40]
	//        [26]  [50]
	
	// �� 3���� ���̽��� �ִ�. (Replace �Լ������� ����ó���� �Ǿ��ִ�.)
	if (node->left == nullptr) // 1. left node�� ���� ��� : right node�� ���� node�� �Ǹ� �ȴ�.
		Replace(node, node->right);
	else if (node->right == nullptr) // 2. right node�� ���� ��� : left node�� ���� node�� �Ǹ� �ȴ�. 
		Replace(node, node->left);
	else // 3. �ڽ� �� �� ���� ��� : Next �Լ��� �̿��� ���� node���� ���� ū ���� ã�� ��ü�Ѵ�.
	{
		// ���� ������ ã��
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

// u ����Ʈ���� v ����Ʈ���� ��ü
// �׸��� delete u
void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == nullptr)
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if (v)
		v->parent = u->parent;

	delete u;
}
