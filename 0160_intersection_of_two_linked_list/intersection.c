#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。

// 图示两个链表在节点 c1 开始相交：
// A: A1 A2 A3 A4 A5 A6
// b: B1 B2 B3 A4 A5 A6
// ==> 相交A4

// 题目数据 保证 整个链式结构中不存在环。

// 注意，函数返回结果后，链表必须 保持其原始结构 。
// 自定义评测：

// 评测系统 的输入如下（你设计的程序 不适用 此输入）：

// intersectVal - 相交的起始节点的值。如果不存在相交节点，这一值为 0
// listA - 第一个链表
// listB - 第二个链表
// skipA - 在 listA 中（从头节点开始）跳到交叉节点的节点数
// skipB - 在 listB 中（从头节点开始）跳到交叉节点的节点数
// 评测系统将根据这些输入创建链式数据结构，并将两个头节点 headA 和 headB 传递给你的程序。如果程序能够正确返回相交节点，那么你的解决方案将被 视作正确答案 。
// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     struct ListNode *next;
//  * };
//  */
// struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {

// }

//法一：A和B练成链表，，采用快慢指针判断是否有环，重新相遇
struct ListNode
{
    int val;
    struct ListNode *next;
};

static struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    if (headA == NULL || headB == NULL)
    {
        return NULL;
    }

    struct ListNode *p;
    for (p = headA; p->next != NULL; p = p->next)
    {
    }
    //for后的{}不能删掉，删掉就进入死循环了,因为这里上下不是一起的
    //实际上，上面的for就是完整的for循环
    // 等同于：
    // struct ListNode *p = headA;
    // while(p->next != NULL){
    //     p = p->next;
    // }
    p->next = headB;//将链表B放在A链表后，组合起来

    struct ListNode *slow = headA, *fast = headA; //快慢指针

    //快慢指针方法 == 龟兔算法 （快慢指针简单应用==》回文链表）
    // 如果链表中节点个数为偶数时，当快指针无法继续移动时，慢指针刚好指向中点；
    // 如果链表中节点个数为奇数时，当快指针走完，慢指针指向中点前一个节点。
    while (fast != NULL && fast->next != NULL) //&& fast->next->next != NULL)最好加上这个调节，不然下方fast = fast->next->next会越界
    {

        slow = slow->next;       //指针每次走一步
        fast = fast->next->next; //指针每次走两步，有环则会走到环处回去；// 最重要的理解：赋值时按地址赋的，值一样的话地址也是一样的，会循环回去；
        //printf("%d\n",fast->next->next->val);//这里错了，上面已经改地址了，不需要再这么深入
        printf("%d\n",fast->val);
        //疑问：没有环的话，上面这里会越界; fast = fast->next->next;会赋一个未知地址，但是不操作(如打印)不报错，操作就会报错
        if (slow == fast) //如果两指针相遇则组合有环
        {
            slow = headA; //指向A的头节点
            while (slow != fast) //此时两指针再相遇的地方就是两链表相交的地方
            {
                slow = slow->next; //指针下移
                fast = fast->next; //指针下移
            }
            p->next = NULL;
            return slow; //两链表相交节点
        }
    }

    p->next = NULL;
    return NULL;
}

int main(int argc, char **argv)
{
    struct ListNode *headA = malloc(sizeof(*headA));
    struct ListNode *headB = malloc(sizeof(*headB));
    struct ListNode *common = malloc(sizeof(*common));
    struct ListNode *common2 = malloc(sizeof(*common2));
    //每赋值一次都要申请一次空间，不可以直接对next节点直接赋值
    //所有指针未初始化都是野指针，都需要初始化，无论嵌套多少层
    //

    headA->val = 1;
    headB->val = 2;
    common->val = 4;
    common->next= NULL;

    //放到嵌套初始化前面或者后面没有用，因为赋值的是地址
    headA->next = common;

    //以下时两种嵌套指针初始化方式；可以通过数组首地址进行申请空间，也可以common->next =malloc(sizeof(*common));
    //这种花里胡哨的很喜欢
    // common[0].next = malloc(sizeof(*common));
    // common[0].next->val =3;
    // common[0].next->next = NULL;

    // common->next = malloc(sizeof(*common));
    // common->next->val =3;
    // common->next->next = NULL;
    
    //headB->next = common[0].next;//两种方式可以互用
    common2->val = 4;//注意，这里值一样但是申请地址的空间不一样
    common2->next =NULL;
    headB->next = common2;


    struct ListNode *p = getIntersectionNode(headA, headB);
    if (p != NULL)
    {
        printf("%d\n", p->val);
    } else printf("error\n");
    
    return 0;
}

//法二：直接遍历地址；地址相同则为相交节点；
//重点在于当短链表指针遍历完短链表后接着遍历长链表，长链表指针遍历完自己后接着遍历短链表
// 让短链表指针P1、长链表指针P2同时从各自表头遍历
// 当短链表指针遍历完短链表后接着遍历长链表，长链表指针遍历完自己后接着遍历短链表，当两个指针所指节点地址一样时，这个节点就是相交节点。
// 时间复杂度
// 只使用了while循环，执行次数是链表长度的常数倍，所以时间复杂度还是O(n)
// 空间复杂度
// 我们只使用了两个指针，所以空间复杂度为O(1)

// struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
// {
//     if (!headA || !headB)
//     {
//         return NULL;
//     }

//     struct ListNode *nodeA = headA;
//     struct ListNode *nodeB = headB;
//     while (nodeA != nodeB) //没有找到相交节点前
//     {
//         nodeA = nodeA == NULL ? headB:nodeA->next; //A链表没有遍历完就一直遍历，如果遍历完就接着从B链表遍历
//         nodeB = nodeB == NULL ? headB:nodeB->next; // B同上，当两个节点地址相同时结束循环
//     }
//     return nodeA;
// }

// 法三：先求出两个链表的长度，再求出长度差值dis。
// 较长链表的头节点出发，走长度差值dis个节点，这样就屏蔽掉了链表之间的长度插；
// 然后与从短链表头节点的另一个指针P2同时开始遍历各自对应链表，每到一个节点就互相判断地址是否相同。
// /**
// * 求链表长度
// */
// int getLength(struct ListNode *list)
// {
//     int length = 0;
//     while (list)
//     {
//         length++;
//         list = list->next;
//     }
//     return length;
// }

// struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
// {
//     if (!headA || !headB) //任一链表为空则不存在相交可能
//     {
//         return NULL;
//     }

//    struct ListNode *nodeA = headA;
//     struct ListNode *nodeB = headB;
//     int lengthOfListA = getLength(nodeA);
//     int lengthOfListB = getLength(nodeB);
//     int dis = (lengthOfListA < lengthOfListB) ? (lengthOfListB-lengthOfListA) : (lengthOfListA - lengthOfListB); //链表长度差

//     if (lengthOfListA > lengthOfListB) //找到较长链表，让其指针先走差值dis个节点
//     {
//         for (int i = 0; i < dis; i++)
//         {
//             nodeA = nodeA->next;
//         }
//     }
//     else
//     {
//         for (int i = 0; i < dis; i++)
//         {
//             nodeB = nodeB->next;
//         }
//     }
//     while (nodeA != nodeB) // 屏蔽掉长度差后，同步遍历两个链表，找到相交节点后跳出循环；若没有相交节点，nodeA取值为null
//     {
//         nodeA = nodeA->next;
//         nodeB = nodeB->next;
//     }
//     return nodeA;
// }
