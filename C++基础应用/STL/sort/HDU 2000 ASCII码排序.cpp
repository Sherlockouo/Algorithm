// HDU 2000 
// STL sort ����ӿڵļ�Ӧ��
#include <iostream>
#include <algorithm>
using namespace std;

char ch[10];
int main() {
	while (scanf("%s", ch) != EOF) {
		sort(ch, ch + 3);
		printf("%c %c %c\n", ch[0], ch[1], ch[2]);
	}
	return 0;
}
