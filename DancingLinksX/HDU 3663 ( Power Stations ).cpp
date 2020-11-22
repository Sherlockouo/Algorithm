#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXR 1110
#define MAXC 400
#define INF -1
#define INT64 __int64

enum eCoverType {
    ECT_EXACT = 0,       // ��ȷ����
    ECT_REPEAT = 1,      // �ظ�����
};

/*
DLXNode
    left, right        ʮ�ֽ���˫��ѭ�����������ָ��
    up, down           ʮ�ֽ���˫��ѭ�����������ָ��

    <�������׽��>
    colSum             �еĽ������
    colIdx             �еı��
        
    <�������׽��/Ԫ�ؽ��>
    colHead            ָ�����׽���ָ��
    rowIdx             DLXNode�����ԭ�����е��б��
*/
class DLXNode {
public:
    DLXNode *left, *right, *up, *down;
    union {
        struct {
            DLXNode *colHead;   
            int rowIdx;
        }node;
        struct {
            int colIdx;
            int colSum;
        }col;
    }data;
public:
    //////////////////////////////////////////////////////////
    // ��ȡ/���� �ӿ�
    void resetCol(int colIdx);
    void resetColSum();
    void updateColSum(int delta);
    int getColSum();

    void setColIdx(int colIdx);
    int getColIdx();

    void setColHead(DLXNode *colPtr);
    DLXNode *getColHead();

    void setRowIdx(int rowIdx);
    int getRowIdx();

    ///////////////////////////////////////////////////////////
    // ��������õ��Ľӿ�
    void appendToCol(DLXNode *colPtr);
    void appendToRow(DLXNode *rowPtr);

    void deleteFromCol();
    void resumeFromCol();

    void deleteFromRow();
    void resumeFromRow();
    ///////////////////////////////////////////////////////////
};

void DLXNode::resetCol(int colIdx) {
    // IDA*��ʱ����Ҫ�õ����±����hash
    setColIdx(colIdx);
    // ��ʼ��ÿ�н�������Ϊ0
    resetColSum();
}
void DLXNode::resetColSum() {
    data.col.colSum = 0;
}

void DLXNode::updateColSum(int delta) {
    data.col.colSum += delta;
}

int DLXNode::getColSum() {
    return data.col.colSum;
}

void DLXNode::setColIdx(int colIdx) {
    data.col.colIdx = colIdx;
}
int DLXNode::getColIdx() {
    return data.col.colIdx;
}

void DLXNode::setColHead(DLXNode * colPtr) {
    data.node.colHead = colPtr;
}

DLXNode* DLXNode::getColHead() {
    return data.node.colHead;
}

void DLXNode::setRowIdx(int rowIdx) {
    data.node.rowIdx = rowIdx;
}

int DLXNode::getRowIdx() {
    return data.node.rowIdx;
}

void DLXNode::appendToCol(DLXNode * colPtr) {
    // ��ֵ����ָ��
    setColHead(colPtr);

    // �⼸��Ҫ�������˳��֤�е���������ᵼ������ÿ�β���һ�е����
    up = colPtr->up;
    down = colPtr;
    colPtr->up = colPtr->up->down = this;

    // ��Ԫ��++
    colPtr->updateColSum(1);
}

void DLXNode::appendToRow(DLXNode* rowPtr) {
    // ��ֵ�б��
    setRowIdx(rowPtr->getRowIdx());

    // �⼸��Ҫ�������˳��֤�е�����ÿ�β���һ�е����
    left =  rowPtr->left;
    right = rowPtr;
    rowPtr->left = rowPtr->left->right = this;
}

void DLXNode::deleteFromCol() {        
    left->right = right;
    right->left = left;
}

void DLXNode::resumeFromCol() {    
    right->left = left->right = this;
}

void DLXNode::deleteFromRow() {
    up->down = down;
    down->up = up;
    if (getColHead())
        getColHead()->updateColSum(-1);
}

void DLXNode::resumeFromRow() {
    if (getColHead())
        getColHead()->updateColSum(1);
    up->down = down->up = this;
}

/*
DLX ��������
    head               head ֻ�����ң�left��right������ָ����Ч��ָ������
    rowCount, colCount ������������Ĺ�ģ����������
    row[]              ���׽���б�
    col[]              ���׽���б�
    
    dlx_pool           ������أ����dlx_pool_idxȡ����
*/
class DLX {
    DLXNode *head;             // �ܱ�ͷ
    int rowCount, colCount;    // ������������Ĺ�ģ���������� 
    DLXNode *row, *col;        // ���׽���б� / ���׽���б�
    
