#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;

// Stack (LIFO Last-In-First-Out 후입선출)

// [1][2][3][4] << 밀어넣음
// 되돌리기 (Ctrl+Z) 같은 방식

// stack은 맨 뒤에다가 데이터를 밀어넣고 꺼내오는 방식이기 때문에,
// vector를 이용해서 만들 수 있겠다 생각이 든다.
// 즉, stack도 동적 배열로 만드는 방식과 연결 리스트로 만드는 방식 둘 다 공존한다.
// 중요한 부분은 맨 뒤 데이터의 작업을 지원하면 되기 떄문에 어떤 자료구조든 stack으로 활용할 수 있다.
template<typename T, typename Container = vector<T>> // 기반 자료구조를 받을 수 있고, default 값을 vector로 잡아둠.
class Stack
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}

	// C# 방식
	// 데이터도 줄이고, 반환도 해주는 1+1
	// 근데 C++에서 하지 않는 이유는 순전히 성능 때문이다.
	// 만약 반환형이 T&여서 래퍼런스로 뱉어준다면
	// 동적 배열과 같은 형태로 만들어졌을 때, 유효하지 않은 주소를 넘겨주기 때문에 문제가 발생한다.
	// 그럼 복사같은 형식일 경우는 복사가 데이터 양에 따라 매우 무겁게 동작해서 느리고, 
	// 복사하는 과정에서 예외가 발생할 수도 있다. 그래서 C++은 top과 pop이 구분되어있는 이유다.
	//T pop()
	//{
	//	T ret = _data[_size - 1];
	//	_size--;
	//	return ret;
	//}

	void pop()
	{
		_container.pop_back();
	}

	T& top()
	{
		return _container.back();
	}

	bool empty() { return _container.empty(); }
	int size() { return _container.size(); }

private:
	// stl의 특성인, 인터페이스의 통일화로 인한 장점때문에
	// 아래의 두 가지 자료구조 중 아무거나 해도 문제없이 잘 동작한다.
	//vector<T> _container;
	//list<T> _container;

	Container _container;
};

int main()
{
	Stack<int, list<int>> s;

	// 삽입
	s.push(1);
	s.push(2);
	s.push(3);

	// 비었나?
	while (s.empty() == false)
	{
		// 최상위 원소
		int data = s.top();
		// 최상위 원소 삭제
		s.pop();

		cout << data << endl;
	}

	int size = s.size();
}