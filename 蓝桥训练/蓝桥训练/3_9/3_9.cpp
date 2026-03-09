class Solution {
public:
    void func(int x) {
        //递归出口
        if (x > n) {
            vs.push_back(v);
            return;
        }
        for (int i = 0; i < n; i++) {
            if (!col[i] && !st1[x - i + n] && !st2[x + i]) {
                string s(n, '.');
                s[i] = 'Q';
                col[i] = st1[x - i + n] = st2[x + i] = true;
                v.push_back(s);
                func(x + 1);
                v.pop_back();
                col[i] = st1[x - i + n] = st2[x + i] = false;
            }
        }

    }
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        func(1);
        return vs;
    }
    int n;
    int col[30];
    int st1[60];//主对角线
    int st2[60];//副对角线
    vector<vector<string>> vs;
    vector<string> v;
};








class Solution {
public:
    //对于移动问题我们可以通过递归调用来实现
    bool func(int i, int j) {
        if (i == 9) {
            return true;
        }
        if (j == 9) {
            return func(i + 1, 0);
        }
        if (board[i][j] != '.') {
            return func(i, j + 1);
        }

        for (char ch = '1'; ch <= '9'; ch++) {
            int num = ch - '0';
            if (row[i][num] || col[j][num] || st[i / 3][j / 3][num]) {
                continue;
            }
            row[i][num] = col[j][num] = st[i / 3][j / 3][num] = true;
            board[i][j] = ch;
            if (func(i, j + 1)) {
                return true;
            }
            board[i][j] = '.';
            row[i][num] = col[j][num] = st[i / 3][j / 3][num] = false;
        }
        return false;
    }
    void solveSudoku(vector<vector<char>>& board) {
        memset(row, false, sizeof(row));
        memset(col, false, sizeof(col));
        memset(st, false, sizeof(st));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char ch = board[i][j];
                if (ch != '.') {
                    int num = ch - '0';
                    row[i][num] = col[j][num] = st[i / 3][j / 3][num] = true;
                }
            }
        }
        this->board = board;
        func(0, 0);
        board = this->board;
        return;
    }
    bool row[10][10], col[10][10], st[3][3][10];
    vector<vector<char>> board;
};