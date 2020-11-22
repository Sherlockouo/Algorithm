#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXR 55
#define MAXC 80
#define INF -1
#define INT64 __int64

enum eCoverType {
    ECT_EXACT = 0,        // ��ȷ����
    ECT_REPEAT = 1,       // �ظ�����
    ECT_EXACT_REPEAT = 2, // ǰlimitColCount�ظ����ǣ�����ʣ��ľ�ȷ���� 
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
    int limitColCount;         // �����еĸ���
                               // �� ǰ limitColCount ������ÿ��1��"1"��������������
                               // һ������� limitColCount == colCount 
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

    void reset_size(int r, int c, int limitC = INF, eCoverType ect = ECT_EXACT) {
        rowCount = r;
        colCount = c;
        limitColCount = limitC != INF? limitC : c; 
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
                           
    void init(int r, int c, int limitC, eCoverType ect);
    void add(int rowIdx, int colIdx);       // index 0-based
    void output();
    bool dance(int depth, int startRow, int maxDepth);
    void preCoverRow(int rowIndex);

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
        // ��ʼ�����׽��
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

void DLX::init(int r, int c, int limitC, eCoverType ect) {
    reset_size(r, c, limitC, ect);
    reset_row();
    reset_col();
}

DLXNode* DLX::get_min_col() {
    DLXNode *resPtr = head->right;
    for(DLXNode *ptr = resPtr->right; ptr != head; ptr = ptr->right) {
        if(ptr->getColIdx() >= limitColCount)
            break;
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
        if(colIdx >= limitColCount)
            break;
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
        if (eCType == ECT_EXACT || eCType == ECT_EXACT_REPEAT && colPtr->getColIdx() >= limitColCount) {
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
        if (eCType == ECT_EXACT || eCType == ECT_EXACT_REPEAT && colPtr->getColIdx() >= limitColCount) {
            for(DLXNode* nodePtr = colPtr->up; nodePtr != colPtr; nodePtr = nodePtr->up) {
                uncoverRow(nodePtr);
            }
        }
        // �ָ�colPtrָ�����һ��
        colPtr->resumeFromCol();
    }
}

/*
    ���ܣ�����Ԥ��ѡ��ĳ�� 
*/
void DLX::preCoverRow(int rowIndex) {
    DLXNode *rowPtr = &row[rowIndex];
    for(DLXNode *p = rowPtr->right; p != rowPtr; p = p->right) {
        cover(p->getColHead());
    }
}

bool DLX::isEmpty() {
    if(head->right == head) {
        return true;
    }
    return head->right->getColIdx() >= limitColCount;
}

bool DLX::dance(int depth, int startRow, int maxDepth=INF) {
    // ��ǰ����Ϊ�գ�˵���ҵ�һ�����н⣬�㷨��ֹ 
    if(isEmpty()) {
        resultCount = depth;
        /*for(int i =0; i < depth; i++) {
            printf("%d ", result[i]);
        }*/
        return true;
    }
    if (maxDepth != INF) {
        if(depth + get_eval() > maxDepth) {
            return false;
        }
    }
    if(depth == maxDepth) return false;
    int i, r;
    // minPtrΪ��������ٵ��У�ö�����������е���
    DLXNode *minPtr = get_min_col();
    cover(minPtr);
    for(DLXNode *rowPtr = minPtr->down; rowPtr != minPtr; rowPtr = rowPtr->down) {
        // ��r = p->getRowIdx()����r���뵱ǰ��
        r = rowPtr->getRowIdx();
        result[depth] = r;
        DLXNode *p = &row[r];
        // ��r�ϵĽ���Ӧ���н���ɾ�� 
        for(DLXNode *q = p->right; q != p; q = q->right) {
            cover(q->getColHead());
        }
        // ��������������һ�� 
        if(dance(depth+1, r+((r&1)?1:2), maxDepth)) {
            return true;
        }
        // ��r�ϵĽ���Ӧ���н��лָ� 
        for(DLXNode *q = p->left; q != p; q = q->left) {
            uncover(q->getColHead());
        }
    }
    uncover(minPtr);
    return false;
}

struct RoleModel {
    int roleID, modelID;
    void read() {
        scanf("%d %d", &roleID, &modelID);
    }
};

struct Model {
    vector <RoleModel> beatList;
    void read() {
        int k;
        beatList.clear();
        scanf("%d", &k);
        while(k--) {
            RoleModel rm;
            rm.read();
            beatList.push_back(rm);
        }
    }
};

struct Role {
    int m;
    Model model[2];
    void read() {
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            model[i].read();
        }
    }
}R[MAXR/2];

int mat[MAXR][MAXC];

int construct_dlx(int n) {
    DLX &dlx = DLX::Instance();
    dlx.init(2*n, 2*n+n, 2*n, ECT_EXACT_REPEAT);
    int i, j;
    memset(mat, 0, sizeof(mat));
    for(i = 0; i < 2*n; ++i) {
        Model &mdl = R[i/2].model[i&1];
        if((i&1) < R[i/2].m) {
            for(j = 0; j < mdl.beatList.size(); ++j) {
                RoleModel &rm = mdl.beatList[j];
                mat[i][ rm.roleID<<1|rm.modelID ] = 1;
                if(R[rm.roleID].m == 1) {
                    mat[i][ rm.roleID<<1|1 ] = 1;
                }
            }
        }
        mat[i][2*n + (i/2)] = 1;

        // �Լ�һ���ܴ���Լ�
        mat[i][(i/2)*2] = mat[i][(i/2)*2+1] = 1;
    }
    for(i = 0; i < 2*n; ++i) {
        for(j = 0; j < 2*n+n; ++j) {
            if(mat[i][j]) dlx.add(i, j);
            //printf("%d", mat[i][j]);
        }
        //puts("");
    }
    for(i = 1; i < n; i++) {
        if(dlx.dance(0, 0, i))
            break;
    }
    return i;
}

int n;
int main() {
    int t, cases = 0;
    int i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            R[i].read();
        }
        printf("Case %d: %d\n", ++cases, construct_dlx(n));
    }
    return 0;
}
