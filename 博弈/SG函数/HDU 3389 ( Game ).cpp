/*
题意：
    给定N(N <= 10000)堆石子，每堆石子编号为i(1<=i<=N)，两人分别可以从第
A堆石子取若干石子到第B堆(B<A && (A+B)%2=1 && (A+B)%3=0)，两人轮次进行，
最后一个不能移动石子的人判为输。
题解：
    A + B = 2k' + 1
    A + B = 3k''
    则 根据中国剩余定理，A + B = 6k + 3
    于是B = (6k + 3 - A)
    当A % 6 == 3，B % 6 == 0
    当A % 6 == 2，B % 6 == 1
    当A % 6 == 5，B % 6 == 4
    由此可见，当A为1、3、4的时候将无法移动，即终止状态；
    然后来考虑一堆的情况，
        1）当A <= 6：
            i)  当A 为 1、3、4，先手必输；
            ii) 当A 为 2、5、6，直接把所有石子移动到对应的终止，所以先手必胜；
        3）当A > 6:
            i)  当A%6 == 1/3/4，无论怎么移动，对手只要将你移动的东西一直
    往终点移动，最后的情况就是面对 1、3、4 这样的终止状态，所以必输；
            ii) 当A%6 == 2/5/0，将所以石子移动到1、3、4即可让对手达到必输状态，
    所以为必胜点；
    多堆的情况其实是一样的，因为一堆会变成多堆，多堆的情况就是所有堆的sg值异或
    和了。
        根据sg值的定义，终止状态的sg值为0，当编号小于7的时候，1、3、4的sg值为0
    ，其他点的sg值为石子的数量，因为除了0这个状态不能到达，其他小于石子数量的状
    态都是可达的，更加广义的，必输点的sg为0，所以A%6 == 1/3/4的点的sg值为0，于
    是A%6 == 2/5/6的sg值就是对应的石子数量，所以最后的结论就是，将堆编号模6为2
    或者5或0的数异或，结果等于0，先手必输，否则先手必胜。
*/
#include <iostream>

using namespace std;

int main() {
    int t, n, x, i, cases = 1;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%d", &n);
        int sg = 0;
        for(i = 1; i <= n; i++) {
            scanf("%d", &x);
            if(i%6 == 2 || i%6 == 5 || i%6 == 0) sg ^= x;
        }
        printf( "Case %d: %s\n", cases++, sg ? "Alice" : "Bob" );
    }
    return 0;
}

