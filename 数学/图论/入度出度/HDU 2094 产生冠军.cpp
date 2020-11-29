// HDU 2094
// ͼ�ۣ� ͳ���������Ϊ0�ĵ㣬�ж��Ƿ�ֻ��һ�����Ϊ0�ĵ㼴��
// STL map/string ��Ӧ��

#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 1010

std::map<string, int> Map;
bool indeg[MAXN];

bool check() {
	int i, j, c = 0;
	int size = Map.size();
	for (i = 1; i <= size; ++i) {
		if (!indeg[i]) {
			c++;
		}
	}
	return c == 1;
}

char str[10000];
int main() {
	int i;
	int t;
	while (scanf("%d", &t) != EOF && t) {
		Map.clear();
		for (i = 0; i < MAXN; ++i) {
			indeg[i] = false;
		}

		while (t--) {
			int s, e;
			scanf("%s", str);
			if (Map.find(str) == Map.end()) {
				int c = Map.size() + 1;
				Map[str] = c;
			}
			s = Map[str];

			scanf("%s", str);
			if (Map.find(str) == Map.end()) {
				int c = Map.size() + 1;
				Map[str] = c;
			}
			e = Map[str];

			if (s != e)
			{
				indeg[e] = true;
			}
		}

		if (check()) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}

	}
	return 0;
}
