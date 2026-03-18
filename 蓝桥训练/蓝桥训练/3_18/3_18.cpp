//class Solution {
//public:
//    int coinChange(vector<int>& coins, int amount) {
//        if (coins.size() && amount == 0) {
//            return 0;
//        }
//        coins.insert(coins.begin(), 0);
//        memset(dp, 0x3f, sizeof(dp));
//        dp[0][0] = 0;
//        for (int i = 1; i < coins.size(); i++) {
//            for (int j = 0; j <= amount; j++) {
//                dp[i][j] = dp[i - 1][j];
//                for (int k = 1; j - coins[i] * k >= 0; k++) {
//                    dp[i][j] = min(dp[i][j], dp[i - 1][j - k * coins[i]] + k);
//                }
//            }
//        }
//        ULL tmp = 0;
//        memset(&tmp, 0x3f, sizeof(tmp));
//        return dp[coins.size() - 1][amount] == tmp ? -1 : dp[coins.size() - 1][amount];
//    }
//    typedef unsigned long long ULL;
//    ULL dp[15][10010];
//};




//class Solution {
//public:
//    int coinChange(vector<int>& coins, int amount) {
//        if (coins.size() && amount == 0) {
//            return 0;
//        }
//        coins.insert(coins.begin(), 0);
//        memset(dp, 0x3f, sizeof(dp));
//        dp[0] = 0;
//        for (int i = 1; i < coins.size(); i++) {
//            for (int j = coins[i]; j <= amount; j++) {
//                dp[j] = min(dp[j], dp[j - coins[i]] + 1);
//            }
//        }
//        ULL tmp = 0;
//        memset(&tmp, 0x3f, sizeof(tmp));
//        return dp[amount] == tmp ? -1 : dp[amount];
//    }
//    typedef unsigned long long ULL;
//    ULL dp[10010];
//};


//class Solution {
//public:
//    int numSquares(int n) {
//        memset(dp, 0x3f, sizeof(dp));
//        dp[0] = 0;
//        for (int i = 1; i <= sqrt(n); i++) {
//            int num = i * i;
//            for (int j = num; j <= n; j++) {
//                dp[j] = min(dp[j], dp[j - num] + 1);
//            }
//        }
//        return dp[n];
//    }
//    typedef unsigned long long ULL;
//    int dp[10010];
//};


//class Solution {
//public:
//    int numSquares(int n) {
//        memset(dp, 0x3f, sizeof(dp));
//        dp[0][0] = 0;
//        for (int i = 1; i <= sqrt(n); i++) {
//            int num = i * i;
//            for (int j = 0; j <= n; j++) {
//                dp[i][j] = dp[i - 1][j];
//                if (j >= num) {
//                    dp[i][j] = min(dp[i][j], dp[i][j - num] + 1);
//                }
//            }
//        }
//        return dp[(int)sqrt(n)][n];
//    }
//    typedef unsigned long long ULL;
//    int dp[110][10010];
//};

//class Solution {
//public:
//    int rob(vector<int>& nums) {
//        nums.insert(nums.begin(), 0);
//        dp[1] = nums[1];
//        for (int i = 2; i < nums.size(); i++) {
//            dp[i] = dp[i - 1];
//            if (i - 2 >= 0) {
//                dp[i] = max(dp[i], dp[i - 2] + nums[i]);
//            }
//        }
//        return dp[nums.size() - 1];
//    }
//    int dp[110];
//};

//class Solution {
//public:
//    int func(vector<int>& nums, int l, int r) {
//        memset(dp, 0, sizeof(dp));
//        dp[l] = nums[l];
//        for (int i = l + 1; i <= r; i++) {
//            dp[i] = dp[i - 1];
//            if (i - 2 >= l - 1) {
//                dp[i] = max(dp[i], dp[i - 2] + nums[i]);
//            }
//        }
//        return dp[r];
//    }
//    int rob(vector<int>& nums) {
//        nums.insert(nums.begin(), 0);
//        if (nums.size() == 2) {
//            return nums[1];
//        }
//        return max(func(nums, 1, nums.size() - 2), func(nums, 2, nums.size() - 1));
//    }
//    int dp[110];
//};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
//class Solution {
//public:
//    int dfs(TreeNode* root) {
//        if (root == nullptr) {
//            return m[root] = 0;
//        }
//        if (root->left == nullptr && root->right == nullptr) {
//            return m[root] = root->val;
//        }
//        if (m.count(root) != 0) {
//            return m[root];
//        }
//        int rob_cur = root->val;
//        if (root->left) {
//            rob_cur += dfs(root->left->left) + dfs(root->left->right);
//        }
//        if (root->right) {
//            rob_cur += dfs(root->right->left) + dfs(root->right->right);
//        }
//        int no_cur = dfs(root->left) + dfs(root->right);
//        return m[root] = max(rob_cur, no_cur);
//    }
//    int rob(TreeNode* root) {
//        return dfs(root);
//    }
//    typedef unsigned long long ULL;
//    unordered_map<TreeNode*, ULL> m;
//};


//class Solution {
//public:
//    int maxProfit(vector<int>& prices) {
//        prices.insert(prices.begin(), 0);
//        dp[1][0] = -0x3f3f3f3f;
//        for (int i = 1; i < prices.size(); i++) {
//            dp[0][i] = max(dp[1][i - 1] + prices[i], dp[0][i - 1]);
//            dp[1][i] = max(dp[1][i - 1], dp[0][i - 1] - prices[i]);
//        }
//        return dp[0][prices.size() - 1];
//    }
//    int dp[2][30010];
//};

//long long dp[100100][2][3];
//class Solution {
//public:
//    int maxProfit(vector<int>& prices) {
//        prices.insert(prices.begin(), 0);
//        memset(dp, -0x3f, sizeof(dp));
//        dp[0][0][2] = 0;
//
//        for (int i = 1; i < prices.size(); i++) {
//            dp[i][0][2] = 0;
//            dp[i][0][1] = max(dp[i - 1][0][1], dp[i - 1][1][1] + prices[i]);
//            dp[i][0][0] = max(dp[i - 1][0][0], dp[i - 1][1][0] + prices[i]);
//            dp[i][1][2] = -0x3f3f3f3f;
//            dp[i][1][1] = max(dp[i - 1][1][1], dp[i - 1][0][2] - prices[i]);
//            dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][0][1] - prices[i]);
//        }
//
//        int n = prices.size() - 1;
//        long long ret = max(max(dp[n][0][0], dp[n][0][1]), dp[n][0][2]);
//        return ret >= 0 ? ret : 0;
//    }
//};


//class Solution {
//public:
//    int maxProfit(int k, vector<int>& prices) {
//        prices.insert(prices.begin(), 0);
//        memset(dp, -0x3f, sizeof(dp));
//        dp[0][k][0] = 0;
//        for (int i = 1; i < prices.size(); i++) {
//            for (int j = 0; j <= k; j++) {
//                dp[i][j][0] = max(dp[i - 1][j][1] + prices[i], dp[i - 1][j][0]);
//                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j + 1][0] - prices[i]);
//            }
//        }
//        int ret = 0;
//        for (int i = 0; i <= k; i++) {
//            ret = max(ret, dp[prices.size() - 1][i][0]);
//        }
//        return ret >= 0 ? ret : 0;
//    }
//    int dp[1010][110][2];
//};