    DLXNode *dlx_pool;         // �������
    int dlx_pool_idx;          // ��������±� 

    eCoverType eCType;
    int  *col_coverd;          // ��ǵ�i���Ƿ񸲸ǣ������ظ�����
    INT64 *row_code;           // ÿ�в��ö����Ʊ�ǽ����Ż�

public:
    int *result, resultCount;  // �������
private: 

    DLX() {
        dlx_pool_idx = 0;
        head = NULL;
        dlx_pool = new DLXNode[MAXR*MAXC];
        col = new DLXNode[MAXC+1];
        row = new DLXNode[MAXR];
        result = new int[MAXR];
        col_coverd = new int[MAXC+1];
        row_code = new INT64[MAXR];
    }

    ~DLX() {
        delete [] dlx_pool;
        delete [] col;
        delete [] row;
        delete [] result;
        delete [] col_coverd;
        delete [] row_code;
    }

    void reset_size(int r, int c, eCoverType ect) {
        rowCount = r;
        colCount = c;
        eCType = ect;
        dlx_pool_idx = 0;
        resultCount = -1;
    }

    void reset_col();
    void reset_row();
    DLXNode* get_node();
    DLXNode* get_min_col();
    int get_eval();                // ���ۺ���

    void cover(DLXNode *colPtr);
    void uncover(DLXNode *colPtr);

    void coverRow(DLXNode *nodePtr);
    void uncoverRow(DLXNode *nodePtr);

    bool isEmpty();
    
public:
                           
    void init(int r, int c, eCoverType ect);
    void add(int rowIdx, int colIdx);       // index 0-based
    void output();
    bool dance(int depth, int maxDepth);


    static DLX& Instance() {
        static DLX inst;
        return inst;
    }
};

void DLX::reset_col() {
    // [0, colCount)��Ϊ����Ԫ�أ�
    // ��colCount������Ԫ�صĵ�ַ��Ϊ�ܱ�ͷhead
    for(int i = 0; i <= colCount; ++i) {
        DLXNode *colPtr = &col[i];
        colPtr->resetCol(i);
        // ��ʼ����ÿ��Ԫ��Ϊ�գ���������ָ������ѭ��ָ���Լ�
        colPtr->up = colPtr->down = colPtr;
        // ��i��Ԫ��ָ���i-1������i==0����ָ���colCount��������ѭ��
        colPtr->left = &col[(i+colCount)%(colCount+1)];
        // ��i��Ԫ��ָ���i+1������i==colCount����ָ���0��������ѭ��
        colPtr->right = &col[(i+1)%(colCount+1)];
        col_coverd[i] = 0;
    }
    // ȡ��colCount������Ԫ�صĵ�ַ��Ϊ�ܱ�ͷ
    head = &col[colCount];
}

void DLX::reset_row() {
    for(int i = 0; i < rowCount; ++i) {
        // ��ʼ���б���
        DLXNode *rowPtr = &row[i];
        // ��ʼ���У�ÿ�ж�Ϊ�գ����Խ��ĸ���ָ�붼ָ���Լ�
        rowPtr->left = rowPtr->right = rowPtr->up = rowPtr->down = rowPtr;
        // ��Ӧcoverʱ��ĺ�����ڵķǿ��ж�
        rowPtr->setColHead(NULL);
        rowPtr->setRowIdx(i);
        row_code[i] = 0;
    }
}

DLXNode* DLX::get_node() {
    return &dlx_pool[dlx_pool_idx++];
}

void DLX::init(int r, int c, eCoverType ect) {
    reset_size(r, c, ect);
    reset_row();
    reset_col();
}

DLXNode* DLX::get_min_col() {
    DLXNode *resPtr = head->right;
    for(DLXNode *ptr = resPtr->right; ptr != head; ptr = ptr->right) {
        if(ptr->getColSum() < resPtr->getColSum()) {
            resPtr = ptr;
        }
    }
    return resPtr;
}

