//#include <iostream>
//using namespace std;
//const int N = 1e3 + 10;
//int f[N];
//int main()
//{
//    int n; cin >> n;
//    for (int i = 1; i <= n; i++) {
//        cin >> f[i];
//        f[i] += f[i - 1];
//    }
//    int x = 0x3f3f3f3f;
//    for (int i = 1; i < n; i++) {
//        if (abs(f[n] - f[i] - f[i]) < x) {
//            x = abs(f[n] - f[i] - f[i]);
//        }
//    }
//    cout << x << endl;
//    return 0;
//}


//#include <iostream>
//#include <string>
//using namespace std;
//string s;
//long long cnt;
//int main()
//{
//    for (int i = 1; i <= 1023; i++) {
//        s += to_string(i);
//    }
//    for (int i = 1; i <= s.size(); i++) {
//        for (int j = i + 1; j <= s.size(); j++) {
//            for (int k = j + 1; k <= s.size(); k++) {
//                for (int l = k + 1; l <= s.size(); l++) {
//                    string s_tmp = "" + s[i] + s[j] + s[k] + s[l];
//                    if (s_tmp == "2023") {
//                        cnt++;
//                    }
//                }
//            }
//        }
//    }
//    cout << cnt;
//    return 0;
//}



//#include <iostream>
//#include <cmath>
//using namespace std;
//int main()
//{
//    for (double i = 1; i <= 23333333; i++) {
//        double n0 = i; double n1 = 23333333 - n0;
//        double n = 23333333;
//        double y1 = log2(n0 / n), y2 = log2(n1 / n);
//        double x1 = (n0 * n0) / n, x2 = (n0 * n0) / n;
//        if (fabs(-(x1 * y1 + x2 * y2) - 11625907.5798) < 0.1) {
//            printf("%lf", i);
//            break;
//        }
//    }
//    return 0;
//}


//#include <iostream>
//#include <vector>
//using namespace std;
//const int N = 1e2 + 10;
//vector<int> vi;
//bool st[N];
//int n;
//void dfs() {
//	if (vi.size() == n) {
//		for (auto e : vi) {
//			cout << e;
//		}
//		cout << endl;
//	}
//	for (int i = 1; i <= n; i++) {
//		if (st[i]) {
//			continue;
//		}
//		vi.push_back(i);
//		st[i] = true;
//		dfs();
//		st[i] = false;
//		vi.pop_back();
//	}
//}
//int main() {
//	cin >> n;
//	dfs();
//
//
//
//	return 0;
//}










//注意：排列问题不需要关注下一个是谁！！！

//#include <iostream>
//using namespace std;
//const int N = 15;
//int n;
//bool st[N];
//int t[N], d[N], l[N];
//bool dfs(int pos, int end) {
//    if (pos > n) {
//        return true;
//    }
//    for (int i = 1; i <= n; i++) {
//        if (st[i]) continue;
//        if (end > t[i] + d[i]) continue;
//        int newend = max(t[i], end) + l[i];
//        st[i] = true;
//        if (dfs(pos + 1, newend)) {
//            return true;
//        }
//        st[i] = false;
//    }
//    return false;
//    //if (cnt == n) {
//    //    return true;
//    //}
//    //if (end > t[num] + d[num]) {
//    //    return false;
//    //}
//    //st[num] = true;
//    //int newend = max(t[num], end) + l[num];
//    //cnt++;
//    //for (int i = 1; i <= n; i++) {
//    //    if (st[i]) continue;
//    //    if (dfs(i + 1, newend)) {
//    //        return true;
//    //    }
//    //}
//    //cnt--;
//    //st[num] = false;
//}
//int main()
//{
//    int T; cin >> T;
//    while (T--) {
//        cin >> n;
//        for (int i = 1; i <= n; i++) {
//            cin >> t[i] >> d[i] >> l[i];
//        }
//        if (dfs(1, 0)) {
//            cout << "YES" << endl;
//        }
//        else {
//            cout << "NO" << endl;
//        }
//    }
//    return 0;
//}

//排列问题与下一个是谁无关！！
//当下情况在不在循环里面是取决于处理的是一组分支！！！



//在递归树上，节点的处理是整体的，也就是要在循环外面处理
//而在边上的问题是要在循环里面处理的
//排列问题关键需要知道下一个是哪一个位置
//组合问题则需要知道下一个从谁开始以及下一个是哪个位置
//剪枝需要的东西可以从传参得来

