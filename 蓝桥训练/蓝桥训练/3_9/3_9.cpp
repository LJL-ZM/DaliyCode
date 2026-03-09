//class Solution {
//public:
//    void func(int x) {
//        //递归出口
//        if (x > n) {
//            vs.push_back(v);
//            return;
//        }
//        for (int i = 0; i < n; i++) {
//            if (!col[i] && !st1[x - i + n] && !st2[x + i]) {
//                string s(n, '.');
//                s[i] = 'Q';
//                col[i] = st1[x - i + n] = st2[x + i] = true;
//                v.push_back(s);
//                func(x + 1);
//                v.pop_back();
//                col[i] = st1[x - i + n] = st2[x + i] = false;
//            }
//        }
//
//    }
//    vector<vector<string>> solveNQueens(int n) {
//        this->n = n;
//        func(1);
//        return vs;
//    }
//    int n;
//    int col[30];
//    int st1[60];//主对角线
//    int st2[60];//副对角线
//    vector<vector<string>> vs;
//    vector<string> v;
//};
//
//
//
//
//
//
//
//
//class Solution {
//public:
//    //对于移动问题我们可以通过递归调用来实现
//    bool func(int i, int j) {
//        if (i == 9) {
//            return true;
//        }
//        if (j == 9) {
//            return func(i + 1, 0);
//        }
//        if (board[i][j] != '.') {
//            return func(i, j + 1);
//        }
//
//        for (char ch = '1'; ch <= '9'; ch++) {
//            int num = ch - '0';
//            if (row[i][num] || col[j][num] || st[i / 3][j / 3][num]) {
//                continue;
//            }
//            row[i][num] = col[j][num] = st[i / 3][j / 3][num] = true;
//            board[i][j] = ch;
//            if (func(i, j + 1)) {
//                return true;
//            }
//            board[i][j] = '.';
//            row[i][num] = col[j][num] = st[i / 3][j / 3][num] = false;
//        }
//        return false;
//    }
//    void solveSudoku(vector<vector<char>>& board) {
//        memset(row, false, sizeof(row));
//        memset(col, false, sizeof(col));
//        memset(st, false, sizeof(st));
//        for (int i = 0; i < 9; i++) {
//            for (int j = 0; j < 9; j++) {
//                char ch = board[i][j];
//                if (ch != '.') {
//                    int num = ch - '0';
//                    row[i][num] = col[j][num] = st[i / 3][j / 3][num] = true;
//                }
//            }
//        }
//        this->board = board;
//        func(0, 0);
//        board = this->board;
//        return;
//    }
//    bool row[10][10], col[10][10], st[3][3][10];
//    vector<vector<char>> board;
//};



//#include <iostream>
//using namespace std;
//const int N = 6;
//int row[N], col[N], st1, st2;//行、列、主、副
//int w;
//int ret;
//void dfs(int x, int y) {
//	if (y > 5) {
//		x++;
//		y = 1;
//	}
//	if (x > 5) {
//		for (int i = 1; i <= 5; i++) {
//			if (row[i] == 5 || col[i] == 5 || row[i] == 0 || col[i] == 0) {
//				return;
//			}
//		}
//		if (st1 == 5 || st2 == 5 || st1 == 0 || st2 == 0) {
//			return;
//		}
//		if (w != 13) {
//			return;
//		}
//		ret++;
//		return;
//	}
//	//当前位置放白子
//	w++;
//	row[x]++, col[y]++;
//	if (x == y) {
//		st1++;
//	}
//	if (x + y == 6) {
//		st2++;
//	}
//	dfs(x, y + 1);
//	row[x]--, col[y]--;
//	if (x == y) {
//		st1--;
//	}
//	if (x + y == 6) {
//		st2--;
//	}
//	//当前位置不放
//	w--;
//	dfs(x, y + 1);
//	return;
//}
//int main() {
//	dfs(1, 1);
//	cout << ret << endl;
//
//
//	return 0;
//}








