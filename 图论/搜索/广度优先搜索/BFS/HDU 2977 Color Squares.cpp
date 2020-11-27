/*
���⣺3 X 3 �ĸ����У����Է��� B/R/G/Y ���ֿ飬ÿ�������Լ��ķ��������ù������£�
0. ��������ԭ���Ѿ��п��ʱ��Ҳ��������õģ������Ȱ��Ǹ����ó������ó��Ĺ��̲��㲽����
1. �κ�ʱ�򶼿��Է���һ�� B ��
2. ���Ա��� B ��ʱ�򣬿��Է�һ�� R ��
3. ���Ա��� B �� R ��ʱ�򣬿��Է�һ�� G ��
4. ���Ա��� B��R��G�����Է� Y ��
�������ڸ����ϵĿ�ķ���֮�ʹﵽ w ����С������

��⣺BFS + Ԥ����BFS����Ҫ�ľ���״̬������
1��ÿ�������ܹ��� 5��B/R/G/Y/�հף� ��״̬������9�������ܹ� 5^9 ��״̬ (ʵ�������ڸ������ƣ�״̬��ԶС�����ֵ)��
2�����ָ��ӵķ����ܺ�ֻ�����ǵġ���ϡ��й�ϵ���͡����С�û��ϵ�����Կ�������ɸѡ�����е���ϣ�ÿ���ķ�ΧΪ [0,9], ��������ֵ <= 9��Ԥ��ɸѡ�������ܹ� 715 �������
3���������� 715 ��״̬����Ӧ�ķ����ͼ����������������ʹ��ڵ���w�ģ�������״̬���Ϊ 1��������Ϊ 0��
4��������״̬���б��룬����Ȩ�ذ��մ����ң����ϵ��½��У������Ͻǵĸ�����Ϊ 5^0��Ȼ���� 5^1 ... �����½ǵĸ���Ȩ��Ϊ 5^8����Ϊ0��B��R��G��Y��Ӧ1��2��3��4��
5) �� 0 ״̬��ʼBFS������״̬Ϊ 3����Ԥ����������Ǽ���״̬�������жϽ���״̬�ı�����Ҫ�ӡ����С�ת��ɡ���ϡ�����ʽ��
6��������չ״̬��ʱ�������ô����ö��ÿ�ֿ飨��ŷֱ�Ϊ1��2��3��4����ö��ÿ�����ӣ������ܶ�Ӧλ�õ�״̬��ϵ�һ��λ���
1 -> 1<<(0)
2 -> 1<<(2-1)
3 -> 1<<(3-1)
4 -> 1<<(4-1)
��ô 1 �ſ���Ҫ����������ǣ�  λ����  & 0 == 0
2 �ſ���Ҫ�����������:   λ����  & 1 == 1
3 �ſ���Ҫ�����������:   λ����  & 11 == 11
4 �ſ���Ҫ�����������:   λ����  & 111 == 111

7��ע�⣬����ÿ��������ʵ�����ظ��ģ����Կ���Ԥ����һ�ι��Ѱ�����״̬��Ҫ���Ķ��ٲ������ܳ�����Ȼ��������������������
*/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define COMB_MAX 10000
#define MAXC 3
bool validState[COMB_MAX];

const int BLOCK_TOTAL_MASK[5] = { -1, 0, 1, 3, 7 };
const int BLOCK_SINGLE_MASK[5] = { 0, 1, 2, 4, 8 };

int power5[] = { 1, 5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125 };

int changeToComb(int arrangeCode) {
	int has[5] = { 0, 0, 0, 0, 0 };
	while (arrangeCode) {
		++has[arrangeCode % 5];
		arrangeCode /= 5;
	}
	int combCode = 1000 * has[1] + 100 * has[2] + 10 * has[3] + has[4];
	return combCode;
}

int getValueInPower(int arrangeCode, int pos) {
	return arrangeCode / power5[pos] % 5;
}

int getNextValue(int arrangeCode, int pos, int block) {
	return arrangeCode + (block - (arrangeCode / power5[pos] % 5)) * power5[pos];
}

int dir[4][2] = {
	{ 0, 1 },
	{ 0, -1 },
	{ 1, 0 },
	{ -1, 0 }
};

int step[2000000];

bool outOfBound(int posx, int posy) {
	return posx < 0 || posx >= 3 || posy < 0 || posy >= 3;
}

struct State {
	int arrageState;
	int combState;
	int cnt;

	State() {}
	State(int _a, int _c, int _cnt) : arrageState(_a), combState(_c), cnt(_cnt) {
	}
}allState[300000];
int stateTop;

void bfs() {
	int block, pos, d;
	memset(step, -1, sizeof(step));

	queue <int> Q;
	stateTop = 0;
	Q.push(0);
	step[0] = 0;
	allState[stateTop++] = State(0, 0, 0);


	while (!Q.empty()) {
		int nowState = Q.front();
		Q.pop();

		for (pos = 0; pos < 9; ++pos) {
			int posx = (pos / 3);
			int posy = (pos % 3);
			int adjMask = 0;
			for (d = 0; d < 4; ++d) {
				int nexposx = posx + dir[d][0];
				int nexposy = posy + dir[d][1];
				if (outOfBound(nexposx, nexposy)) {
					continue;
				}
				int nexpos = nexposx * 3 + nexposy;
				int adjBlock = getValueInPower(nowState, nexpos);
				adjMask |= BLOCK_SINGLE_MASK[adjBlock];
			}

			for (block = 1; block <= 4; ++block) {
				if ((adjMask & BLOCK_TOTAL_MASK[block]) == BLOCK_TOTAL_MASK[block]) {
					// ������������� pos �Ϸ��� block
					int nextState = getNextValue(nowState, pos, block);
					if (step[nextState] == -1) {
						Q.push(nextState);
						step[nextState] = step[nowState] + 1;
						allState[stateTop++] = State(nextState, changeToComb(nextState), step[nextState]);
					}
				}
			}
		}
	}
}

int main() {
	int a, b, c, d, w;
	int i, j, k, l;
	int cas = 0;
	bfs();

	while (scanf("%d", &a) != EOF && a) {
		scanf("%d %d %d %d", &b, &c, &d, &w);

		for (i = 0; i <= 9; ++i) {
			for (j = 0; j + i <= 9; ++j) {
				for (k = 0; k + j + i <= 9; ++k) {
					for (l = 0; l + k + j + i <= 9; ++l) {
						validState[i * 1000 + j * 100 + k * 10 + l] = ((a*i + b*j + c*k + d*l) >= w);
					}
				}
			}
		}
		int ans = -1;
		for (i = 0; i < stateTop; ++i) {
			if (validState[allState[i].combState]) {
				if (allState[i].cnt < ans || ans == -1) {
					ans = allState[i].cnt;
				}
			}
		}
		printf("Case %d: ", ++cas);
		if (ans == -1) {
			printf("Impossible");
		}
		else {
			printf("%d", ans);
		}

		puts("");
	}
	return 0;
}
