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
//    TreeNode* dfs(TreeNode* root, int val) {
//        if (root == nullptr) {
//            return nullptr;
//        }
//        if (root->val == val) {
//            return root;
//        }
//        TreeNode* ret_root_left = dfs(root->left, val), * ret_root_right = dfs(root->right, val);
//        return ret_root_left == nullptr ? ret_root_right : ret_root_left;
//    }
//    TreeNode* searchBST(TreeNode* root, int val) {
//        return dfs(root, val);
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
//    TreeNode* searchBST(TreeNode* root, int val) {
//        TreeNode* cur = root;
//        while (cur) {
//            if (cur->val == val) {
//                return cur;
//            }
//            if (cur->val > val) {
//                cur = cur->left;
//            }
//            else {
//                cur = cur->right;
//            }
//        }
//        return nullptr;
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
//    void dfs(vector<int>& front, TreeNode* root) {
//        if (root->left) {
//            dfs(front, root->left);
//        }
//        front.push_back(root->val);
//        if (root->right) {
//            dfs(front, root->right);
//        }
//    }
//    bool isValidBST(TreeNode* root) {
//        vector<int> front;
//        dfs(front, root);
//        for (int i = 0; i < front.size() - 1; i++) {
//            if (front[i] >= front[i + 1]) {
//                return false;
//            }
//        }
//        return true;
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
//    bool isValidBST(TreeNode* root) {
//        vector<int> front;
//        stack<TreeNode*> st;
//        TreeNode* cur = root;
//        while (cur || st.size()) {
//            while (cur) {
//                st.push(cur);
//                cur = cur->left;
//            }
//            cur = st.top();
//            st.pop();
//            front.push_back(cur->val);
//            cur = cur->right;
//        }
//        for (int i = 0; i < front.size() - 1; i++) {
//            if (front[i] >= front[i + 1]) {
//                return false;
//            }
//        }
//        return true;
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
//    bool isValidBST(TreeNode* root) {
//        long long front_num = -0x3f3f3f3f3f3f3f3f, cur_num = 0;
//        stack<TreeNode*> st;
//        TreeNode* cur = root;
//        while (cur || st.size()) {
//            while (cur) {
//                st.push(cur);
//                cur = cur->left;
//            }
//            cur = st.top();
//            st.pop();
//            cur_num = cur->val;
//            if (front_num >= cur_num) {
//                return false;
//            }
//            front_num = cur_num;
//            cur = cur->right;
//        }
//        return true;
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
//    int getMinimumDifference(TreeNode* root) {
//        long long _min = 0x3f3f3f3f3f3f3f3f;
//        long long prev_val = 0x3f3f3f3f3f3f3f3f;
//        TreeNode* cur = root;
//        stack<TreeNode*> st;
//        while (cur || st.size()) {
//            while (cur) {
//                st.push(cur);
//                cur = cur->left;
//            }
//            cur = st.top();
//            st.pop();
//            if (prev_val != 0x3f3f3f3f3f3f3f3f) {
//                _min = min(_min, abs(cur->val - prev_val));
//            }
//            prev_val = cur->val;
//            cur = cur->right;
//        }
//        return _min;
//
//    }
//};
