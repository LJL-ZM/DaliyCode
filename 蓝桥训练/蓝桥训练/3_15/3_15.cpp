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
//    vector<int> findMode(TreeNode* root) {
//        if (root == nullptr) {
//            return {};
//        }
//        stack<TreeNode*> st;
//        TreeNode* cur = root;
//        LL prev_val = -0x3f3f3f3f;
//        vector<int> ret;
//        while (cur || st.size()) {
//            while (cur) {
//                st.push(cur);
//                cur = cur->left;
//            }
//            cur = st.top();
//            st.pop();
//            if (cur->val == prev_val) {
//                cur_cnt++;
//            }
//            else {
//                cur_cnt = 1;
//            }
//            max_cnt = max(max_cnt, cur_cnt);
//            prev_val = cur->val;
//            cur = cur->right;
//        }
//        //ret.push_back(max_cnt);
//        cur_cnt = 0;
//        cur = root;
//        prev_val = -0x3f3f3f3f;
//        while (cur || st.size()) {
//            while (cur) {
//                st.push(cur);
//                cur = cur->left;
//            }
//            cur = st.top();
//            st.pop();
//            if (cur->val == prev_val) {
//                cur_cnt++;
//            }
//            else {
//                if (cur_cnt == max_cnt) {
//                    ret.push_back(prev_val);
//                }
//                cur_cnt = 1;
//            }
//            prev_val = cur->val;
//            cur = cur->right;
//        }
//        if (cur_cnt == max_cnt) {
//            ret.push_back(prev_val);
//        }
//        return ret;
//    }
//    typedef long long LL;
//    LL max_cnt = 0;
//    LL cur_cnt = 0;
//};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//class Solution {
//public:
//    //后序遍历！！！！！
//    //
//    TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
//        if (root == nullptr || root == p || root == q) {
//            return root;
//        }
//        TreeNode* left = dfs(root->left, p, q);
//        TreeNode* right = dfs(root->right, p, q);
//        if (left != nullptr && right != nullptr) {
//            return root;
//        }
//        return left == nullptr ? right : left;
//    }
//    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//        return dfs(root, p, q);
//    }
//};
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//class Solution {
//public:
//    TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
//        if (root == nullptr || p == root || q == root) {
//            return root;
//        }
//        if (p->val < root->val && q->val < root->val) {
//            return dfs(root->left, p, q);
//        }
//        if (p->val > root->val && q->val > root->val) {
//            return dfs(root->right, p, q);
//        }
//        return root;
//    }
//    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//        return dfs(root, p, q);
//    }
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
//    TreeNode* insertIntoBST(TreeNode* root, int val) {
//        TreeNode* newnode = new TreeNode(val);
//        if (root == nullptr) {
//            return newnode;
//        }
//        TreeNode* prev = nullptr, * cur = root;
//        while (cur) {
//            prev = cur;
//            if (val < cur->val) {
//                cur = cur->left;
//            }
//            else {
//                cur = cur->right;
//            }
//        }
//        if (val < prev->val) {
//            prev->left = newnode;
//        }
//        else {
//            prev->right = newnode;
//        }
//        return root;
//    }
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
//    TreeNode* deleteNode(TreeNode* root, int key) {
//        if (root == nullptr) {
//            return nullptr;
//        }
//        TreeNode* cur = root, * prev = nullptr, * target = nullptr;
//        while (cur && cur->val != key) {
//            prev = cur;
//            if (key < cur->val) {
//                cur = cur->left;
//            }
//            else if (key > cur->val) {
//                cur = cur->right;
//            }
//        }
//        if (cur == nullptr) {
//            return root;
//        }
//        if (cur->left == nullptr || cur->right == nullptr) {
//            TreeNode* tmp = cur->left == nullptr ? cur->right : cur->left;
//            if (prev == nullptr) {
//                return tmp;
//            }
//            if (cur == prev->left) {
//                prev->left = tmp;
//            }
//            else {
//                prev->right = tmp;
//            }
//            return root;
//        }
//        target = prev = cur;
//        cur = cur->right;
//        while (cur->left) {
//            prev = cur;
//            cur = cur->left;
//        }
//        target->val = cur->val;
//        if (cur == prev->left) {
//            prev->left = cur->right;
//        }
//        else {
//            prev->right = cur->right;
//        }
//        return root;
//    }
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
//    TreeNode* dfs(TreeNode* root, int low, int high) {
//        if (!root) {
//            return nullptr;
//        }
//        if (root->val < low) {
//            return dfs(root->right, low, high);
//        }
//        if (root->val > high) {
//            return dfs(root->left, low, high);
//        }
//        root->left = dfs(root->left, low, high);
//        root->right = dfs(root->right, low, high);
//        return root;
//    }
//    TreeNode* trimBST(TreeNode* root, int low, int high) {
//        return dfs(root, low, high);
//    }
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
//    TreeNode* dfs(vector<int>& nums, int l, int r) {
//        if (l > r) {
//            return nullptr;
//        }
//        if (l == r) {
//            return new TreeNode(nums[l]);
//        }
//        int pos = (l + r) / 2;
//        return new TreeNode(nums[pos], dfs(nums, l, pos - 1), dfs(nums, pos + 1, r));
//    }
//    TreeNode* sortedArrayToBST(vector<int>& nums) {
//        return dfs(nums, 0, nums.size() - 1);
//    }
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


 //这个问题需要单调递减，反中序遍历！！！！
 //这样就可以找到左右比当前值更大的值
