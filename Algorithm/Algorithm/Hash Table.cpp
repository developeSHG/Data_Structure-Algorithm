#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
// 오늘의 주제 : 해시 테이블

// Q) map vs hash_map (C++11 표준 unordered_map)

// map : Red-Black Tree
// - 추가/탐색/삭제 O(logN)

// C# dictionary = C++ map (X)
// C# dictionary = C++ unordered_map

// hash_map (unordered_map)
// - 추가/탐색/삭제 O(1)

// 살은 내주고 뼈를 취한다!
// 메모리를 내주고 속도를 취한다!

// 아파트 우편함
// [201][202][203][204][205]
// [101][102][103][104][105]

// 1~999 user(userId=1~999)
// [1][2][3][][][][][999]

// '해시' 와 '테이블' 을 따로 구현해보고 비교해보자.

// O(1)
void TestTable()
{
	struct User
	{
		int userId = 0; // 1~999
		string username;
	};

	vector<User> users;
	users.resize(1000);

	// 777번 유저 정보 세팅
	users[777] = User{ 777, "shg" };

	// 777번 유저 이름은?
	string name = users[777].username;
	cout << name << endl;

	// 테이블
	// 키를 알면, 데이터를 단번에 찾을 수 있다!

	// 문제의 상황
	// int32_max (3억~)
	// 살을 내주는 것도 정도껏 내줘야지...
	// 메모리도 무한은 아니다!
}

// 위처럼 3억명 이상이라면 메모리의 문제도 있고, 또 다르게 보안의 문제점도 있다.
// 만약 해킹을 당해서 id와 pw를 누군가 알았을 때, 그 사이트에서만 사용한다는 보장이 있는가?
// 대부분의 경우, 다른 사이트에서도 자신의 고유 id와 pw를 동일하게 사용할 경우, 큰 위험이 있다.
// 그래서 사용할 수 있는게 hash
// hash는 값을 가공해서 고유의 값으로 만들어준다.

// id: shg + pw: qwer1234
// id: shg + pw: hash(qwer1234) -> sdaf123!@#asdfasdf1234

// DB [shg][sdaf123!@#asdfasdf1234]
// 예를 들어, 이런식으로 바꿔주고 DB에다가 저장을 한다는 것.
// 그래서 홈페이지 비번 까먹을 때도 인증 단계를 거처서 새 비밀번호를 바꾸는 식으로 간다.
// 비밀번호 찾기 -> 아이디 입력 / 폰 인증 -> 새 비밀번호를 입력하세요

void TestHash()
{
	struct User
	{
		int userId = 0; // 1~int32_max
		string username;
	};

	// [][][][][][][][]
	vector<User> users;
	users.resize(1000);

	const int userId = 123456789;
	int key = (userId % 1000); // hash < 고유번호

	// 123456789번 유저 정보 세팅
	users[key] = User{ userId, "shg" };

	// 123456789번 유저 이름은?
	User& user = users[key];
	if (user.userId == userId)
	{
		string name = user.username;
		cout << name << endl;
	}

	// 충돌 문제 (즉, key값이 충돌할 때 == 해시값이 충돌을 할 때 문제가 발생함)
	// 충돌이 발생한 자리를 대신해서 다른 빈자리를 찾아나서면 된다
	// - 선형 조사법 (linear probing)
	// hash(key)+1 -> hash(key)+2
	// - 이차 조사법 (quadratic probing)
	// hash(key)+1^2 -> hash(key)+2^2

	// 이런식으로 분산을 해서 사용을 해서 충돌을 피한다.
	// 근데 이것도 한계가 있음 -> User가 엄청 늘어날 경우 애초에 bucket이 다 차버릴 수 있다.
	// 그래서 다른 방식으로 체이닝 이라는 것을 사용한다.
	// 말 그대로 백터나 연결 리스트로 충돌이 되는 키값을 연결해버리는 것이다.
	// 그래서 2차 vector를 만들어서 관리를 할 수 있다.
}

// 체이닝 - 내부적으로 배열이나 리스트 형태로 관리되고있어 계속 저장가능한 형태
// [][][][][][][][]
//       []
//       []
// O(1)
void TestHashTableChaining()
{
	struct User
	{
		int userId = 0; // 1~int32_max
		string username;
	};

	// [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
	vector<vector<User>> users;
	users.resize(1000);

	const int userId = 123456789;
	int key = (userId % 1000); // hash < 고유번호

	// 123456789번 유저 정보 세팅
	users[key].push_back(User{ userId, "shg" });
	users[789].push_back(User{ 789, "FaKer" });

	// 123456789번 유저 이름은?
	vector<User>& bucket = users[key];
	for (User& user : bucket)
	{
		if (user.userId == userId)
		{
			string name = user.username;
			cout << name << endl;
		}
	}
}

int main()
{
	//TestTable();
	TestHash();
}