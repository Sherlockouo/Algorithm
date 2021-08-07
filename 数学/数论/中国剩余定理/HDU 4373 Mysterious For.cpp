#include <iostream>
#include <map>
#include <vector>
#include <cstring>
using namespace std; 

#define MAXC 1100010
#define MAXX 2
#define MAXP 19103
#define MOD 364875103

#define LL __int64

bool notprime[MAXP];

LL GCD(LL a, LL b) {
    return b ? GCD(b, a%b) : a;
}

// ��չŷ�����
// aX + bY = 1 
LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
     LL q, temp;
     if( !b ) {
         q = a; X = 1; Y = 0;
         return q;
     }else {
        q = ExpGcd(b, a % b, X, Y);
        temp = X; 
        X = Y;
        Y = temp - (a / b) * Y;
        return q;
     }
}

// K = m[0] * x + r[0];
// K = m[1] * y + r[1];
// K = m[2] * z + r[2];

// �����y�ı��ʽ m[0] * x - m[1] * y = r[1] - r[0];
// y = m[3] * v + r[3];


// ���Ӷ��� ģ��
// -1 ��ʾ�޽� 
LL chineseRemain(int n, LL mod[], LL rem[]) {
    LL lcm = 1;
    int i;
    // 1. Ԥ���������е�mod[]��rem[]��ת����������
    for(i = 0; i < n; ++i) {
        // K = x[i]*mod[i] + rem[i];     (KΪ���ս⣬x[i]Ϊδ֪��)
        // a.����ȡ�� 
        if(mod[i] < 0) {
            mod[i] = -mod[i];
        } 
        // b.����ȡ��
        rem[i] = (rem[i] % mod[i] + mod[i]) % mod[i];
    } 
    // 2.�������б�ģ������С������ 
    for(i = 0; i < n; i++) {
        LL g = GCD(lcm, mod[i]);
        lcm = lcm / g * mod[i];
    }
    // 3.�㷨������ �������ս�ΪK�� 
    //   ö�� i = 1 to n-1 
    //   1) �ϲ���ʽ(0)��(i)�� mod[0]*x[0] + rem[0]      = mod[i]*x[i] + rem[i];
    //                         mod[0]*x[0] - mod[i]*x[i] = rem[i] - rem[0];
    //                            A  *  X  +   B   * Y   = C;
    //   2) ������չŷ����ã����x[i] = Y = Y0 + A*t; 
    //   3) ��x[i]�����ʽ(i)���õ���   K = mod[0]*mod[i]*t + (rem[i]+mod[i]*Y0); 
    //   4) ���µ�ʽ(0)��    mod[0] = mod[0]*mod[i]
    //                       rem[0] = (rem[i]+mod[i]*Y0) % mod[0];
    //   5) n-1�ε�����ϣ�rem[0]������С�Ǹ������⡣ 
    LL A, B, C, X, Y;
    for(i = 1; i < n; i++) {
        A = mod[0];
        B = -mod[i];
        C = rem[i] - rem[0];
        LL g = GCD(A, B);
        if( C % g ) {
            return -1;
        }
        // ��ʽ����ͬʱ����g��-1����ʽ���� 
        A /= g, B /= g, C /= g;
        if(A < 0) {
            // ��һ����Ϊ�˰�A��B��ת�������� 
            A = -A, B = -B, C = -C;
            B = ((B % A) + A) % A;
        }
        ExpGcd(A, B, X, Y);
        Y = ( (Y % A * C) % A + A ) % A;
        mod[0] = A*mod[i];
        rem[0] = (rem[i] + mod[i]*Y) % mod[0];
    }
    return rem[0];
}
LL cm[100], cr[100];

struct factor {
    int prime, count;
    factor() {
    } 
    factor(int p, int c) {
        prime = p;
        count = c;
    }
    void print() {
        printf("(%d, %d)\n", prime, count);
    }
};
vector <factor> Factor;