//class Solution {
//public:
//    int sum = 0;
//    TreeNode* dfs(TreeNode* root) {
//        if (root == nullptr) {
//            return nullptr;
//        }
//        root->right = dfs(root->right);
//        sum += root->val;
//        root->val = sum;
//        root->left = dfs(root->left);
//        return root;
//    }
//    TreeNode* convertBST(TreeNode* root) {
//        return dfs(root);
//    }
//};

//class Solution {
//public:
//    int minCostClimbingStairs(vector<int>& cost) {
//        f[0] = f[1] = 0;
//        for (int i = 2; i <= cost.size(); i++) {
//            f[i] = min(f[i - 1] + cost[i - 1], f[i - 2] + cost[i - 2]);
//        }
//        return f[cost.size()];
//    }
//    int f[1010];
//};


//class Solution {
//public:
//    int uniquePaths(int m, int n) {
//        f[1][1] = 1;
//        for (int i = 1; i <= m; i++) {
//            for (int j = 1; j <= n; j++) {
//                if (!f[i][j]) {
//                    f[i][j] = f[i][j - 1] + f[i - 1][j];
//                }
//            }
//        }
//        return f[m][n];
//    }
//    int f[110][110];
//};


//class Solution {
//public:
//    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
//        if (obstacleGrid[0][0] == 1) {
//            return 0;
//        }
//        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
//        f[0][0] = 1;
//        for (int i = 1; i < n; i++) {
//            f[i][0] = obstacleGrid[i][0] == 1 ? 0 : 1;
//            if (obstacleGrid[i][0] == 1) {
//                break;
//            }
//        }
//        for (int i = 1; i < m; i++) {
//            f[0][i] = obstacleGrid[0][i] == 1 ? 0 : 1;
//            if (obstacleGrid[0][i] == 1) {
//                break;
//            }
//        }
//        for (int i = 1; i < n; i++) {
//            for (int j = 1; j < m; j++) {
//                f[i][j] = obstacleGrid[i][j] == 1 ? 0 : (f[i][j - 1] + f[i - 1][j]);
//            }
//        }
//        return f[n - 1][m - 1];
//    }
//    int f[1010][1010];
//};


//class Solution {
//public:
//    int integerBreak(int n) {
//        if (n < 4) {
//            return n - 1;
//        }
//        int ret = 1;
//        while (n > 4) {
//            ret *= 3;
//            n -= 3;
//        }
//        ret *= n;
//        return ret;
//    }
//};


//class Solution {
//public:
//    int numTrees(int n) {
//        f[0] = f[1] = 1;
//        for (int i = 2; i <= n; i++) {
//            for (int j = 1; j <= i; j++) {
//                f[i] += f[j - 1] * f[i - j];
//            }
//        }
//        return f[n];
//    }
//    int f[25];
//};