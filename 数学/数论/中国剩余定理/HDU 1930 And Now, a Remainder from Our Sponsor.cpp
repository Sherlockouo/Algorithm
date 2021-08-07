#include <iostream>
#include <cstring>

using namespace std;

#define ll long long
const int MAXN = 100010;


ll GCD(ll a, ll b) {
    return b ? GCD(b, a%b) : a;
}

class ModPair {
    /*
        x = km + a
    */
private:
    ll m_;   // modulus
    ll a_;   // remainder
public:
    ModPair() {}
    ModPair(ll m, ll a) : m_(m), a_(a) {}

    // ��׼������ m �� a ��ת��Ϊ����
    void standardization() {
        if(m_ < 0) {
            m_ = -m_;
        }
        a_ = (a_ % m_ + m_) % m_;
    }

    ll lcm (ll om) const {
        ll g = GCD(om, m_);
        return om / g * m_;
    }

    ll getModulus() const { return m_;}
    void setModulus(ll m) {m_ = m;}
    ll getRemainder() const { return a_;}
    void setRemainder(ll a) {a_ = a;} 
};


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
            ans.setRemainder(0);
            ans.setModulus(-1);             
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

 

ModPair mp[MAXN];
ll tm[MAXN], m[MAXN], r[MAXN];
int n, N;
char ansStr[100110];
int ansTop;

int main() {
    int t;
    int i, j;
    n = 4;
    scanf("%d", &t);
    while(t--) {
        ansTop = 0;
        scanf("%d", &N);
        for(i = 0; i < n; ++i) {
            scanf("%lld", &tm[i]);
        }
        for(i = 0; i < N; ++i) {
            int v;
            scanf("%d", &v);
            for(j = 0; j < n; ++j) {
                m[j] = tm[j];
                r[n-1-j] = v % 100;
                v /= 100;
            }
            for(j = 0; j < n; ++j) {
                mp[j] = ModPair(m[j], r[j]); 
            }
            ModPair ans = chineseRemain(n, mp);
            int bases = 10000;
            for(j = 0; j < 3; ++j) {
                int v = (ans.getRemainder()/bases) % 100;
                ansStr[ansTop++] = v==27? ' ': (v-1 + 'A');
                bases /= 100;
            }
        }
        while(ansTop && ansStr[ansTop-1] == ' ') ansTop--;
        ansStr[ansTop] = '\0';
        puts(ansStr);
    }
    return 0;
}
/*
10
7
2 7 6 1 4 3 5
*/