/*
    ���ܣ����ۺ���
    ע�⣺����ʣ���и����껹��Ҫ���еĸ�������Сֵ <= ʵ����Ҫ����Сֵ
*/
int DLX::get_eval() {
    int eval = 0;
    INT64 row_status = 0;
    DLXNode *colPtr;

    // ö��ÿһ��
    for(colPtr = head->right; colPtr != head; colPtr = colPtr->right) {
        int colIdx = colPtr->getColIdx();
        if(!(row_status & ((INT64)1)<<colIdx)) {
            row_status |= (((INT64)1)<<colIdx);
            ++eval;
            // ö�ٸ����ϵ�ô��Ԫ��
            for(DLXNode *nodePtr = colPtr->down; nodePtr != colPtr; nodePtr = nodePtr->down) {
                row_status |= row_code[nodePtr->getRowIdx()];
            }
        }
    }
    return eval;
}

/*
    ���ܣ�����һ��(rowIdx, colIdx)�Ľ�㣨��ԭ01������(rowIdx, colIdx)λ��Ϊ1�ģ�
    ע�⣺�����е������е�����˳����в���
*/
void DLX::add(int rowIdx, int colIdx) {
    //printf("%d - %d (%d %d) add \n", rowCount, colCount, rowIdx, colIdx);
    DLXNode *nodePtr = get_node();
    // �������뵽��Ӧ��β
    nodePtr->appendToCol(&col[colIdx]);
    // �������뵽��Ӧ��β
    nodePtr->appendToRow(&row[rowIdx]);
    row_code[rowIdx] |= ((INT64)1<<colIdx);
}

/*
    ���ܣ������ǰ����
    ��������
*/
void DLX::output() {
    for(int i = 0; i < rowCount; i++) {
        DLXNode *rowPtr = &row[i];
        printf("row(%d)", i);
        for(DLXNode *nodePtr = rowPtr->right; nodePtr != rowPtr; nodePtr = nodePtr->right) {
            printf(" [%d]", nodePtr->getColHead()->getColIdx());
        }
        puts("");
    }
}

/*
    ���ܣ�ɾ����
          ��ȷ������ɾ���е�ʱ����Ҫ���н���ɾ������
          ö��ÿ����nodePtr��ͬһ�еĽ��p��ִ��ɾ������ 
*/
void DLX::coverRow(DLXNode* nodePtr) {
    for(DLXNode *p = nodePtr->right; p != nodePtr; p = p->right) {
        p->deleteFromRow();
    }
}

/*
    ���ܣ��ָ���
        coverRow������� 
*/
void DLX::uncoverRow(DLXNode* nodePtr) {
    for(DLXNode *p = nodePtr->left; p != nodePtr; p = p->left) {
        p->resumeFromRow();
    }
}

/*
    ���ܣ�����colPtrָ�����һ��
         ˵�Ǹ��ǣ���ʵ��ɾ����һ�С�
         ����Ǿ�ȷ���ǣ���Ҫɾ�����������н���Ӧ���У�ԭ���ǣ�cover�����һ�ѡ�����У���������1���б��붼ɾ��
*/
void DLX::cover(DLXNode *colPtr) {
    if(!colPtr) {
        return;
    }
    if(!col_coverd[colPtr->getColIdx()]) {
        // ɾ��colPtrָ�����һ��
        colPtr->deleteFromCol();
        // ö��ÿ����colPtr��Ӧ���ϵĽ��p
        if (eCType == ECT_EXACT) {
            for(DLXNode* nodePtr = colPtr->down; nodePtr != colPtr; nodePtr = nodePtr->down) {
                coverRow(nodePtr);
            }
        }    
    }
    ++col_coverd[colPtr->getColIdx()];
}

/*
    ���ܣ��ָ�colPtrָ�����һ��
         cover�������
*/
void DLX::uncover(DLXNode* colPtr) {
    if(!colPtr) {
        return;
    }
    --col_coverd[colPtr->getColIdx()];
    if(!col_coverd[colPtr->getColIdx()]) {
        // ö��ÿ����colPtr��Ӧ���ϵĽ��p
        if (eCType == ECT_EXACT) {
            for(DLXNode* nodePtr = colPtr->up; nodePtr != colPtr; nodePtr = nodePtr->up) {
                uncoverRow(nodePtr);
            }
        }
        // �ָ�colPtrָ�����һ��
        colPtr->resumeFromCol();
    }
}

bool DLX::isEmpty() {
    return head->right == head;
}

