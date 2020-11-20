/*
lazy˼��
Ⱦɫģ��
�ʺ���ɫ��Ŀ����(64����)������Ⱦɫ���⡣
���������
1����ĳ�������������Ⱦɫ��
2��ѯ��ĳ�������������ɫ��������ࡢ��Ŀ�ȵȣ���
�������ͣ�
poj 2777 Count Color
hdu 5023 A Corrupt Mayor's Performance Art
���洢
��ɫֵ��λ��colorBit��ÿ����ɫ��2��������ʾ����ɫֵ��ʾ�ֱ�Ϊ1��2��4��8...������������Щ��ɫ�Ϳ��������ǵĻ�����ʾ
�ӳٱ��lazy���ö�������ȫ��Ⱦɫ����lazy������ɫ�������lazyҪô��2���ݣ�Ҫô��0

�ӿ�˵��
giveLazyToSon      �����ӳٱ�Ǹ������ӽ�㣨�����ӽ���updateByValue������lazy���ã�
updateByValue      ͨ��ĳ����ɫֵ���µ�ǰ�����Ϣ������colorBit��lazy��
updateFromSon      ͨ�������ӽ����µ�ǰ�����Ϣ������colorBit��
mergeQuery         ѯ��ʱ���ڶԷָ����ӽ����кϲ��ã���ͬ���ʵ�ֲ�ͬ

����˵��
������              ���þ�̬����   treeNode::segtree_build(1, 1, n);
����([x, y], val)�� ���þ�̬����   treeNode::segtree_insert(1, 1, n, x, y, val);
ѯ��([x, y]):       ���þ�̬����   treeNode::segtree_query(1, 1, n, x, y, ans);

*/
#include <iostream>

using namespace std;

#define MAXN 1048576
typedef int ValueType;


// ����[l, r]��[x, y]�����߶��Ƿ��ཻ
bool is_intersect(int l, int r, int x, int y) {
	return !(r < x || l > y);
}
// ����[x, y]�Ƿ���ȫ����[l, r]
bool is_contain(int l, int r, int x, int y) {
	return x <= l && r <= y;
}

struct treeNode {
	ValueType lazy;
	ValueType colorBit;
	int pid;
	int len;

	treeNode() {
		reset(-1, 0);
	}
	void reset(int p, int _len) {
		pid = p;
		colorBit = 0;
		lazy = 0;
		len = _len;
	}
	int lson() { return pid << 1; }
	int rson() { return pid << 1 | 1; }

	void updateByValue(ValueType _val);
	void giveLazyToSon();
	void updateFromSon();

	// ѯ�ʵ�ʱ�򽫽��ϲ�������
	void mergeQuery(int p);

	// ���� 
	static void segtree_build(int p, int l, int r);
	// �����߶�[x, y]��[l, r]
	static void segtree_insert(int p, int l, int r, int x, int y, ValueType val);
	// ����ѯ��[x, y]�ϵ���Ϣ
	static void segtree_query(int p, int l, int r, int x, int y, treeNode& ans);

};

/* ȫ�ֱ���
nodes[MAXN*2] �洢���о�̬�߶������(��̬���ڴ�̫��ʱ��)
totalNodes    �洢�����Ŀ
*/
treeNode nodes[MAXN * 2];

void treeNode::updateByValue(ValueType _val) {
	lazy = _val;
	colorBit = _val;
}

void treeNode::giveLazyToSon() {
	if (lazy) {
		nodes[lson()].updateByValue(lazy);
		nodes[rson()].updateByValue(lazy);
		lazy = 0;
	}
}

void treeNode::updateFromSon() {
	colorBit = nodes[lson()].colorBit | nodes[rson()].colorBit;
}

void treeNode::mergeQuery(int p) {
	colorBit |= nodes[p].colorBit;
}

void treeNode::segtree_build(int p, int l, int r) {
	// �����߶�������ʱ��ֻ��Ҫ֪�����߶�������Ͻ����ĳ��ȣ�����˵㲻�ô棬�����ڵݹ��ʱ����Ϊ��������
	nodes[p].reset(p, r - l + 1);
	nodes[p].colorBit = (1 << 1);
	if (l < r) {
		int mid = (l + r) >> 1;
		// �ݹ鴴�����Ҷ��ӽ��
		treeNode::segtree_build(p << 1, l, mid);
		treeNode::segtree_build(p << 1 | 1, mid + 1, r);
		nodes[p].updateFromSon();
	}
}

void treeNode::segtree_insert(int p, int l, int r, int x, int y, ValueType val) {
	if (!is_intersect(l, r, x, y)) {
		return;
	}
	if (is_contain(l, r, x, y)) {
		nodes[p].updateByValue(val);
		return;
	}
	nodes[p].giveLazyToSon();
	int mid = (l + r) >> 1;
	treeNode::segtree_insert(p << 1, l, mid, x, y, val);
	treeNode::segtree_insert(p << 1 | 1, mid + 1, r, x, y, val);
	nodes[p].updateFromSon();
}

void treeNode::segtree_query(int p, int l, int r, int x, int y, treeNode& ans) {
	if (!is_intersect(l, r, x, y)) {
		return;
	}
	if (is_contain(l, r, x, y)) {
		ans.mergeQuery(p);
		return;
	}
	nodes[p].giveLazyToSon();
	int mid = (l + r) >> 1;
	treeNode::segtree_query(p << 1, l, mid, x, y, ans);
	treeNode::segtree_query(p << 1 | 1, mid + 1, r, x, y, ans);
	nodes[p].updateFromSon();
}

int n, m;
int main() {
	int i;
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		treeNode::segtree_build(1, 1, n);
		int maxz = 2;
		while (m--) {
			char str[10];
			int x, y, z;
			scanf("%s %d %d", str, &x, &y);
			if (str[0] == 'P') {
				scanf("%d", &z);
				treeNode::segtree_insert(1, 1, n, x, y, 1 << z - 1);
				if (z > maxz) {
					maxz = z;
				}
			}
			else {
				treeNode ans;
				treeNode::segtree_query(1, 1, n, x, y, ans);
				bool flag = false;
				for (i = 0; i < 30; i++) {
					if ((1 << i) & ans.colorBit) {
						if (flag) {
							printf(" ");
						}
						flag = 1;
						printf("%d", i + 1);
					}
				}
				puts("");
			}
		}
	}
	return 0;
}