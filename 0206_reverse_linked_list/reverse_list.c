// 206. 反转链表
// 简单
// 输入：head = [1,2,3,4,5]
// 输出：[5,4,3,2,1]
// 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 
#include <stdio.h>
#include <stdlib.h>


struct ListNode {
    int val;
    struct ListNode *next;
};

//递归 递归是神
static struct ListNode *recursive(struct ListNode *prev, struct ListNode *p)
{
    if (p == NULL) {
        return prev;
    }

    struct ListNode *q = p->next;
    p->next = prev;
    return recursive(p, q);
}

struct ListNode *reverseList(struct ListNode *head)
{
    return recursive(NULL, head);
}


#if 0
/* Iteration 迭代*/
struct ListNode *reverseList(struct ListNode *head)
{
    struct ListNode *prev = NULL;
    struct ListNode *p = head;//原数据处理
    while (p != NULL) {
        struct ListNode *q = p->next;//存放后面数据
        p->next = prev;//只保留一位并将后续初始化(NULL)，后续为prev的后续部分保存
        prev = p;//最后所需的数据
        p = q;//原数据剩余未处理部分
    }

    return prev;
}
#endif

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    struct ListNode *head = NULL, *p, *prev;
    for (i = 0; i < count; i++) {
        p = malloc(sizeof(*p));
        p->val = atoi(argv[i + 1]);
        p->next = NULL;
        if (head == NULL) {
            head = p;
        } else {
            prev->next = p;
        }
        prev = p;
    }

    for (p = reverseList(head); p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
    return 0;
}
