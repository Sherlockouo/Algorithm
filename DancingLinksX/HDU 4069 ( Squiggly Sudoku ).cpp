#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

#define SDK_CNT 3
#define SDK_MAX (SDK_CNT*SDK_CNT)
#define SDK_BLOCK (SDK_MAX*SDK_MAX)

#define MAXR (SDK_BLOCK*SDK_MAX+10)   
#define MAXC (SDK_BLOCK*4+10)
#define INF -1
#define INT64 __int64 

enum eCoverType {
    ECT_EXACT = 0,       // ��ȷ����
    ECT_REPEAT = 1,      // �ظ�����
};

enum eDanceType {
    EDT_GET_ONE_SOLUTION = 0,    // ��ȡһ����
    EDT_JUDGE_MULTIPLE = 1,      // �ж��Ƿ�����
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
    eDanceType eDType;
    int  *col_coverd;          // ��ǵ�i���Ƿ񸲸ǣ������ظ�����
    INT64 *row_code;           // ÿ�в��ö����Ʊ�ǽ����Ż�
    int limitColCount;         // �����еĸ���
                               // �� ǰ limitColCount ������ÿ��1��"1"��������������
                               // һ������� limitColCount == colCount 
public: 
    int *result, resultCount;  // �������
    int solutionCount;         // ������
    
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

