#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
// 오늘의 주제 : 정렬

// C# 자료구조/알고리즘
// -> A* OpenList (PQ)
// -> C# List = C++ vector

// PQ O(logN)
// Red-Black Tree O(logN)
// Sorting ?



// 1) 버블 정렬 (Bubble Sort)
// 순서대로 앞 뒤로 비교해서 조건에 부합하면 자리를 바꾸고(swap), 
// 가장 큰 값을 맨 뒤부터 채워넣는 방식
void BubbleSort(vector<int>& v)
{
	const int n = (int)v.size();

	// (N-1) + (N-2) + ... + 2 + 1
	// 등차수열의 합 = N * (N-1) / 2
	// O(N^2)
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < (n - 1 - i); j++)
		{
			if (v[j] > v[j + 1])
			{
				int temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
	}
}

// [3][5][9][J][K]

// 2) 선택 정렬 (Selection Sort)
// 버블 정렬과 둘둘씩 비교해서 승자를 뒤에서 채워넣은 것처럼 방식이 유사하지만,
// 선택 정렬은 눈대중으로 전체를 스캔해서 원하는 값을 선택해 앞에서부터 채운다.
// 버블 정렬은 라운드마다 둘둘씩 대결해서 승자를 가렸다면,
// 선택 정렬은 라운드마다 전체에서 승자를 골라낸다. 
void SelectionSort(vector<int>& v)
{
	const int n = (int)v.size();

	// O(N^2)
	for (int i = 0; i < n - 1; i++)
	{
		int bestIdx = i;

		for (int j = i + 1; j < n; j++)
		{
			if (v[j] < v[bestIdx])
				bestIdx = j;
		}

		// 교환
		int temp = v[i];
		v[i] = v[bestIdx];
		v[bestIdx] = temp;
	}
}

// 3) 삽입 정렬 (Insertion Sort)
// 삽입 정렬도 선택 정렬과 매 턴마다 비교를 하는 것이 유사하긴 하지만,
// 달라지는 부분이 선택 정렬은 매 턴마다 제일 좋은 후보를 찾아 원하는 위치에 배치했다하면
// 삽입 정렬은 실시간으로 정렬된 데이터를 만들어놨다라는 느낌으로 동작한다.
// 마치 카드를 하나씩 뽑아 완성된 손에 원하는 위치로 카드를 꽂아주는 형태로 동작.
// 
// i = 2
// insertData = [5]
// [4][5][9][K][3]
// 
void InsertionSort(vector<int>& v)
{
	const int n = (int)v.size();

	// O(N^2)
	for (int i = 1; i < n; i++)
	{
		int insertData = v[i];

		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (v[j] > insertData)
				v[j + 1] = v[j];
			else
				break;
		}

		v[j + 1] = insertData;
	}
}

int main()
{
	vector<int> v{ 1, 5, 3, 4, 2 };

	std::sort(v.begin(), v.end());

	//BubbleSort(v);
	//SelectionSort(v);
	InsertionSort(v);
}