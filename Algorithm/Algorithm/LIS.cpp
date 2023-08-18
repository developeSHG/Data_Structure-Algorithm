#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
#include <windows.h>

// 오늘의 주제 : 동적 계획법 (DP)
// LIS (Longest Increasing Sequence)

int cache[100];
vector<int> seq;

int LIS(int pos)
{
	// 기저 사항

	// 캐시 확인
	int& ret = cache[pos]; // & 래퍼런스 타입이니 원본 cache에도 값이 추후 업데이트된다.
	if (ret != -1)
		return ret;

	// 구하기

	// Seq : 1 9 2 5 7
	//
	// 1 9 = 2
	// 1 2 5 7 = 4
	// 1 5 7 = 3		LIS(0) -> 1 + LIS(3) -> 1 + LIS(4)
	// 1 7 = 2			LIS(0) -> 1 + LIS(4)
	// 중복되는 과정은 캐시에 값이 있으면 바로 반환해준다.

	// 최소 seq[pos]은 있으니 1부터 시작
	ret = 1;

	// 구하기
	for (int next = pos + 1; next < seq.size(); next++)
		if (seq[pos] < seq[next])
			ret = max(ret, 1 + LIS(next));

	return ret;
}

int main()
{
	::memset(cache, -1, sizeof(cache));
	seq = vector<int>{ 10, 1, 9, 2, 5, 7 };

	int ret = 0;

	// 시작점이 제일 큰 수일 수 있으니 모든 경우에 대해 시작점으로 다 돌려준다.
	for (int pos = 0; pos < seq.size(); pos++)
		ret = max(ret, LIS(pos));

}