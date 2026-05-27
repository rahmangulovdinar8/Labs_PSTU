#include "tree.h"
#include <algorithm>
#include <limits>

TreeNode::TreeNode(double val) : data(val), left(nullptr), right(nullptr) {}

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    clear();
}

void BinaryTree::clear() {
    clear(root);
    root = nullptr;
}

void BinaryTree::clear(TreeNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void BinaryTree::insert(double val) {
    root = insert(root, val);
}

TreeNode* BinaryTree::insert(TreeNode* node, double val) {
    if (!node) return new TreeNode(val);
    if (val < node->data)
        node->left = insert(node->left, val);
    else if (val > node->data)
        node->right = insert(node->right, val);
    return node;
}

bool BinaryTree::remove(double val) {
    if (find(val)) {
        root = remove(root, val);
        return true;
    }
    return false;
}

TreeNode* BinaryTree::remove(TreeNode* node, double val) {
    if (!node) return nullptr;
    if (val < node->data)
        node->left = remove(node->left, val);
    else if (val > node->data)
        node->right = remove(node->right, val);
    else {
        if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        TreeNode* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }
    return node;
}

TreeNode* BinaryTree::findMin(TreeNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

bool BinaryTree::find(double val) {
    return find(root, val);
}

bool BinaryTree::find(TreeNode* node, double val) {
    if (!node) return false;
    if (val == node->data) return true;
    if (val < node->data) return find(node->left, val);
    return find(node->right, val);
}

std::vector<double> BinaryTree::preorder() {
    std::vector<double> result;
    preorder(root, result);
    return result;
}

void BinaryTree::preorder(TreeNode* node, std::vector<double>& result) {
    if (node) {
        result.push_back(node->data);
        preorder(node->left, result);
        preorder(node->right, result);
    }
}

std::vector<double> BinaryTree::inorder() {
    std::vector<double> result;
    inorder(root, result);
    return result;
}

void BinaryTree::inorder(TreeNode* node, std::vector<double>& result) {
    if (node) {
        inorder(node->left, result);
        result.push_back(node->data);
        inorder(node->right, result);
    }
}

std::vector<double> BinaryTree::postorder() {
    std::vector<double> result;
    postorder(root, result);
    return result;
}

void BinaryTree::postorder(TreeNode* node, std::vector<double>& result) {
    if (node) {
        postorder(node->left, result);
        postorder(node->right, result);
        result.push_back(node->data);
    }
}

void BinaryTree::balance() {
    std::vector<double> arr = toSortedArray();
    clear();
    root = buildBalanced(arr, 0, arr.size() - 1);
}

std::vector<double> BinaryTree::toSortedArray() {
    std::vector<double> arr;
    inorder(root, arr);
    return arr;
}

TreeNode* BinaryTree::buildBalanced(std::vector<double>& arr, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    TreeNode* node = new TreeNode(arr[mid]);
    node->left = buildBalanced(arr, start, mid - 1);
    node->right = buildBalanced(arr, mid + 1, end);
    return node;
}

double BinaryTree::findMax() {
    if (!root) return -std::numeric_limits<double>::infinity();
    return findMax(root);
}

double BinaryTree::findMax(TreeNode* node) {
    double max = node->data;
    if (node->left) {
        double leftMax = findMax(node->left);
        if (leftMax > max) max = leftMax;
    }
    if (node->right) {
        double rightMax = findMax(node->right);
        if (rightMax > max) max = rightMax;
    }
    return max;
}