void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    int i;
    int u = MOD;
    for(i = 2; i < MAXP; i++) {
        if( !notprime[i] ) {
            if(u % i == 0) {
                u /= i;
                factor f(i, 1);
                while(u % i == 0) {
                    u /= i;
                    ++f.count;
                }
                Factor.push_back(f);
            }
            //��Ҫע��i*i�������ͺ��ɸ��������⣬����ת���� __int64 
            for(LL j = (LL)i*i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
    if(u != 1) {
        Factor.push_back(factor(u, 1));
    }
    
    //for(i = 0; i < Factor.size(); ++i) {
    //    Factor[i].print();
    //}
}

int n, m, k;
int a[20];

// ��Ҫ�洢 n! mod p 
LL factorialMod[MAXC][MAXX];


class PrimeIndex {
    map < int, int > primes;
    int primeCount;
public:
    PrimeIndex() {
        primeCount = 0;
    }
    void addPrime(int p) {
        if(primes.find(p) != primes.end()) {
            return ;
        }
        primes[p] = primeCount++;
    }
    
    int getIndex(int p) {
        return primes[p];
    }
    
    static PrimeIndex& Instance() {
        static PrimeIndex inst;
        return inst;
    }
};

// ��ʼ�� n! mod p 
void initFactorialMod(int n, int p) {
    int i;
    PrimeIndex &PI = PrimeIndex::Instance();
    PI.addPrime(p);
    
    int pIdx = PI.getIndex(p);
    factorialMod[0][pIdx] = 1;
    for(i = 1; i <= n; ++i) {
        factorialMod[i][pIdx] = factorialMod[i-1][pIdx] * i % p;
    }
}

// ���ֿ����� 
LL mod(LL a, LL b, LL p) {
    if(!b) {
        return 1;
    }
    LL x = mod(a*a%p, b>>1, p);
    if(b&1) {
        x = x * a % p;
    }
    return x;
}

// ���������n<p, m<p mod ����
LL Comb(int n, int m, int p) {
    // n��������ȡm�������m>n�������������ڣ�����0 
    if(m > n) {
        return 0;
    }
    // Comb(n,m,p) = n!/(m!(n-m)!) % p
    // ��x = m!(n-m)!��x'Ϊx��p����Ԫ����x*x'%p=1����Comb(n,m,p) = n!*x'%p
    // ���ݷ���С����a^(p-1)%p=1����a����ԪΪa^(p-2)%p����x' = x^(p-2)%p��
    //  Comb(n,m,p) = n! * (m!(n-m)!)^(p-2) % p
    // ����ת������ n! % p��
    int pIdx = PrimeIndex::Instance().getIndex(p);
    LL ans = 1;
    ans = ans * factorialMod[n][pIdx] % p;
    ans = ans * mod(factorialMod[m][pIdx], p-2, p) % p;
    ans = ans * mod(factorialMod[n-m][pIdx], p-2, p) % p;
    return ans;
}

// ��������� mod ���� 
// C(n,m) % p
LL Lucas(int n, int m, int p) {
    if(m == 0) {
        return 1;
    }
    return Lucas(n/p, m/p, p) * Comb(n%p, m%p, p) % p;
}

/*int main() {
    int n = 10, m = 3, p = 11;

    printf("C(%d,%d) mod %d = %I64d\n", n,m,p, Lucas(n, m, p));
    return 0;
}*/






// ��������� mod ����
// ���������Factor�� 
// MOD = 97 * 3761599
LL C(int n, int m) {
    for(int i = 0; i < Factor.size(); ++i) {
        factor f = Factor[i];
        cm[i] = f.prime;
        cr[i] = Lucas(n, m, f.prime);
    }
    return chineseRemain(Factor.size(), cm, cr);
}


LL S(int n, int t) {
    //printf("S(%d, %d)\n", n, t);
    return C(n+t, t+1);
}

int main() {
    int i, j;
    Eratosthenes();
    for(i = 0; i < Factor.size(); ++i) {
        int p = Factor[i].prime;
        initFactorialMod(MAXC-1, p);
    }
    int t, cases = 0;
    scanf("%d", &t); 
    while(t--) {
        scanf("%d %d", &n, &m);
        scanf("%d", &k);
        for(i = 0; i < k; ++i) {
            scanf("%d", &a[i]);
        }
        a[k] = m;
        
        LL ans = 1;
        for(i = 1; i <= k; ++i) {
            int t = a[i]-a[i-1]-1;
            ans = ans * S(n, t) % MOD;
        }
        printf("Case #%d: %I64d\n", ++cases, ans);
        
    }
    return 0;
}

/*
34 120 5
0 2 14 28 37
Case #X: 325627254

34 83 1 0
Case #X: 42600460
*/
