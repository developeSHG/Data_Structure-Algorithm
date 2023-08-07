#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename T>
class Node
{
public:
	Node() : _prev(nullptr), _next(nullptr), _data(T())
	{

	}

	Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
	{

	}

public:
	Node* _prev;
	Node* _next;
	T		_data;
};

template<typename T>
class Iterator
{
public:
	Iterator() : _node(nullptr)
	{

	}

	Iterator(Node<T>* node) : _node(node)
	{

	}

	// ++it
	Iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	// it++
	Iterator operator++(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_next;
		return temp;
	}

	// --it
	Iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	// it--
	Iterator operator--(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_prev;
		return temp;
	}

	// *it
	T& operator*()
	{
		return _node->_data;
	}

	bool operator==(const Iterator& other)
	{
		return _node == other._node;
	}

	bool operator!=(const Iterator& other)
	{
		return _node != other._node;
	}

public:
	Node<T>* _node;
};

template<typename T>
class List
{
public:
	List() : _size(0)
	{
		// 만약 head가 데이터가 없이 nullptr이 될 수 있다하면
		// 계속 데이터가 있는지 null check를 해줘야하는 문제가 있다.
		// 그래서 보통 리스트를 구현할 때, 사용하는 데이터만 가리키게끔 유도하는 게 아니라
		// 범위 노드란 걸 만들어서, 무작정 데이터가 없다해도 시작 상태로 노드를 두 개 만들어 주게 된다.
		// 그것이 head, tail 이고 데이터가 추가되면 head와 tail 사이로 들어간다.

		// [head] <-> ... <-> [tail]
		_head = new Node<T>();
		_tail = new Node<T>();
		_head->_next = _tail;
		_tail->_prev = _head;
	}

	~List()
	{
		while (_size > 0)
			pop_back();

		delete _head;
		delete _tail;
	}

	void push_back(const T& value)
	{
		AddNode(_tail, value);
	}

	void pop_back()
	{
		RemoveNode(_tail->_prev);
	}

private:

	// [head] <-> [1] <-> [prevNode] <-> [before] <-> [tail]
	// [head] <-> [1] <-> [prevNode] <-> [newNode] <-> [before] <-> [tail]
	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		Node<T>* prevNode = before->_prev;

		prevNode->_next = newNode;
		newNode->_prev = prevNode;

		newNode->_next = before;
		before->_prev = newNode;

		_size++;

		return newNode;
	}

	// [head] <-> [prevNode] <-> [node] <-> [nextNode] <-> [tail]
	// [head] <-> [prevNode] <-> [nextNode] <-> [tail]
	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* prevNode = node->_prev;
		Node<T>* nextNode = node->_next;

		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;

		delete node;

		_size--;

		return nextNode;
	}

	int size() { return _size; }

public:
	using iterator = Iterator<T>;

	iterator begin() { return iterator(_head->_next); }
	iterator end() { return iterator(_tail); }

	// it '앞에' 추가
	iterator insert(iterator it, const T& value)
	{
		Node<T>* node = AddNode(it._node, value);
		return iterator(node);
	}

	iterator erase(iterator it)
	{
		Node<T>* node = RemoveNode(it._node);
		return iterator(node);
	}

private:
	Node<T>* _head;
	Node<T>* _tail;
	int			_size;
};

int main()
{
	List<int> li;

	List<int>::iterator eraseIt;
	// [ ] <-> [ ] <-> [ ] <-> [ ]  <-> [ ]  <-> [ ]
	for (int i = 0; i < 10; i++)
	{
		if (i == 5)
		{
			eraseIt = li.insert(li.end(), i);
		}
		else
		{
			li.push_back(i);
		}
	}

	// list는 노드로 이루어져 중간 삽입/삭제가 빠르기 때문에 push_front도 존재하지만,
	// vector의 경우는 push_front가 없고, push_back만 존재한다.
	// vector는 앞에 데이터를 추가할 경우, 데이터들의 위치를 모두 한 칸씩 뒤로 이동해야 하기 때문에
	// 효율성이 좋지 않아 애초에 push_back만 지원한다.
	// - push_back   O(1)
	// - push_front  O(N)

	li.pop_back();

	li.erase(eraseIt);
	// 근데, 의문점이 하나 있다.
	// 리스트는 vector와 다르게 임의접근이 허용하지 않아서 데이터를 탐색하는 것이 느리다.
	// 그래서 하나 하나씩 타고가서 n번째 데이터를 찾을 수 밖에 없다.
	// 근데 n번째 데이터를 찾는 것은 느린데, 리스트의 장점인 n번째 데이터를 삭제하는 건 빠른 게 모순적이란 생각이 든다.
	// 헷갈릴 수 있는데, 중간 삽입/삭제가 빠르다고 한 것은 내가 삭제할 대상을 iterator로 들고 있는 상태에서
	// 그 위치를 기억하고 있을 때, 빠르다는 의미인 것이지. 
	// 그게 아닌, 아무것도 모르는 형태였으면 다시 n번째 데이터를 하나 하나 찾아가서 삭제해야 되기 때문에
	// 전혀 빠르지 않다는 문제가 생긴다. 
	// 결론 - List의 중간 삽입/삭제가 느리다는 것은 아니지만, 빠르다함은 조건부적으로 맞는 말이다!
	// (삭제할 위치를 저장했을 때, 빠르다)

	for (List<int>::iterator it = li.begin(); it != li.end(); it++)
	{
		cout << (*it) << endl;
	}
}