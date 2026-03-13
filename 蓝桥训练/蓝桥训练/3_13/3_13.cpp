///**
// * Definition for a binary tree node.
// * struct TreeNode {
// *     int val;
// *     TreeNode *left;
// *     TreeNode *right;
// *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
// *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// * };
// */
//class Solution {
//public:
//    void bfs() {
//        int cur_cnt = 1;
//        int next_cnt = 0;
//        queue<TreeNode*> q;
//        q.push(root);
//        vector<int> vi;
//        while (q.size()) {
//            TreeNode* f = q.front();
//            q.pop();
//            cur_cnt--;
//            vi.push_back(f->val);
//            if (f->left) {
//                q.push(f->left);
//                next_cnt++;
//            }
//            if (f->right) {
//                q.push(f->right);
//                next_cnt++;
//            }
//            //计数的层序遍历，一定要将判断放到最后面！！
//            if (cur_cnt == 0) {
//                cur_cnt = next_cnt;
//                next_cnt = 0;
//                vvi.push_back(vi);
//                vi.clear();
//            }
//        }
//    }
//    vector<vector<int>> levelOrder(TreeNode* root) {
//        if (root == nullptr) {
//            return {};
//        }
//        this->root = root;
//        bfs();
//        return vvi;
//    }
//    TreeNode* root;
//    vector<vector<int>> vvi;
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
//    TreeNode* func(TreeNode* root) {
//        if (root == nullptr) {
//            return nullptr;
//        }
//        TreeNode* tmp = root->left;
//        root->left = root->right;
//        root->right = tmp;
//        func(root->left);
//        func(root->right);
//        return root;
//    }
//    TreeNode* invertTree(TreeNode* root) {
//        return func(root);
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
//    bool func(TreeNode* r1, TreeNode* r2) {
//        if (r1 == nullptr && r2 == nullptr) {
//            return true;
//        }
//        if (r1 == nullptr || r2 == nullptr) {
//            return false;
//        }
//        return (r1->val == r2->val) && func(r1->left, r2->right) && func(r1->right, r2->left);
//    }
//    bool isSymmetric(TreeNode* root) {
//        return func(root, root);
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
//    int dfs(TreeNode* root) {
//        if (root == nullptr) {
//            return 0;
//        }
//        if (root->left == nullptr && root->right == nullptr) {
//            return 1;
//        }
//        if (root->left == nullptr) {
//            return dfs(root->right) + 1;
//        }
//        if (root->right == nullptr) {
//            return dfs(root->left) + 1;
//        }
//        return dfs(root->right) + dfs(root->left) + 1;
//    }
//    int countNodes(TreeNode* root) {
//        return dfs(root);
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
//    int height(TreeNode* root) {
//        if (root == nullptr) {
//            return 0;
//        }
//        int hl = height(root->left);
//        int hr = height(root->right);
//        return max(hl, hr) + 1;
//    }
//    bool dfs(TreeNode* root) {//判平衡
//        if (root == nullptr) {
//            return true;
//        }
//        int hl = height(root->left);
//        int hr = height(root->right);
//        if (abs(hl - hr) >= 2) {
//            return false;
//        }
//        return dfs(root->right) && dfs(root->left);
//    }
//    bool isBalanced(TreeNode* root) {
//        return dfs(root);
//    }
//};