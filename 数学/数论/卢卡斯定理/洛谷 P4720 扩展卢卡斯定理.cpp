#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long 
#define maxn 1000010

int primes[maxn];
bool notprime[maxn];
ll FacCache[maxn];

struct factor {
	int prime, count;
	factor() :prime(0), count(0) {}
	factor(int p, int c) : prime(p), count(c) {}
	void print() {
		printf("(%d, %d)\n", prime, count);
	}
};

void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for(int i = 2; i < maxn; i++) {
		if( !notprime[i] ) {
			primes[ ++primes[0] ] = i;
		    //��Ҫע��i*i�������ͺ��ɸ��������⣬����ת���� long long 
			for(ll j = (ll)i*i; j < maxn; j += i) {
				notprime[j] = true;
			}
		}
	}
}

// ��ʽ�ֽ� - ��n�ֽ�������ݳ˻�����ʽ
// ������
// 252 = (2^2) * (3^2) * (7^1) 
// �� ans = [ (2,2), (3,2), (7,1) ]
void Factorization(int n, vector <factor>& ans) {
	ans.clear();
	if(n == 1) {
		return ;
	}
	// �����Գ� 
	for(int i = 1; i <= primes[0]; i++) {
		if(n % primes[i] == 0) {
			factor f(primes[i], 0);
			while( !(n % primes[i]) ) {
				n /= primes[i];
				f.count ++;
			}
			ans.push_back(f);
		}
		if(n == 1) {
			return ;
		}
	}
	// ©��֮������ ������MAXP�����������1�� 
	ans.push_back( factor(n, 1) );
}


// ���ֿ����� 
ll Exp(ll a, ll n, ll Mod){
	ll ans = 1;
	while (n){
		if (n & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		n >>= 1;
	}
	return ans;
}

// ����С���� 
ll Inv(ll a, ll p) {
    return Exp(a, p-2, p);
}

// ����׳� ģ p������ FacCache
void CalcCache(int n, int p) {
    FacCache[0] = 1 % p;
    for(int i = 1; i <= n; ++i) {
        FacCache[i] = FacCache[i-1] * i;
        if(FacCache[i] >= p) FacCache[i] %= p;
    }
}

// С�����ģ p 
// n,m < p
ll SmallComb(int n, int m, int p) {
    if(m == 0 || m == n) {
        return 1;
    }else if(m > n) {
        return 0;
    }
    // n! * m!^(-1) * (n-m)!^(-1)
    ll ans = FacCache[n] * Inv( FacCache[m], p) % p;
    return ans * Inv( FacCache[n-m], p) % p;
} 

// lucas ����
ll Lucas (ll n, ll m, int p) {
    if(m == 0) {
        return 1;
    }
    return Lucas(n/p, m/p, p) * SmallComb(n % p, m % p, p) % p;
}
 
// �������ģ p
ll BigComb(ll n, ll m, int p) {
    if(p == 1) {
        return 0;
    }
    CalcCache(p, p);
    return Lucas(n, m, p);
} 

// ���� �й�ʣ�ඨ�� ���� 

ll GCD(ll a, ll b) {
    return b ? GCD(b, a%b) : a;
}

class ModPair {
private:
    ll m_;   // modulus
    ll a_;   // remainder
public:
    ModPair() {}
    ModPair (ll m, ll a) : m_(m), a_(a) {}
    void standardization();
    ll lcm (ll om) const;
    ll getModulus() const { return m_;}
    void setModulus(ll m) {m_ = m;}
    ll getRemainder() const { return a_;}
    void setRemainder(ll a) {a_ = a;} 
};

void ModPair::standardization() {
    if(m_ < 0) {
        m_ = -m_;
    }
    a_ = (a_ % m_ + m_) % m_;
}
ll ModPair::lcm (ll om) const {
    ll g = GCD(om, m_);
    return om / g * m_;
}
    

// ��չŷ�����
// aX + bY = 1 
ll ExpGcd(ll a, ll b, ll &X, ll &Y) {
    ll q, temp;
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

// long long �˷���������汾 
ll Product_Mod(ll a, ll b, ll mod) {
   ll sum = 0;
   int flag = (b >= 0 ? 1 : -1);
   if(flag < 0) {
       b = -b;
   }
   while(b) {
       if(b & 1) 
           sum = (sum + a) % mod;
       a = (a + a) % mod;
       b >>= 1;
   }
   return (sum * flag + mod) % mod;
}

// �й�ʣ�ඨ�� ģ��
// return -1 ��ʾ�޽� 
ModPair chineseRemain(int n, ModPair* mp) {
    /********************(1)********************/
    for(int i = 0; i < n; ++i) {
        mp[i].standardization();
    } 
    ModPair ans = mp[0];
    ll A, B, C, X, Y;
    for(int i = 1; i < n; i++) {
        /********************(2)********************/
        A = ans.getModulus();         
        B = -mp[i].getModulus();
        C = mp[i].getRemainder() - ans.getRemainder();
        ll g = GCD(A, B);
        if( C % g ) {     
            ans.setRemainder(-1);             
            return ans;
        }
        /********************(3)********************/
        A /= g, B /= g, C /= g;
        /********************(4)********************/
        if(A < 0) {
            A = -A, B = -B, C = -C;
            B = ((B % A) + A) % A;
        }
        /********************(5)********************/
        ExpGcd(A, B, X, Y);
        Y = Product_Mod(Y, C, A);
        /********************(6)********************/
        ll tmpm = A * mp[i].getModulus();
        ll tmpr = (mp[i].getRemainder() + Product_Mod(mp[i].getModulus(), Y, tmpm)) % tmpm;
        
        ans.setModulus(tmpm);
        ans.setRemainder(tmpr);
    }
    return ans;
}

ModPair mp[maxn];

int main() {
    
    ll n, m;
    int p;
    Eratosthenes();
    
    while(scanf("%lld %lld %d", &n, &m, &p) != EOF) { 
        vector <factor> ans;
        Factorization(p, ans);
                          

    }
    return 0;
}
