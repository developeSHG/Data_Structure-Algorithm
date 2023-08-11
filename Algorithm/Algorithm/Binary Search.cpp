#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// 오늘의 주제 : 이진 탐색

// 이진 탐색(binary search)
// 상황) 배열에 데이터가 정렬되어 있다

// [1][8][15][23][32][44][56][63][81][91]
// Q) 82라는 숫자가 배열에 있습니까?
// 과정) 중간값을 기준으로 절반씩 나누어 범위를 좁혀나가면서 해당값을 찾는다.
// O(Log N)

// - 정렬된 배열을 이용해서 이진 탐색 가능 (numbers[mid])
// - 정렬된 연결 리스트로는 불가 (임의 접근X)

// -- 잠깐! 그런데 배열의 단점은 뭐더라?
// --- 중간 삽입/삭제가 느리다!

// 만약 중간에 데이터가 삽입될 경우, 이진 탐색으로는 한계가 생긴다.
// 데이터가 바뀌는 상황에 한해서는 느리기 때문이다.
// 그래서 이진 탐색이 아닌 이진 탐색 트리까지 가는 이유는
// 데이터가 빈번하게 삭제되고 추가될 경우도 고려해야하기 때문에
// 필연적으로 Node 기반으로 만들어서 데이터가 유동적으로
// 변화할 수 있는 tree 구조로 만드는 것이다.

// 그게 아니라, 한 번만 데이터가 고정되어 변화하지 않을 것이라면
// 배열로 관리해서 이진 탐색을 사용하는 것도 우월한 방법이다.

vector<int> numbers;

void BinarySearch(int N)
{
	int left = 0;
	int right = (int)numbers.size() - 1;

	while (left <= right)
	{
		cout << "탐색 범위: " << left << "~" << right << endl;

		int mid = (left + right) / 2;

		if (N < numbers[mid])
		{
			cout << N << " < " << numbers[mid] << endl;
			right = mid - 1;
		}
		else if (N > numbers[mid])
		{
			cout << N << " > " << numbers[mid] << endl;
			left = mid + 1;
		}
		else
		{
			cout << "찾음!" << endl;
			break;
		}
	}

}

int main()
{
	numbers = vector<int>{ 1, 8, 15, 23, 32, 44, 56, 63, 81, 91 };
	BinarySearch(81);

}