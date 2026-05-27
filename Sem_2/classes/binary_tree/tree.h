#ifndef TREE_H
#define TREE_H

#include <vector>

struct TreeNode {
    double data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(double val);
};

class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();
    void clear();
    void clear(TreeNode* node);
    void insert(double val);
    TreeNode* insert(TreeNode* node, double val);
    bool remove(double val);
    TreeNode* remove(TreeNode* node, double val);
    bool find(double val);
    bool find(TreeNode* node, double val);
    std::vector<double> preorder();
    std::vector<double> inorder();
    std::vector<double> postorder();
    void preorder(TreeNode* node, std::vector<double>& result);
    void inorder(TreeNode* node, std::vector<double>& result);
    void postorder(TreeNode* node, std::vector<double>& result);
    void balance();
    std::vector<double> toSortedArray();
    void toSortedArray(TreeNode* node, std::vector<double>& arr);
    TreeNode* buildBalanced(std::vector<double>& arr, int start, int end);
    double findMax();
    double findMax(TreeNode* node);
    TreeNode* getRoot() { return root; }

private:
    TreeNode* root;
    TreeNode* findMin(TreeNode* node);
};

#endif
