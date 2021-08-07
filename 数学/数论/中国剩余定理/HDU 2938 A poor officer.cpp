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

 

ModPair mp[MAXN];

ll m[MAXN], r[MAXN];


class CyclicGroup {
    // original[i]��ʾԭ�ȵ����� 
    int *original;
    // originalPos �� original ���� 
    int *originalPos;
    // ����һ��arrange֮�� original���nextOriginal 
    int *nextOriginal;
    
    
    // arrange[i]�ĺ���Ϊ:
    // ���� arrange[i] ���������i��λ�ã����Ϊһ������ 
    // ie. [2,1,4,5,7,6,3]
    int *arrange;
    
    // ѭ��Ⱥ��ID 
    int *cyclicID; 
    int *cyclicCount; 
    int length;
    
public:
    CyclicGroup() {
        original = new int[MAXN]; 
        originalPos = new int[MAXN];
        nextOriginal = new int[MAXN];
        arrange = new int[MAXN];
        cyclicID = new int[MAXN];
        cyclicCount = new int[MAXN];
    }
    
    ~CyclicGroup() {
        delete [] original;
        delete [] originalPos;
         delete [] nextOriginal;
         delete [] arrange;
        delete [] cyclicID;
        delete [] cyclicCount;
    }
    
    void init(int len);
    void assignOriginal(int *ori);
    void assignArrange(int *arr);
    int getCyclicID(int idx) const;
    // ��ȡͬһ��ѭ��Ⱥ���е���һ������ 
    int getNext(int number) const; 
    void doRearrange();

    void print();
    friend bool isSameCyclicGroup(const CyclicGroup& a, const CyclicGroup& b);
    friend ll  getCyclicGroupDist(const CyclicGroup& a, const CyclicGroup& b);
};

void CyclicGroup::init(int len) {
    int i; 
    length = len;
    for(i = 1; i <= len; ++i) {
        cyclicID[i] = 0;
        cyclicCount[i] = 0;
    }
}

void CyclicGroup::assignOriginal(int *ori) {
    for(int i = 1; i <= length; ++i) {
        original[i] = ori[i];
        originalPos[ ori[i] ] = i;
    }
}

void CyclicGroup::assignArrange(int *arr) {
    for(int i = 1; i <= length; ++i)
        arrange[i] = arr[i];
}

//
// ����ǰ��3 2 1 
// ���ź�2 1 3
// getNext : 3->2->1->3... 
int CyclicGroup::getNext(int number) const {
    return nextOriginal[ originalPos[number] ];
}

void CyclicGroup::doRearrange() {
    int i;
    // 0. ���ȹ���һ������arrange��Ȼ������ original �� nextOriginal����ѭ���� 
    for(i = 1; i <= length; ++i) {
        nextOriginal[i] = original[ arrange[i] ];
    } 
    for(i = 1; i <= length; ++i) {
        // 1.�ҵ�iλ��ԭ�ȵ��Ǹ����� 
        int val = original[i];
        // 2.ȷ����û�����ѭ��Ⱥ�����û����ʼ�齨ѭ��Ⱥ 
        while(!cyclicID[val]) { 
            // 3.����val����ѭ��Ⱥ���Ϊi��ѭ��Ⱥ��Ա��������++ 
            ++cyclicCount[ cyclicID[val] = i ];
            // 4.Ѱ����һ��ͬȺ��Ա 
            val = getNext(val);
        }
        //printf("%d(%d) ", getCyclicID(i), cyclicCount[ getCyclicID(i) ]);
    }
    //puts("");
}

int CyclicGroup::getCyclicID(int idx) const {
    return cyclicID[ original[idx] ];
}

void CyclicGroup::print() {
    int i;
    for(i = 1; i <= length; ++i) {
        printf("%d ", original[i]);
    }
    puts("");
}
 
bool cyclicVisited[MAXN];
bool isSameCyclicGroup(const CyclicGroup& a, const CyclicGroup& b) {
    // ���Ȳ�һ����һ�㲻�迼�� 
    if(a.length != b.length) {
        return false;
    }
    int i;
    // ѭ���ڱ�Ų�һ�£��϶�������ͬһ��ѭ���� 
    for(i = 1; i <= a.length; ++i) {
        if(a.cyclicID[i] != b.cyclicID[i]) {
            return false;
        }
    }
    // ѭ���ڱ��һ�£����뵥����ÿ��ѭ���ڽ����ж�
    memset(cyclicVisited, false, sizeof(cyclicVisited));
    for(i = 1; i <= a.length; ++i) {
        // 1.���ĳ�����ڼ����ѭ����
        int id = a.getCyclicID(i);
        if(cyclicVisited[id]) {
            continue;
        }
        cyclicVisited[id] = true;
        
        // 2.������ѭ��Ⱥ��ѭ���ڵ������� 
        int pos_a = a.original[i];
        int pos_b = b.original[i];
        while(pos_a != pos_b) {
            pos_a = a.getNext(pos_a);
        }
        
        // 3.��ʼ��һ�Ƚ�
        do {
            //printf("%d %d\n", a.arrange[pos_a], b.arrange[pos_b]);
            if(pos_a != pos_b) {
                return false;
            }
            pos_a = a.getNext(pos_a);
            pos_b = b.getNext(pos_b);
            
        }while (pos_b != b.original[i]);
    }
    
    return true;
}

