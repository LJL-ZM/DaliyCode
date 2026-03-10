//class Solution {
//    typedef pair<int, int> PII;
//public:
//    Solution() {
//        cnt_1 = cnt_2 = cnt_0 = 0;
//        dx[0] = 1, dx[1] = -1, dx[2] = 0, dx[3] = 0;
//        dy[0] = 0, dy[1] = 0, dy[2] = 1, dy[3] = -1;
//    }
//    void bfs() {
//        queue<PII> q;
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < m; j++) {
//                if (grid[i][j] == 2) {
//                    q.push({ i, j });
//                    f[i][j] = 0;
//                }
//            }
//        }
//        while (q.size()) {
//            int x = q.front().first, y = q.front().second;
//            q.pop();
//            for (int k = 0; k < 4; k++) {
//                int newx = x + dx[k], newy = y + dy[k];
//                if (newx < 0 || newx >= n || newy < 0 || newy >= m || f[newx][newy] != -1 || grid[newx][newy] != 1) {
//                    continue;
//                }
//                f[newx][newy] = f[x][y] + 1;
//                q.push({ newx, newy });
//            }
//        }
//    }
//
//    int orangesRotting(vector<vector<int>>& grid) {
//        this->grid = grid;
//        n = grid.size();
//        m = grid[0].size();
//        memset(f, -1, sizeof(f));
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < m; j++) {
//                int num = grid[i][j];
//                if (num == 0) {
//                    cnt_0++;
//                }
//                else if (num == 1) {
//                    cnt_1++;
//                }
//                else {
//                    cnt_2++;
//                }
//            }
//        }
//        bfs();
//        if (cnt_1 > 0 && cnt_2 == 0) {
//            return -1;
//        }
//        if (cnt_1 == 0 && cnt_2 == 0 && cnt_0 > 0) {
//            return 0;
//        }
//        if (cnt_1 == 0 && cnt_2 > 0) {
//            return 0;
//        }
//        bool flag = 0;
//        int _max = -1;
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < m; j++) {
//                if (grid[i][j] == 1 && f[i][j] == -1) {
//                    flag = 1;
//                }
//                _max = max(f[i][j], _max);
//            }
//        }
//        if (flag) {
//            return -1;
//        }
//        return _max;
//    }
//    int n, m;
//    int ret;
//    int f[11][11];
//    int dx[4], dy[4];
//    vector<vector<int>> grid;
//    int cnt_1 = 0;
//    int cnt_2 = 0;
//    int cnt_0 = 0;
//};




// // class Solution {
// //     typedef long long LL;
// // public:
// //     bool check(string s1, string s2){
// //         return s1[0] == s2[0];
// //     }
// //     int biFind(string s){
// //         LL l = 0, r = products.size();
// //         while(l  < r){
// //             LL mid = (l + r) / 2;
// //             if(products[mid] >= s){
// //                 r = mid;
// //             }
// //             else{
// //                 l = mid + 1;
// //             }
// //         }
// //         return l;
// //     }
// //     vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
// //         this->products = products;
// //         sort(products.begin(), products.end());
// //         string s = "";
// //         for(auto e : searchWord){
// //             s += e;
// //             int pos = biFind(s);
// //             int n = 0;
// //             vector<string> vs;
// //             while(n < 3){
// //                 if(pos + n < products.size() && check(s, products[pos + n])){
// //                     vs.push_back(products[pos + n]);
// //                 }
// //                 else{
// //                     break;
// //                 }
// //             }
// //             vvs.push_back(vs);
// //         }
// //         return vvs;
// //     }
// //     vector<vector<string>> vvs;
// //     vector<string> products;
// // };






// class Solution {
//     typedef long long LL;
// public:
//     bool check(string s1, string s2){
//         return s1[0] == s2[0];
//     }
//     int biFind(string s){
//         LL l = 0, r = products.size();
//         while(l  < r){
//             LL mid = (l + r) / 2;
//             if(products[mid] >= s){
//                 r = mid;
//             }
//             else{
//                 l = mid + 1;
//             }
//         }
//         return l;
//     }
//     vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
//         this->products = products;
//         sort(products.begin(), products.end());
//         string s = "";
//         for(auto e : searchWord){
//             s += e;
//             int pos = biFind(s);
//             int n = 0;
//             vector<string> vs;
//             while(n < 3){
//                 if(pos + n < products.size() && check(s, products[pos + n])){
//                     vs.push_back(products[pos + n]);
//                 }
//                 else{
//                     break;
//                 }
//             }
//             vvs.push_back(vs);
//         }
//         return vvs;
//     }
//     vector<vector<string>> vvs;
//     vector<string> products;
// };






//#include <vector>
//#include <string>
//#include <algorithm>
//using namespace std;
//
//class Solution {
//    typedef long long LL;
//public:
//    // 修正 1：正确的前缀检查（核心逻辑）
//    bool check(string& prefix, string& product) {
//        // 产品长度必须 >= 前缀长度，否则不可能匹配
//        if (product.size() < prefix.size()) return false;
//        // 逐字符比较每一位
//        for (int i = 0; i < prefix.size(); i++) {
//            if (product[i] != prefix[i]) return false;
//        }
//        return true;
//    }
//
//    // 你的二分逻辑完全正确，保留
//    int biFind(string s, vector<string>& products) {
//        LL l = 0, r = products.size();
//        while (l < r) {
//            LL mid = (l + r) / 2;
//            if (products[mid] >= s) {
//                r = mid;
//            }
//            else {
//                l = mid + 1;
//            }
//        }
//        return l;
//    }
//
//    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
//        sort(products.begin(), products.end());
//        vector<vector<string>> result;
//        string currentPrefix = "";
//
//        for (char c : searchWord) {
//            currentPrefix += c;
//            int startPos = biFind(currentPrefix, products);
//            vector<string> matches;
//            int count = 0;
//
//            // 修正 3：这里必须 count++，否则会死循环
//            while (count < 3 && (startPos + count) < products.size()) {
//                string& p = products[startPos + count];
//                if (check(currentPrefix, p)) {
//                    matches.push_back(p);
//                }
//                else {
//                    // 优化：如果当前位置不匹配，后面的也不匹配，直接 break
//                    break;
//                }
//                count++;
//            }
//            result.push_back(matches);
//        }
//        return result;
//    }
//};


//class Solution {
//public:
//    void find(vector<string>& wordList, string& s, vector<string>& vs) {
//        for (string& list_s : wordList) {
//            if (list_s.size() != s.size()) {
//                continue;
//            }
//            int cnt = 0;
//            for (int i = 0; i < s.size(); i++) {
//                if (s[i] != list_s[i])
//                    cnt++;
//            }
//            if (cnt == 1) {
//                vs.push_back(list_s);
//            }
//        }
//    }
//    void bfs(string& beginWord, vector<string>& wordList) {
//        queue<string> q;
//        us[beginWord] = 1;
//        q.push(beginWord);
//        while (q.size()) {
//            string s = q.front(); q.pop();
//            vector<string> vs;
//            find(wordList, s, vs);
//            for (string& tmp : vs) {
//                if (!us.count(tmp)) {
//                    q.push(tmp);
//                    us[tmp] = us[s] + 1;
//                }
//            }
//        }
//    }
//    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
//        bfs(beginWord, wordList);
//        return us.count(endWord) ? us[endWord] : 0;
//    }
//    unordered_map<string, int> us;
//};