    void reset_size(int r, int c, int limitC = INF, eCoverType ect = ECT_EXACT, eDanceType edt = EDT_GET_ONE_SOLUTION) {
        rowCount = r;
        colCount = c;
        limitColCount = limitC != INF? limitC : c; 
        eCType = ect;
        eDType = edt;
        dlx_pool_idx = 0;
        resultCount = -1;
        solutionCount = 0;
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
                           
    void init(int r, int c, int limitC, eCoverType ect, eDanceType edt);
    void add(int rowIdx, int colIdx);       // index 0-based
    void output();
    bool dance(int depth, int maxDepth);
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

void DLX::init(int r, int c, int limitC, eCoverType ect, eDanceType edt) {
    reset_size(r, c, limitC, ect, edt);
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

bool DLX::dance(int depth, int maxDepth=INF) {
    // ��ǰ����Ϊ�գ�˵���ҵ�һ�����н⣬�㷨��ֹ 
    if(isEmpty()) {
        resultCount = depth;
        if(eDType == EDT_GET_ONE_SOLUTION) {
            return true;
        }
        solutionCount ++;
        return solutionCount > 1;
    }
    if (maxDepth != INF) {
        if(depth + get_eval() > maxDepth) {
            return false;
        }
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

class Sudoku {
    int sdkMatrix[SDK_MAX][SDK_MAX];     //Sudoku���� ���ַ�ΧΪ[1��SDK_MAX], û��������ּ�Ϊ0 
    int sdkCnt, sdkMax, sdkBlock;        // sdkMax = sdkCnt^2, sdkBlock = sdkMax^2

    struct DLXRow {
        int sudokuNum;
        int sudokuRow, sudokuCol;
    
        DLXRow() {}
        DLXRow(int r, int c, int num): sudokuRow(r), sudokuCol(c), sudokuNum(num) {}
    }*dlxRow;
    int dlxRowCount;
    
    int getRegionIndex(int r, int c);    
    void assignSize(int n);
    void fillSDKMatrix(char sdkTemp[SDK_MAX][SDK_MAX+1]);
    void createDancingLincks(eDanceType edt);
    void startDance();

public:
    Sudoku() {
        dlxRow = new DLXRow[MAXR];
    }
    ~Sudoku() {
        delete [] dlxRow;
    }
    void outputSDKMatrix();
    void startSolveSudoku(int n, eDanceType edt, char sdkTemp[SDK_MAX][SDK_MAX+1]);

    static Sudoku& Instance() {
        static Sudoku inst;
        return inst;
    }
};

void Sudoku::assignSize(int n) {
    sdkCnt = n;
    sdkMax = sdkCnt * sdkCnt;
    sdkBlock = sdkMax * sdkMax;
}

void Sudoku::fillSDKMatrix(char sdkTemp[SDK_MAX][SDK_MAX+1]) {
    int i, j;
    for(i = 0; i < sdkMax; ++i) {
        for(j = 0; j < sdkMax; ++j) {
            int num = 0;
            if('A' <= sdkTemp[i][j] && sdkTemp[i][j] <= 'G') {
                num = (sdkTemp[i][j] - 'A' + 10);
            }else if('1' <= sdkTemp[i][j] && sdkTemp[i][j] <= '9') {
                num = (sdkTemp[i][j] - '0');
            }
            sdkMatrix[i][j] = num;
        }
    }
}

void Sudoku::createDancingLincks(eDanceType edt) {
    DLX &dlx = DLX::Instance();
    dlx.init(MAXR-1, sdkBlock*4, INF, ECT_EXACT, edt);
    dlxRowCount = 0;
    int i, j, k;
    for(i = 0; i < sdkMax; ++i) {
        for(j = 0; j < sdkMax; ++j) {
            for(k = 1; k <= sdkMax; ++k) {
                if(sdkMatrix[i][j] && sdkMatrix[i][j] != k) {
                    continue;
                }
                // �������ƣ�ÿ��һ����
                dlx.add(dlxRowCount, i*sdkMax+j);
                // �����ƣ�ÿ��ֻ��һ��k
                dlx.add(dlxRowCount, sdkBlock + i*sdkMax + (k-1));
                // �����ƣ�ÿ��ֻ��һ��k
                dlx.add(dlxRowCount, 2*sdkBlock + j*sdkMax + (k-1));
                // �����ƣ�ÿ��ֻ��һ��k
                dlx.add(dlxRowCount, 3*sdkBlock + getRegionIndex(i,j)*sdkMax + (k-1));
                dlxRow[dlxRowCount++] = DLXRow(i, j, k);
            }
        }
    }
    // �ܹ� dlxRowCount ��
}

void Sudoku::startDance() {
    DLX &dlx = DLX::Instance();
    dlx.dance(0, INF);
    int i;
    for(i = 0; i < dlx.resultCount; i++) {
        int &idx = dlx.result[i];
        sdkMatrix[ dlxRow[idx].sudokuRow ][ dlxRow[idx].sudokuCol ] = dlxRow[idx].sudokuNum;
    }
}

void Sudoku::outputSDKMatrix() {
    int i, j;
    for(i = 0; i < sdkMax; ++i) {
        for(j = 0; j < sdkMax; ++j) {
            char c;
            if(1 <= sdkMatrix[i][j] && sdkMatrix[i][j] <= 9) {
                c = sdkMatrix[i][j] + '0';
            }else {
                c = sdkMatrix[i][j] - 10 + 'A';
            }
            printf("%c", c);
        }
        puts("");
    }
}

void Sudoku::startSolveSudoku(int n, eDanceType edt, char sdkTemp[SDK_MAX][SDK_MAX+1]) {
    assignSize(n);
    fillSDKMatrix(sdkTemp);
    createDancingLincks(edt);
    startDance();
}

char sdkTemp[SDK_MAX][SDK_MAX+1];
int matCode[SDK_MAX][SDK_MAX];
int region[SDK_MAX][SDK_MAX], regionIdx;

int dir[4][2] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

int wall[4] = {
    16, 32, 64, 128
};

/* 
    (0, sdkMax-1)-(0, sdkMax-1)   =>     (0, sdkMax-1) ��ӳ��    
    �ѿ�������(r, c) �� "��" ��ӳ��
*/
int Sudoku::getRegionIndex(int r, int c) {
    return region[r][c];
}

void dfs(int r, int c, int regionIdx) {
    int i;
    for(i = 0; i < 4; ++i) {
        int tr = r + dir[i][0];
        int tc = c + dir[i][1];
        if(matCode[r][c] & wall[i]) {
            continue;
        }
        if(tr < 0 || tc < 0 || tr >= SDK_MAX || tc >= SDK_MAX) {
            continue;
        }
        if(region[tr][tc] == -1) {
            region[tr][tc] = regionIdx;
            dfs(tr, tc, regionIdx);
        }
    }
}

int main() {
    int i, j;
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < SDK_MAX; ++i) {
            for(j = 0; j < SDK_MAX; ++j) {
                scanf("%d", &matCode[i][j]);
            }
        }
        memset(region, -1, sizeof(region));
        regionIdx = 0;
        for(i = 0; i < SDK_MAX; ++i) {
            for(j = 0; j < SDK_MAX; ++j) {
                sdkTemp[i][j] = matCode[i][j] % wall[0] + '0';
                if(region[i][j] == -1) {
                    region[i][j] = regionIdx;
                    dfs(i, j, regionIdx);
                    ++regionIdx;
                }
            }
            sdkTemp[i][SDK_MAX] = '\0';
        }

        /*for(i = 0; i < SDK_MAX; i++) puts(sdkTemp[i]);
        for(i = 0; i < SDK_MAX; ++i) {
            for(j = 0; j < SDK_MAX; ++j) {
                printf("%d", region[i][j]);
            }
            puts("");
        }*/
        printf("Case %d:\n", ++cases);
        Sudoku &sdk = Sudoku::Instance();
        sdk.startSolveSudoku(SDK_CNT, EDT_JUDGE_MULTIPLE, sdkTemp);
        DLX &dlx = DLX::Instance();
        if(dlx.solutionCount == 0) {
            puts("No solution");
        }else if(dlx.solutionCount > 1) {
            puts("Multiple Solutions");
        }else {
            sdk.startSolveSudoku(SDK_CNT, EDT_GET_ONE_SOLUTION, sdkTemp);
            sdk.outputSDKMatrix();
        }
    }
    return 0;
}
