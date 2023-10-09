// 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的 两个 整数。
// 你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
// 示例:
// 给定 nums = [2, 7, 11, 15], target = 9
// 因为 nums[0] + nums[1] = 2 + 7 = 9
// 所以返回 [0, 1]

#include <stdio.h>
#include <stdlib.h>


struct object {
    int val;
    int index;
};

//还有二分法，暂无
//法一：哈希写法，将乱序变为有序，时间复杂度最优，空间复杂最差
static int compare(const void *a, const void *b)
{
    return ((struct object *) a)->val - ((struct object *) b)->val;
}

	/*
	qsort 对数组进行排序
	void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
	base -- 指向要排序的数组的第一个元素的指针。
	nitems -- 由 base 指向的数组中元素的个数。
	size -- 数组中每个元素的大小，以字节为单位。
	compar -- 用来比较两个元素的函数。
	*/

int *twosum(int *nums, int numsSize, int target, int *returnSize)
{
    int i, j;
	struct object *objs=NULL;
	//objs = malloc(numsSize * sizeof(*objs));
	objs = (struct object *)malloc(numsSize * sizeof(*objs));//这个正规点
    //struct object *objs = malloc(numsSize * sizeof(*objs));
	//这里使用malloc没有free，题目中假设main函数已有free;
	//实际上在这个进程结束的时候，现代系统一般都会释放掉;
    for (i = 0; i < numsSize; i++) {
        objs[i].val = nums[i];
        objs[i].index = i;
    }
    qsort(objs, numsSize, sizeof(*objs), compare);//对数组进行排列  qsort==quicksort 快速排列
    //base -- 指向要排序的数组的第一个元素的指针。，compare比较后，会按objs[i~j从小到大排列，会导致最初的序列变化，但是objs->index未变，可以通过这个知道下标]
    //排序会打乱所给数组的下标，此题仅要求输出答案值，可不在意所给下标；不过objs的结构体中的 index记录了下标，虽然没有用上，但是这题有考虑这方面的问题

    //111
    int *results = malloc(2 * sizeof(int));
    i = 0;
    j = numsSize - 1;
    while (i < j) {
        int sum = objs[i].val + objs[j].val;
        if (sum < target) {
            i++;
        } else if (sum > target) {
            j--;
        } else {
            results[0] = objs[i].index;
            results[1] = objs[j].index;
            //*returnSize = 2;
			//leetcode模板没有main，缺少变量传过来的数据
			//因此后续需设为2，即返回值个数
            return results;
        }
    }
    return NULL;
}

//相较于C++,C需要更多的轮子
int main(void)
{
    //int nums[] = {-1, -2, -3, -4, -5};
    //int target = -8;
    //int nums[] = {0,4,3,0};
    //int target = 0;
    int nums[] = { 3, 2, 3 };
    int size = sizeof(nums) / sizeof(*nums);//个数
    int target = 6;
    int count = 0;
    int *indexes = twosum(nums, size, target, &count);
    if (indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    } else {
        printf("Not found\n");
    }
	//自己加的,报错undeclared;
	//free(objs);
	//objs=NULL;
    return 0;
}



//法二：双循环暴力解法，较简单//O(n^2)   空间复杂度最优，但是时间复杂度差
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// int* twoSum(int* nums, int numsSize, int target, int* returnSize)
// {
//     int *num = malloc(sizeof(int)*2);
// 	int i = 0;
// 	int j = i+1;
// 		//j比i大了1，为了防止数组越界访问 
		
//     for(int i = 0; i < numsSize - 1; i++)
//     {
//         for(int j = i + 1; j < numsSize; j++)
//         {
//             if(nums[i] + nums[j] == target)
//             {
//                 num[0] = i;
//                 num[1] = j;
//                 *returnSize = 2;//无main时，不能删除
//                 return num;
//             }
//         }
//     }
//     return NULL;
// }
