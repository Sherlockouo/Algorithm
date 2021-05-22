
#define ll long long
const int maxn = 200010;
const double eps = 1e-8;
const int mod = 1000000007;

struct IInterval {
    int l, r;  
    IInterval(int _l, int _r): l(_l), r(_r) {}
    int len() const {
        return r - l + 1;
    }
    void print() {
        printf("[%d, %d]\n", l, r);
    }
};

//  g(x) = n / x     (x in [1, maxx])
// �� g(x) �Ķ����� x �ֲ�� ��� 2sqrt(n) �����䣬�洢�� ret ���� 
void integerSplit(int maxx, int n, vector<IInterval> &ret) {
    ret.clear();
    double sqrtn = sqrt(n + 0.0);
    int last = 1;
    // 1. ���� x <= sqrt(n) �Ĳ��֣� 
    for(int x = 1; x <= sqrtn; ++x) {
        if(x > maxx) {
            return;
        } 
        ret.push_back( IInterval(x, x) );
        last = x;
    }
    int intsqrtn = (int)(sqrtn + eps);
    // 2. ���� x > sqrt(n) �Ĳ��� ���� g(x) < sqrt(n) ��������� 
    for(int x = intsqrtn; x >= 1; --x) {
        int now = n / x;
        
        if(last+1 > now) {
            continue;
        }
        
        if(now > maxx) {
            now = maxx;
            ret.push_back( IInterval(last+1, now) );
            return ;
        }
        ret.push_back( IInterval(last+1, now) );
        last = now;
    }
}

class Solution {
public:
    /**
     * �����е����������������������Ѿ�ָ���������޸ģ�ֱ�ӷ��ط����涨��ֵ����
     * ����1-n������k*m�ĺ�
     * @param num long������ ������ n
     * @return long������
     */
    ll sqrMod(ll x) {
        x %= mod;
        return x * x % mod; 
    }
    long long cowModCount(long long num) {
        // write code here
        vector<IInterval> ret;
        integerSplit(num, num, ret);
        ll ans = 0;
        for(int i = 0; i < ret.size(); ++i) {
            ll val = num / ret[i].l;
            ans += num % mod * val % mod * ret[i].len();
            ll p = ((ll)ret[i].l+ret[i].r)*ret[i].len()/2 % mod;
            ans -= sqrMod(val) * p % mod;
            ans %= mod;
        }
        ans = (ans + mod) % mod;
        return ans;
    }
};