//#include <iostream>
//using namespace std;
//long long ret;
//void dfs(int a, int b, int pos) {
//	if (pos > 7) {
//		if (a == 0 && b == 0) {
//			ret++;
//		}
//		return;
//	}
//	for (int i = 0; i <= 5; i++) {
//		int j = 2 - i >= 0 ? 2 - i : 0;
//		int ex = 5 - i;
//		for (; j <= ex; j++) {
//			if (a - i >= 0 && b - j >= 0) {
//				dfs(a - i, b - j, pos + 1);
//			}
//		}
//	}
//}
//int main() {
//	dfs(9, 16, 1);
//	cout << ret << endl;
//
//
//
//	return 0;
//}


//#include <iostream>
//using namespace std;
//const int N = 7;
//int a[N][N];
//int row[N], col[N];
//
//bool is_valid() {
//	for (int i = 1; i <= 6; i++) {
//		if (a[i][1] == a[i][2] && a[i][2] == a[i][3]) {
//			return false;
//		}
//		if (a[i][3] == a[i][2] && a[i][4] == a[i][3]) {
//			return false;
//		}
//		if (a[i][3] == a[i][4] && a[i][4] == a[i][5]) {
//			return false;
//		}
//		if (a[i][4] == a[i][5] && a[i][5] == a[i][6]) {
//			return false;
//		}
//	}
//	//列相邻
//	for (int j = 1; j <= 6; j++) {
//		if (a[1][j] == a[2][j] && a[2][j] == a[3][j]) {
//			return false;
//		}
//		if (a[2][j] == a[3][j] && a[4][j] == a[3][j]) {
//			return false;
//		}
//		if (a[3][j] == a[4][j] && a[4][j] == a[5][j]) {
//			return false;
//		}
//		if (a[4][j] == a[5][j] && a[5][j] == a[6][j]) {
//			return false;
//		}
//	}
//	//行唯一
//	for (int i = 1; i <= 6; i++) {
//		for (int j = i + 1; j <= 6; j++) {
//			int flag = 0;
//			for (int k = 1; k <= 6; k++) {
//				if (a[i][k] != a[j][k]) {
//					flag = 1;
//					break;
//				}
//			}
//			if (flag == 0) {
//				return false;
//			}
//		}
//	}
//	for (int i = 1; i <= 6; i++) {
//		for (int j = i + 1; j <= 6; j++) {
//			int flag = 0;
//			for (int k = 1; k <= 6; k++) {
//				if (a[k][i] != a[k][j]) {
//					flag = 1;
//					break;
//				}
//			}
//			if (flag == 0) {
//				return false;
//			}
//		}
//	}
//	for (int i = 1; i <= 6; i++) {
//		if (row[i] != 3 || col[i] != 3) {
//			return false;
//		}
//	}
//	return true;
//}
//bool dfs(int x, int y) {
//	if (y > 6) {
//		return dfs(x + 1, 1);
//	}
//	if (x > 6) {
//		//记录结果
//		//行相邻
//		for (int i = 1; i <= 6; i++) {
//			if (a[i][1] == a[i][2] && a[i][2] == a[i][3]) {
//				return false;
//			}
//			if (a[i][3] == a[i][2] && a[i][4] == a[i][3]) {
//				return false;
//			}
//			if (a[i][3] == a[i][4] && a[i][4] == a[i][5]) {
//				return false;
//			}
//			if (a[i][4] == a[i][5] && a[i][5] == a[i][6]) {
//				return false;
//			}
//		}
//		//列相邻
//		for (int j = 1; j <= 6; j++) {
//			if (a[1][j] == a[2][j] && a[2][j] == a[3][j]) {
//				return false;
//			}
//			if (a[2][j] == a[3][j] && a[4][j] == a[3][j]) {
//				return false;
//			}
//			if (a[3][j] == a[4][j] && a[4][j] == a[5][j]) {
//				return false;
//			}
//			if (a[4][j] == a[5][j] && a[5][j] == a[6][j]) {
//				return false;
//			}
//		}
//		//行唯一
//		for (int i = 1; i <= 6; i++) {
//			for (int j = i + 1; j <= 6; j++) {
//				int flag = 0;
//				for (int k = 1; k <= 6; k++) {
//					if (a[i][k] != a[j][k]) {
//						flag = 1;
//						break;
//					}
//				}
//				if (flag == 0) {
//					return false;
//				}
//			}
//		}
//		for (int i = 1; i <= 6; i++) {
//			for (int j = i + 1; j <= 6; j++) {
//				int flag = 0;
//				for (int k = 1; k <= 6; k++) {
//					if (a[k][i] != a[k][j]) {
//						flag = 1;
//						break;
//					}
//				}
//				if (flag == 0) {
//					return false;
//				}
//			}
//		}
//		for (int i = 1; i <= 6; i++) {
//			if (row[i] != 3 || col[i] != 3) {
//				return false;
//			}
//		}
//		return true;
//	}
//	if (a[x][y] == 1) {
//		return dfs(x, y + 1);
//	}
//	//填黑棋
//	if (!is_valid()) {
//		row[x]++;
//		col[y]++;
//		if (dfs(x, y + 1)) {
//			return true;
//		}
//	}
//	//不填
//	row[x]--;
//	col[y]--;
//	return dfs(x, y + 1);
//}
//int main() {
//	a[1][1] = a[5][3] = a[5][6] = a[6][5] = 1;
//	row[1] = 1;
//	row[5] = 2;
//	row[6] = 1;
//	col[1] = 1;
//	col[3] = 1;
//	col[5] = 1;
//	col[6] = 1;
//	dfs(1, 1);
//	for (int i = 1; i <= 6; i++) {
//		for (int j = 1; j <= 6; j++) {
//			cout << a[i][j];
//		}
//	}
//
//
//
//
//	return 0;
//}
//
//
//


