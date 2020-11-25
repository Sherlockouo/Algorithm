/*
���⣺N��ѧ����M�ڿΣ�ÿ�ڿ��и�����C���Լ���Ҫ�Ͽε�ʱ���б�T[]
R ��ѯ�ʣ���ʾ ѧ��A�ܹ���B�ĿΣ� ���ж������������ģ�

��⣺HASH

�������⣬trick�㣺
1������ÿ�ڿΣ�����ѧ�����󣬰���˳������
2�����һ��ѧ��Ҫ����ĳ�ڿΣ�Ҫ�������е�ʱ��㶼������в��У�

*/

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 100
#define MAXS 100

char course_names[MAXN][MAXS];
char student_names[MAXN][MAXS];
int total_student, total_course;

int find_student(char *str_stu) {
	for (int i = 0; i < total_student; ++i) {
		if (!strcmp(str_stu, student_names[i])) {
			return i;
		}
	}
	strcpy(student_names[total_student], str_stu);
	return total_student++;
}

int find_course(char *str_course) {
	for (int i = 0; i < total_course; ++i) {
		if (!strcmp(str_course, course_names[i])) {
			return i;
		}
	}
	strcpy(course_names[total_course], str_course);
	return total_course++;
}

int curCapacity[MAXN];
int stuHash[MAXN][MAXN];
int stdCurHash[MAXN][MAXN];
vector <int> curTime[MAXN];

struct Pair {
	int stu_id, cur_id;
	Pair(){}
	Pair(int s, int c) : stu_id(s), cur_id(c) {

	}

};

vector <Pair> v;

int main() {
	int N, M, R;
	char str[MAXS];
	int i, j, cas = 0;

	while (scanf("%d %d %d", &N, &M, &R) != EOF) {
		total_student = 0;
		total_course = 0;
		v.clear();
		memset(stuHash, 0, sizeof(stuHash));
		memset(stdCurHash, 0, sizeof(stdCurHash));

		for (int i = 0; i < N; ++i) {
			scanf("%s", str);
			find_student(str);
		}
		for (int i = 0; i < M; ++i) {
			scanf("%s", str);
			int cur_id = find_course(str);
			scanf("%d", &curCapacity[cur_id]);
			curTime[cur_id].clear();
			int k;
			scanf("%d", &k);
			while (k--) {
				int t;
				scanf("%d", &t);
				curTime[cur_id].push_back(t);
			}
		}
		int ans = 0;
		while (R--){
			char stu[MAXS], cur[MAXS];
			scanf("%s %s", stu, cur);
			int stu_id = find_student(stu);
			int cur_id = find_course(cur);
			v.push_back(Pair(stu_id, cur_id));
		}

		for (int cur = 0; cur < M; ++cur) {

			for (j = 0; j < v.size(); ++j) {
				if (v[j].cur_id != cur) continue;

				int stu_id = v[j].stu_id;
				int cur_id = v[j].cur_id;

				// 1.accepting the request will result in a conflict in the student's schedule
				for (i = 0; i < curTime[cur_id].size(); ++i) {
					if (stuHash[stu_id][curTime[cur_id][i]]) {
						break;
					}
				}
				if (i < curTime[cur_id].size()) continue;

				// 2.if no more students could be accepted by this class,
				if (curCapacity[cur_id] == 0) continue;

				// 3.the student has already enrolled in this class
				if (stdCurHash[stu_id][cur_id]) continue;

				// 4. accept
				stdCurHash[stu_id][cur_id] = 1;
				--curCapacity[cur_id];
				++ans;

				for (i = 0; i < curTime[cur_id].size(); ++i) {
					if (!stuHash[stu_id][curTime[cur_id][i]]) {
						stuHash[stu_id][curTime[cur_id][i]] = 1;
					}
				}
			}
		}
		printf("Case %d: %d\n", ++cas, ans);
	}


	return 0;
}