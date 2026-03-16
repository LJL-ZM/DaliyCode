//class Solution {
//public:
//    int minDistance(string word1, string word2) {
//        string s = " " + word1, t = " " + word2;
//        //初始化
//        int n = word1.size(), m = word2.size();
//        for (int i = 0; i <= n; i++) {
//            f[i][0] = i;
//        }
//        for (int j = 0; j <= m; j++) {
//            f[0][j] = j;
//        }
//        for (int i = 1; i <= n; i++) {
//            for (int j = 1; j <= m; j++) {
//                if (s[i] == t[j]) {
//                    f[i][j] = f[i - 1][j - 1];
//                }
//                else {
//                    f[i][j] = min(f[i - 1][j], f[i][j - 1]) + 1;
//                    f[i][j] = min(f[i - 1][j - 1] + 1, f[i][j]);
//                }
//            }
//        }
//        return f[n][m];
//    }
//    int f[550][550];
//};


//class Solution {
//public:
//    void dfs(int start, int target) {
//        if (target == 0) {
//            ret.push_back(path);
//            return;
//        }
//        for (int i = start; i < candidates.size(); i++) {
//            if (candidates[i] > target) {
//                break;
//            }
//            path.push_back(candidates[i]);
//            dfs(i, target - candidates[i]);
//            path.pop_back();
//        }
//    }
//    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
//        sort(candidates.begin(), candidates.end());
//        this->candidates = candidates;
//        dfs(0, target);
//        return ret;
//    }
//    vector<vector<int>> ret;
//    vector<int> path;
//    vector<int> candidates;
//};


//组合问题一定使用start优化
//排列问题使用数组标记路径