//#include <iostream>
//#include <queue>
//#include <cstring>
//using namespace std;
//const int N = 110;
//int a[N];
//int n;
//int f[N];
//
//void bfs() {
//	queue<int> q;
//	f[1] = 0;
//	q.push(1);
//	while (q.size()) {
//		int pos = q.front(); q.pop();
//		for (int i = 1; i <= a[pos]; i++) {
//			if (pos + i > n || f[pos + i] != -1) {
//				continue;
//			}
//			f[pos + i] = f[pos] + 1;
//			if (pos + i == n) {
//				return;
//			}
//			q.push(pos + i);
//		}
//	}
//}
//int main() {
//	memset(f, -1, sizeof(f));
//	cin >> n;
//	for (int i = 1; i <= n; i++) {
//		cin >> a[i];
//	}
//	bfs();
//	cout << f[n] << endl;
//
//
//	return 0;
//}












//#include <iostream>
//using namespace std;
//int dx[] = {-1, 1, 0, 0};
//int dy[] = { 0, 0, 1, -1 };
//const int N = 510;
//char a[N][N];
//bool f[N][N];
//int n, m;
//int ret;
//void dfs(int x, int y) {
//	f[x][y] = true;
//	for (int k = 0; k < 4; k++) {
//		int newx = x + dx[k], newy = y + dy[k];
//		if (newx < 1 || newx > n || newy < 1 || newy > m || a[newx][newy] == 'X' || f[newx][newy]) {
//			continue;
//		}
//		dfs(newx, newy);
//	}
//}
//
//int main() {
//	cin >> n >> m;
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= m; j++) {
//			cin >> a[i][j];
//		}
//	}
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= m; j++) {
//			if (f[i][j] == false && a[i][j] == 'R') {
//				ret++;
//				dfs(i, j);
//			}
//		}
//	}
//	cout << ret << endl;
//
//	return 0;
//}