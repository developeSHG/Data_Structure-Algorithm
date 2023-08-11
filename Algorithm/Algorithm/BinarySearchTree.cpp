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

// Tree 구조를 직관적으로 보기 위해 임시적으로 만든 함수
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
	// 전위 순회 (preorder traverse)
	// 중위 순회 (inorder)
	// 후위 순회 (postorder)
	if (node == nullptr)
		return;

	//   [중]
	// [좌][우]
	// 전위 : [중]이 앞에 온다 (중 -> 좌 -> 우)
	// 중위 : [중]이 중간에 온다 (좌 -> 중 -> 우)
	// 후위 : [중]이 마지막에 온다. (좌 -> 우 -> 중)
	cout << node->key << endl;
	Print_Inorder(node->left);
	Print_Inorder(node->right);
}

// 1. 재귀 형식 
// 성능적으론 스택프레임을 구성하고, 함수를 호출하기 때문에 무한루프 형식이 좋지만
// 가독성은 재귀 형식이 좋다.
Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr || key == node->key)
		return node;

	if (key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);
}

// 2. 무한루프 형식
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

// 현재 node에서 다음으로 큰 값
Node* BinarySearchTree::Next(Node* node)
{
	// node의 right node에서 마지막 left node가 현재 node에서 다음으로 큰 값이니 Min 호출
	if (node->right)
		return Min(node->right);

	// 만약 right에 node가 없을 경우, 
	// 밑의 트리에서 26을 선택했다 생각해보자. 답은 30이 나와야한다.
	//     [20]
	// [10]    [30]
	//      [25]  [40]
	//        [26]  [50]

	Node* parent = node->parent;

	// left node는 밑의 코드를 보면 무한루프를 안타 바로 자신보다 큰 parent를 반환하지만
	// right node는 자신이 부모보다 크다.
	// 그래서 parent의 parent를 반환한다. (나보다 큰 최소한의 첫번쨰 node)

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
	
	// 총 3가지 케이스가 있다. (Replace 함수에서도 예외처리가 되어있다.)
	if (node->left == nullptr) // 1. left node가 없을 경우 : right node가 현재 node가 되면 된다.
		Replace(node, node->right);
	else if (node->right == nullptr) // 2. right node가 없을 경우 : left node가 현재 node가 되면 된다. 
		Replace(node, node->left);
	else // 3. 자식 둘 다 있을 경우 : Next 함수를 이용해 현재 node보다 다음 큰 값을 찾아 교체한다.
	{
		// 다음 데이터 찾기
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

// u 서브트리를 v 서브트리로 교체
// 그리고 delete u
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
