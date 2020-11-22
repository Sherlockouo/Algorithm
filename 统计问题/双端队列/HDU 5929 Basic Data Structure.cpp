/*
���⣺���� NAND ������
0 NAND 0 = 1
0 NAND 1 = 1
1 NAND 0 = 1
1 NAND 1 = 0
Ȼ���� N <= 200000 �β�����������

1) PUSH x ��  ��ջ����һ��Ԫ�� x (x=0,1)�� 
2) POP :      ����һ��ջ��Ԫ�أ� 
3) REVERSE��  ��ջִ�з�������� 
4) QUERY��    ���ջ����ջ��Ԫ�ص�  NAND �ͣ� 

��⣺
��һ��˫�˶��У� REVERSE ����ֻ��Ҫ����ָ�뷽��

PUSH ���ǰ������¹���
1. ����Ϊ�յ������ֱ�Ӳ��� 
2. ���ж�ӦԪ��Ϊ0�������ĸ�����ֱ�Ӳ��� 
3. ���ж�ӦԪ�ش���1���϶��Ƕ��1�ۼ������� 
3.1 ����Ԫ��ҲΪ1��ֱ����ԭ��Ԫ�ػ���������
3.2 ����Ԫ��Ϊ 0�������߷�������µ�ֵ 

POP �ǰ������¹�����еģ�  
1. ����Ϊ�գ��޷� POP 
2. ����λ����һ�� 0 Ԫ�أ��� POP ��ƫ��ָ�� 
3. ����λ�������ɸ�1���� POP�꣬������0�Ժ󣬽���ָ��ƫ��

REVERSE �Ĳ���ֱ�ӽ���ָ�뷽��

QUERY ���ǰ������¹���

1. �ն���ֱ����� Invalid.
2. ����ӦԪ�� cur = 0
2.1 ����г���Ϊ1�������0�� 
2.2 ����г��ȴ���1�������1�� 

3. ����ӦԪ�� cur > 1
3.1 ������г���С�ڵ���2����� cur & 1��
3.2 ������г��ȴ���2����� !(cur & 1)�� 

*/ 

#include <iostream>
#include <cstring> 
using namespace std;

#define START 200000

int Q[400010];
int ileft, iright;
int dir;

void resetQueue() {
	ileft = iright = START;
	Q[START] = -1;
}

void initQueue() {
	dir = 1;
	resetQueue();
}

void addEleByDir(int dir, int v) {
	if(dir == 1) {
		Q[++iright] = v;	
	}else {
		Q[--ileft] = v;
	}
}

void popEleByDir(int dir) {
	if(dir == 1) {
		--iright;
	}else {
		++ileft;
	}
	if(ileft > iright) {
		resetQueue();		
	}
}

int getQueueSize() {
	if(Q[ileft] == -1) {
		return 0;
	}
	return iright - ileft + 1;	
}

void Output() {
	for(int i = ileft; i <= iright; ++i) {
		printf("%d ", Q[i]);
	} 	
	puts("");
}

int main() {
	int t;
	int m, cas = 0;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &m);
		initQueue();
		
		printf("Case #%d:\n", ++cas);
		while(m--) {
			char str[100];
			scanf("%s", str);
			
			
			if( !strcmp(str, "PUSH") ) {
				int v;
				int &p = (dir==1) ? Q[iright] : Q[ileft];
				scanf("%d", &v);
				
				if(p == -1) {
					// ����Ϊ�յ������ֱ�Ӳ��� 
					p = v;
				}else if(p == 0){
					// ���ж�ӦԪ��Ϊ0�������ĸ�����ֱ�Ӳ��� 
					addEleByDir(dir, v);
				}else if(p >= 1) {
					// ���ж�ӦԪ��Ϊ1���϶��Ƕ��1�ۼ������� 
					if(v == 1) {
						// ����Ԫ��ҲΪ1��ֱ����ԭ��Ԫ�ػ���������
						p ++; 
					}else {
						// ����Ԫ��Ϊ 0�������߷�������µ�ֵ 
						addEleByDir(dir, v);
					}
				}
			}else if( !strcmp(str, "POP") ) {
				int &p = (dir==1) ? Q[iright] : Q[ileft];
				if(p == -1) {
					// ����Ϊ�գ��޷� POP 
				} else if( p == 0 ) {
					// ����λ����һ�� 0 Ԫ�أ��� POP ��ƫ��ָ�� 
					popEleByDir(dir);
				} else if(p >= 1) {
					// ����λ�������ɸ�1���� POP�꣬�пպ����ָ��ƫ��
					p--;
					if(p == 0) {
						popEleByDir(dir);
					} 
				}
				
			}else if( !strcmp(str, "REVERSE") ) {
				dir *= -1;
			}else if( !strcmp(str, "QUERY") ) { 
				int &p = (dir==1) ? Q[ileft] : Q[iright];
				if(p == -1) {
					printf("Invalid.\n");
				}else if (p == 0) {
					// ֻ��һ��Ԫ�أ��Ǿ���0���ɣ�
					// ���һ���ж��Ԫ�أ��κκ�0�����궼����1 
					int val = getQueueSize()==1 ? 0 : 1;
					printf("%d\n", val);
				}else {
					int now;
					if(getQueueSize() == 1) {
						// ���ֻ��һ��Ԫ��
						now = (p&1); 
					}else if(getQueueSize() == 2) {
						// ��һ���ض��� 0����������ǣ� 
						now = (p&1); 
					}else {
						// ����ǰ��������������һ���� 1���ٺ�1 NAND ֮��õ���
						now = (p&1)?0:1;
					}
					
					printf("%d\n", now  );
				}
			} 
			
			//Output();
		}
	}
	return 0;
} 