//#include <iostream>
//#include <vector>
//#include <set>
//using namespace std;
//const int N = 1e5 + 10;
//vector<int> edges1[N];//树n的边
//vector<int> edges2[N];//树m的边
//int vi_treenode1[N];//树n的节点权值
//int vi_treenode2[N];//树m的节点权值
//bool a[N];//标记树的i已经访问过了
//vector<int> vi;//临时存储某一条数列
//set<vector<int>> path_set;//存储n树上的所有最长序列
//void func1(int root) {
//    vi.push_back(vi_treenode1[root]);
//    a[root] = true;
//    if (edges1[root].empty())
//    {
//        path_set.insert(vi);
//        return;
//    }
//    for (auto e : edges1[root]) {
//        if (!a[e]) {
//            func1(e);
//        }
//    }
//    a[root] = false;
//    vi.pop_back();
//}
//int main()
//{
//    int n, m; cin >> n >> m;
//    for (int i = 1; i <= n; i++) {
//        cin >> vi_treenode1[i];
//    }
//    for (int i = 1; i <= m; i++) {
//        cin >> vi_treenode2[i];
//
//    }
//    for (int i = 1; i < n; i++) {
//        int x, y; cin >> x >> y;
//        edges1[x].push_back(y);
//        edges1[y].push_back(x);
//    }
//    for (int i = 1; i < m; i++) {
//        int x, y; cin >> x >> y;
//        edges2[x].push_back(y);
//        edges2[y].push_back(x);
//    }
//    func1(1);
//    for (auto e : path_set) {
//        for (auto x : e) {
//            cout << x << ' ';
//        }
//        cout << endl;
//    }
//    return 0;
//}



//#include <iostream>
//#include <vector>
//#include <cstring>
//#include <set>
//#include <string>
//using namespace std;
//const int N = 1e5 + 10;
//vector<int> edges1[N];//树n的边
//vector<int> edges2[N];//树m的边
//int vi_treenode1[N];//树n的节点权值
//int vi_treenode2[N];//树m的节点权值
//bool a[N];//标记树的i已经访问过了
//vector<int> vi;//临时存储某一条数列
//set<string> path_set;//存储n树上的所有最长序列
//long long ret;
//string tostring(vector<int>& vi) {
//    string sret;
//    for (auto e : vi) {
//        sret += to_string(e);
//    }
//    return sret;
//}
//void func1(int root) {
//    vi.push_back(vi_treenode1[root]);
//    a[root] = true;
//    bool is_leaf = true;
//    for (auto e : edges1[root]) {
//        if (!a[e]) {
//            is_leaf = false;
//            func1(e);
//        }
//    }
//    string s = tostring(vi);
//    path_set.insert(s);
//    a[root] = false;
//    vi.pop_back();
//}
//
//void func2(int root) {
//    vi.push_back(vi_treenode2[root]);
//    a[root] = true;
//    bool is_leaf = true;
//    for (auto e : edges2[root]) {
//        if (!a[e]) {
//            is_leaf = false;
//            func2(e);
//        }
//    }
//    string s = tostring(vi);
//    if (path_set.count(s)) {
//        long long size = vi.size();
//        ret = max(ret, size);
//    }
//    a[root] = false;
//    vi.pop_back();
//}
//// void dfs(int root){
////   cout << vi_treenode1[root] << ' ';
////   a[root] = true;
////   for(auto e : edges1[root]){
////     if(!a[e]){
////       dfs(e);
////     }
////   }
//// }
//int main()
//{
//    int n, m; cin >> n >> m;
//    for (int i = 1; i <= n; i++) {
//        cin >> vi_treenode1[i];
//    }
//    for (int i = 1; i <= m; i++) {
//        cin >> vi_treenode2[i];
//
//    }
//    for (int i = 1; i < n; i++) {
//        int x, y; cin >> x >> y;
//        edges1[x].push_back(y);
//        edges1[y].push_back(x);
//    }
//    for (int i = 1; i < m; i++) {
//        int x, y; cin >> x >> y;
//        edges2[x].push_back(y);
//        edges2[y].push_back(x);
//    }
//    func1(1);
//    memset(a, false, sizeof(a));
//
//    func2(1);
//
//    cout << ret << endl;
//    // for(auto e : path_set){
//    //   for(auto x : e){
//    //     cout << x << ' ';
//    //   }
//    //   cout << endl;
//    // }
//    // dfs(1);
//    return 0;
//}


// #include <iostream>
// using namespace std;
// const int N = 10;
// int row[N], col[N], d1, d2;
// int ret;
// int cnt;
// void dfs(int x, int y){
//   if(cnt > 13){
//     return;
//   }
//   if(y > 5){
//     x++;
//     y = 1;
//   }
//   if(x > 5){
//     if(cnt == 13){
//       for(int i = 1; i <= 5; i++){
//         if(row[i] == 5 || row[i] == 0 || col[i] == 5 || col[i] == 0){
//           return;
//         }
//       }
//       if(d1 == 5 || d1 == 0 || d2 == 5 || d2 == 0){
//         return;
//       }
//       ret++;
//     }
//     return;
//   }

//   //填
//   row[x]++;
//   col[y]++;
//   if(x == y) d1++;
//   if(x + y == 6) d2++;
//   cnt++;
//   dfs(x, y + 1);
//   cnt--;
//   row[x]--;
//   col[y]--;
//   if(x == y) d1--;
//   if(x + y == 6) d2--;

//   //不填
//   dfs(x, y + 1);
// }
// int main()
// {
//   dfs(1, 1);
//   cout << ret;
//   return 0;
// }

#include <iostream>
using namespace std;
int main() {



	cout << 3126376;
	return 0;
}