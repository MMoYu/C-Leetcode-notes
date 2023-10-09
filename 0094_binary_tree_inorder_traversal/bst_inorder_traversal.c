// 94. 二叉树的中序遍历 遍历顺序:左节点->根节点->右节点
// 简单
// 1.9K

// 给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static void traverse(struct TreeNode *node, int *result, int *count)
{
    if (node == NULL) {
        return;
    }

    traverse(node->left, result, count);
    result[*count] = node->val;
    (*count)++;
    traverse(node->right, result, count);
}

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int count = 0;
    int *result = malloc(5000 * sizeof(int));
    traverse(root, result, &count);
    *returnSize = count;
    return result;
}

int main()
{
    int count = 0;
    inorderTraversal(NULL, &count);
    return 0;
}
