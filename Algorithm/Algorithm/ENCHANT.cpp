#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
#include <windows.h>

// 오늘의 주제 : 동적 계획법 (DP)
// ENCHANT

// +0 집행검
// 무기 강화 주문서 => +1 / +2 / +3 중 하나

// +9 집행검 뜨는 경우의 수는?
// ex) +1 +2 +3 +4 ... +9
// ex) +3 +6 +9
// ex) +1 +3 +4 

int N;
int cache[100];

// [+num]에서 시작해서, [+N]까지 가는 경우의 수
int Enchant(int num)
{
	// 기저 사례
	if (num > N)
		return 0;
	if (num == N)
		return 1;

	// 캐시
	int& ret = cache[num];
	if (ret != -1)
		return ret;

	// 적용 (강화는 +1 ~ +3까지 3가지 경우의 수이기 때문에)
	return ret = Enchant(num + 1) + Enchant(num + 2) + Enchant(num + 3);
}

int main()
{
	// N = 4; // (7)
	// +1 +2 +3 +4
	// +1 +2 +4 
	// +1 +3 +4
	// +2 +3 +4
	// +2 +4
	// +3 +4

	N = 20; // (121415)
	// +1 +2 +3 +4
	// +1 +2 +4
	// +1 +3 +4
	// +1 +4
	// +2 +3 +4
	// +2 +4
	// +3 +4

	// 메모리제이션을 사용하지 않고, 재귀만을 사용했다면 많은 부하를 잡아먹는다.
	// 특정 함수가 부분적인 연산의 결과물로 다시 재사용된다면 dp가 우월한 방식이다.

	memset(cache, -1, sizeof(cache));

	int ret = Enchant(0);
	cout << ret << endl;
}