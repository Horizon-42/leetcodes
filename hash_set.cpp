#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    unordered_set<size_t> trees;
    unordered_map<size_t, TreeNode *> duplited;
    void mid_iter(TreeNode *root, size_t &hash_code)
    {
        if (root == nullptr)
        {
            hash_code = 0;
            return;
        }

        size_t left_hash = 0;
        size_t right_hash = 0;
        mid_iter(root->left, left_hash);
        mid_iter(root->right, right_hash);

        if (trees.find(left_hash) != trees.end())
        {
            duplited[left_hash] = root->left;
        }
        if (trees.find(right_hash) != trees.end())
        {
            duplited[right_hash] = root->right;
        }
        trees.insert(left_hash);
        trees.insert(right_hash);

        hash_code = 31 * left_hash + root->val;
        hash_code = 31 * hash_code + right_hash;
        if (trees.find(hash_code) != trees.end())
        {
            duplited[hash_code] = root;
        }
        trees.insert(hash_code);
        trees.count(hash_code);
    }

    vector<TreeNode *> findDuplicateSubtrees(TreeNode *root)
    {
        vector<TreeNode *> result;
        size_t hash_code = 0;
        mid_iter(root, hash_code);
        for (auto &item : duplited)
        {
            result.push_back(item.second);
        }
        return result;
    }
};