// ��������ѭ��Ⱥ�Ĳ���
// 1.����isSameCyclicGroup���뷵��True��������Ϊͬһѭ��Ⱥ
// 2.Ȼ����㵥��Ⱥ֮��Ĳ�����
// 3.�����й�ʣ�ඨ����� 
ll getCyclicGroupDist(const CyclicGroup& a, const CyclicGroup& b) {
    // ѭ���ڱ��һ�£����뵥����ÿ��ѭ���ڽ����ж�
    memset(cyclicVisited, false, sizeof(cyclicVisited));
    int top = 0;
    for(int i = 1; i <= a.length; ++i) {
        // 1.���ĳ�����ڼ����ѭ���� 
        int id = a.getCyclicID(i);
        if(cyclicVisited[id]) {
            continue;
        }
        cyclicVisited[id] = true;
        
        // 2.������ѭ��Ⱥ��ѭ���ڵ������� 
        int pos_a = a.original[i];
        int pos_b = b.original[i];
        int cnt = 0;
        while(pos_a != pos_b) {
            pos_a = a.getNext(pos_a);
            cnt++;
        }
        
        m[top] = a.cyclicCount[id];
        r[top] = cnt;
        mp[top] = ModPair(m[top], r[top]);
        //printf("%I64d %I64d\n", m[top], r[top]);
        ++top;
    }
    
    return chineseRemain(top, mp).getRemainder(); 
}

CyclicGroup st, en;
int ori[MAXN], arr[MAXN];

int main() {
    int n;
    int i;
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    while(scanf("%d", &n) != EOF && n) {
        st.init(n), en.init(n);
        for(i = 1; i <= n; ++i) ori[i] = i;
        for(i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        st.assignOriginal(ori);
        st.assignArrange(arr);
        /*for(i = 0; i < 20; ++i)
            st.play(), st.print();*/ 
        
        for(i = 1; i <= n; ++i) {
            scanf("%d", &ori[i]);
        }
        en.assignOriginal(ori);
        en.assignArrange(arr);
        
        st.doRearrange();
        en.doRearrange();
        if( isSameCyclicGroup(st, en) ) {
            printf("%lld\n", getCyclicGroupDist(st, en));
        }else {
            printf("-1\n");
        }
    }
    return 0;
}

/*
7
2 1 4 5 7 6 3
2 1 5 3 4 6 7

7
2 1 4 5 7 6 3
2 1 5 7 4 6 3

7
2 1 4 5 7 6 3
1 2 3 4 5 6 7

7
2 1 4 5 7 6 3
1 2 5 7 3 6 4

7
2 1 4 5 7 6 3
2 1 7 3 4 6 5

10
2 3 4 7 6 5 1 9 8 10
6 7 8 4 3 2 1 9 10 5

ԭ���� 
1 2 3 4 5 6 7 8 9 10
�任������� 
2 3 4 7 6 5 1 9 8 10
3 4 7 1 5 6 2 8 9 10
4 7 1 2 6 5 3 9 8 10
7 1 2 3 5 6 4 8 9 10
1 2 3 4 6 5 7 9 8 10
2 3 4 7 5 6 1 8 9 10
3 4 7 1 6 5 2 9 8 10
4 7 1 2 5 6 3 8 9 10
7 1 2 3 6 5 4 9 8 10
1 2 3 4 5 6 7 8 9 10
2 3 4 7 6 5 1 9 8 10
3 4 7 1 5 6 2 8 9 10
4 7 1 2 6 5 3 9 8 10
7 1 2 3 5 6 4 8 9 10
1 2 3 4 6 5 7 9 8 10
2 3 4 7 5 6 1 8 9 10
3 4 7 1 6 5 2 9 8 10
4 7 1 2 5 6 3 8 9 10
7 1 2 3 6 5 4 9 8 10
1 2 3 4 5 6 7 8 9 10



3
1 2 3
2 3 1

3
2 3 1
3 2 1
*/
