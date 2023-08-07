#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Vector
{
public:
	Vector()
	{

	}

	~Vector()
	{
		if (_data)
			delete[] _data;
	}

	// [ ][ ][ ][ ][ ][ ] [ ]
	void push_back(const T& value)
	{
		if (_size == _capacity)
		{
			// 증설 작업
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity);
		}

		// 데이터 저장
		_data[_size] = value;

		// 데이터 개수 증가
		_size++;
	}

	void reserve(int capacity)
	{
		if (_capacity >= capacity)
			return;

		_capacity = capacity;

		T* newData = new T[_capacity];

		// 데이터 복사
		for (int i = 0; i < _size; i++)
			newData[i] = _data[i];

		if (_data)
			delete[] _data;

		// 교체
		_data = newData;
	}

	T& operator[](const int pos) { return _data[pos]; }

	int size() { return _size; }
	int capacity() { return _capacity; }

	void clear()
	{
		if (_data)
		{
			delete[] _data;
			_data = new T[_capacity];
		}

		_size = 0;
	}

private:
	T* _data = nullptr;
	int		_size = 0;
	int		_capacity = 0;
};

int main()
{
	Vector<int> v;

	v.reserve(100); // 몇 개의 데이터를 사용할지 예상할 수 있다면, 초반에 충분한 양을 예약하는 게 효율적이다.

	// size는 실제 사용한 데이터 개수
	// capacity는 전체 데이터 용량
	cout << v.size() << " " << v.capacity() << endl;

	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << v.size() << " " << v.capacity() << endl;
	}

	v.clear();
	cout << v.size() << " " << v.capacity() << endl;

	// clear를 해서 size가 0이 돼도 capacity는 유지된다.
	// 그러면, 데이터를 할당해서 capacity가 증가했다가 나중에 필요없게 되면 낭비가 아닐까? 생각하게 된다.
	// 물론 낭비가 맞긴 하지만, 동적 배열의 특성상, 메모리 이사 횟수를 최소화 하는게 중요한 일이라
	// 어느 정도의 여유분 데이터를 두어서 일부 메모리를 낭비하는 건, 사실상 메인 이슈는 아니다.
}