bool DLX::dance(int depth, int maxDepth=INF) {
    // ��ǰ����Ϊ�գ�˵���ҵ�һ�����н⣬�㷨��ֹ 
    if(isEmpty()) {
        resultCount = depth;
        return true;
    }
    if (maxDepth != INF) {
        if(depth + get_eval() > maxDepth) {
            return false;
        }
    }
    if(depth == maxDepth) {
        return false;
    }

    DLXNode *minPtr = get_min_col();
    // ɾ��minPtrָ����� 
    cover(minPtr);
    // minPtrΪ��������ٵ��У�ö�����������е���
    for(DLXNode *p = minPtr->down; p != minPtr; p = p->down) {
        // ��r = p->getRowIdx()����r���뵱ǰ�� 
        result[depth] = p->getRowIdx();
        // ��r�ϵĽ���Ӧ���н���ɾ�� 
        for(DLXNode *q = p->right; q != p; q = q->right) {
            cover(q->getColHead());
        }
        // ��������������һ�� 
        if(dance(depth+1, maxDepth)) {
            return true;
        }
        // ��r�ϵĽ���Ӧ���н��лָ� 
        for(DLXNode *q = p->left; q != p; q = q->left) {
            uncover(q->getColHead());
        }
    }
    // �ָ�minPtrָ�����
    uncover(minPtr); 
    return false;
}


int mat[100][100];
int L[100], R[100];
int ansL[100], ansR[100];

struct PowDayInterval {
    int powIdx;
    int dayStart, dayEnd;
    PowDayInterval(){
    }
    PowDayInterval(int p, int ds, int de): powIdx(p), dayStart(ds), dayEnd(de) {
    }
}PI[MAXR];

bool construct_dlx(int pows, int days) {
    DLX &dlx = DLX::Instance();
    int i, j, k, l, o; 
    int rCount = 0; 
    for(i = 1; i <= pows; i++) {
        PI[rCount++] = PowDayInterval(i, 0, 0);
        for(j = L[i]; j <= R[i]; j++) {
            for(k = j; k <= R[i]; k++) {
                // [j, k]
                // ��j����k��ʹ�õ�i��powStation
                PI[rCount++] = PowDayInterval(i, j, k);
            }
        }
    }
    dlx.init(rCount, pows*days + pows, ECT_EXACT);
    
    for(i = 0; i < rCount; i++) {
        int pIdx = PI[i].powIdx;
        dlx.add(i, days*pows-1+pIdx);
        // ������ 
        if(PI[i].dayStart == 0) continue;
        for(l = 1; l <= pows; l++) {
            if(mat[pIdx][l]) {
                for(o = PI[i].dayStart; o <= PI[i].dayEnd; o++) {
                    int col = ((o-1)*pows + l - 1);
                    dlx.add(i, col);
                }
            }
        }
    }
    bool ans = dlx.dance(0, INF);
    if(!ans) {
        printf("No solution\n\n");
        return false;
    } 
    for(i = 1; i <= pows; i++) {
        ansL[i] = ansR[i] = 0;
    }
    sort(dlx.result, dlx.result + dlx.resultCount);
    for(i = 0; i < dlx.resultCount; i++) {
        int v = dlx.result[i];
        ansL[ PI[v].powIdx ] = PI[v].dayStart;
        ansR[ PI[v].powIdx ] = PI[v].dayEnd; 
    }
    for(i = 1; i <= pows; i++) {
        printf("%d %d\n", ansL[i], ansR[i]);
    }
    puts("");
    return true;
}

void test() {
    int i, j;
    DLX &dlx = DLX::Instance();
    int r = 6, c = 9;
    dlx.init(r, c, ECT_REPEAT);
    int mat[6][9] = {
        {0, 0, 1, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1, 0, 1, 1, 1},
    };
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            if(mat[i][j]) {
                dlx.add(i, j);
            }
        }
    }
    printf("%d\n", dlx.dance(0, 6));
}



int main() {
    int N, M, D;
    int i, j;
    while(scanf("%d %d %d", &N, &M, &D) != EOF) {
        for(i = 1; i <= N; i++) {
            for(j = 1; j <= N; j++) {
                mat[i][j] = (i==j) ? 1 : 0;
            }
        }
        for(i = 0; i < M; i++) {
            int x, y; 
            scanf("%d %d", &x, &y); 
            mat[x][y] = mat[y][x] = 1;
        }
        for(i = 1; i <= N; i++) {
            scanf("%d %d", &L[i], &R[i]);
        }
        construct_dlx(N, D);
    }
    return 0;
}
/*
60 2 5
1 2
1 3
1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5
1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5
1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5
1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5
1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5
1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5 1 5

4 2 5
1 2
1 3
1 5
1 5
1 5
1 5

3 2 1
1 2
1 3
1 1
1 1
1 1
*/
