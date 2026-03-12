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
class Solution {
public:
    TreeNode* dfs(int i_l, int i_r, int p_l, int p_r) {//给两个区间，还原一棵树
        if (i_l == i_r) {
            return new TreeNode(inorder[i_l]);
        }
        if (i_l > i_r) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(postorder[p_r]);
        int pos = -1;
        for (int i = 0; i < inorder.size(); i++) {
            if (inorder[i] == postorder[p_r]) {
                pos = i;
            }
        }
        root->left = dfs(i_l, pos - 1, p_l, p_l + pos - i_l - 1);
        root->right = dfs(pos + 1, i_r, p_l + pos - i_l, p_r - 1);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        this->inorder = inorder;
        this->postorder = postorder;
        return dfs(0, inorder.size() - 1, 0, postorder.size() - 1);
    }
    vector<int> inorder, postorder;
};