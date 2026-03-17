//class Solution {
//public:
//    bool canPartition(vector<int>& nums) {
//        memset(dp, false, sizeof(dp));
//        int n = nums.size();
//        int sum = 0;
//        for (int e : nums) {
//            sum += e;
//        }
//        if (sum % 2 != 0) {
//            return false;
//        }
//        for (int i = 0; i < n; i++) {
//            dp[i][0] = true;
//        }
//        for (int i = 1; i < n; i++) {
//            for (int j = 1; j < sum; j++) {
//                dp[i][j] = dp[i - 1][j];
//                if (j >= nums[i]) {
//                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i]];
//                }
//            }
//        }
//        return dp[n - 1][sum / 2];
//    }
//    bool dp[210][20010];
//};

//class Solution {
//public:
//    bool canPartition(vector<int>& nums) {
//        memset(dp, false, sizeof(dp));
//        int n = nums.size();
//        int sum = 0;
//        for (int e : nums) {
//            sum += e;
//        }
//        if (sum % 2 != 0) {
//            return false;
//        }
//        dp[0] = true;
//        for (int i = 1; i < n; i++) {
//            for (int j = sum / 2; j >= nums[i]; j--) {
//                dp[j] = dp[j] || dp[j - nums[i]];
//            }
//        }
//        return dp[sum / 2];
//    }
//    bool dp[20010];
//};


//class Solution {
//public:
//    int lastStoneWeightII(vector<int>& stones) {
//        memset(dp, false, sizeof(dp));
//        int n = stones.size();
//        for (int i = 0; i < n; i++) {
//            dp[i][0] = true;
//        }
//        int sum = 0;
//        for (int w : stones) {
//            sum += w;
//        }
//        for (int i = 1; i < n; i++) {
//            for (int j = 1; j <= sum; j++) {
//                dp[i][j] = dp[i - 1][j];
//                if (j - stones[i] >= 0) {
//                    dp[i][j] = dp[i][j] || dp[i - 1][j - stones[i]];
//                }
//            }
//        }
//        int ret = 0x3f3f3f3f;
//        for (int i = 0; i < sum; i++) {
//            if (dp[n - 1][i]) {
//                ret = min(ret, abs(i - (sum - i)));
//            }
//        }
//        return ret == 0x3f3f3f3f ? 0 : ret;
//    }
//    bool dp[35][3010];
//};

//class Solution {
//public:
//    int findMaxForm(vector<string>& strs, int m, int n) {
//        strs.insert(strs.begin(), "");
//        for (int i = 1; i < strs.size(); i++) {
//            for (int j = 0; j <= m; j++) {//0
//                for (int k = 0; k <= n; k++) {
//                    dp[i][j][k] = dp[i - 1][j][k];
//                    int cnt_0 = 0, cnt_1 = 0;
//                    for (auto ch : strs[i]) {
//                        ch == '1' ? cnt_1++ : cnt_0++;
//                    }
//                    if (j - cnt_0 >= 0 && k - cnt_1 >= 0) {
//                        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - cnt_0][k - cnt_1] + 1);
//                    }
//                }
//            }
//        }
//        return dp[strs.size() - 1][m][n];
//    }
//    int dp[610][110][110];
//};

//class Solution {
//public:
//    void dfs(int start) {
//        if (path.size() > 1) {
//            if (sv.count(path) == 0) {
//                ret.push_back(path);
//                sv.insert(path);
//            }
//
//        }
//        for (int i = start; i < nums.size(); i++) {
//            if (path.size() && nums[i] < path.back()) {
//                continue;
//            }
//            path.push_back(nums[i]);
//            dfs(i + 1);
//            path.pop_back();
//        }
//    }
//    vector<vector<int>> findSubsequences(vector<int>& nums) {
//        this->nums = nums;
//        dfs(0);
//        return ret;
//    }
//    vector<vector<int>> ret;
//    vector<int> path;
//    set<vector<int>> sv;
//    vector<int> nums;
//};

//class Solution {
//public:
//    int change(int amount, vector<int>& coins) {
//        coins.insert(coins.begin(), 0);
//        dp[0][0] = 1;
//        for (int i = 1; i < coins.size(); i++) {
//            for (int j = 0; j <= amount; j++) {
//                dp[i][j] += dp[i - 1][j];
//                for (int k = 1; j - k * coins[i] >= 0; k++) {
//                    dp[i][j] += dp[i - 1][j - k * coins[i]];
//                }
//            }
//        }
//        return dp[coins.size() - 1][amount];
//    }
//    typedef unsigned long long LL;
//    LL dp[310][5010];
//};