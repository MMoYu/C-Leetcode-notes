// 94. 二叉树的中序遍历 遍历顺序:左节点->根节点->右节点
// 简单
// 1.9K

// 给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。


// 二叉树：
// 先序遍历：根节点==》左节点==》右节点
// 中序遍历：左节点==》根节点==》右节点
// 后序遍历：左节点==》右节点==》根节点


#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{ //TreeNode结构体名
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode,*Tree;

//创建 链表
Tree  CreateLink()
{
	int data;
	int temp;
	Tree  node;
	
	scanf("%d",&data);		//	输入数据
	temp=getchar();			//	吸收空格
	
	if(data == 0){			//	输入 0 代表此节点下子树不存数据，也就是不继续递归创建
		
		return NULL;

	}else{
		node = (Tree)malloc(sizeof(TreeNode));			//		分配内存空间
		node->val = data;								//		把当前输入的数据存入当前节点指针的数据域中
		
		printf("请输入%d的左子树: ",data);		
		node->left = CreateLink();					//		开始递归创建左子树
		printf("请输入%d的右子树: ",data);			
		node->right = CreateLink();					//		开始到上一级节点的右边递归创建左右子树
		return node;							//		返回根节点
	}	
	
}

//递归
static void traverse(struct TreeNode *node, int *result, int *count)
{
    if (node == NULL) {
        return;
    }

    traverse(node->left, result, count); //先左
    result[*count] = node->val;
    (*count)++;  //根节点
    printf("%d",node->val);
    traverse(node->right, result, count);//最后右节点
    //前中后序遍历只需要调整这一部分的顺序即可完成
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
    Tree root;
	printf("请输入第一个节点的数据:\n");
	root = CreateLink();
    int count = 0;
    inorderTraversal(root, &count);
    putchar('\n');
    return 0;
}


