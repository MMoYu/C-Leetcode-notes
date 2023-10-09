// 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

// 有效字符串需满足：

// 左括号必须用相同类型的右括号闭合。
// 左括号必须以正确的顺序闭合。
// 每个右括号都有一个对应的相同类型的左括号。


// 示例 1：
// 输入：s = "()"
// 输出：true

// 示例 2：
// 输入：s = "()[]{}"
// 输出：true

// 示例 3：
// 输入：s = "(]"
// 输出：false
 

// 提示：

// 1 <= s.length <= 104
// s 仅由括号 '()[]{}' 组成

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//算法思路：使用栈去存放左括号
static bool isValid(char *s)
{
    int n = 0;
    char stack[100];

    while (*s != '\0') { // \0 空字符
        switch(*s) {
        case '(':
        case '[':
        case '{':
            stack[n++] = *s; //stack 栈 
            break;
        case ')':
            if (n == 0 || stack[--n] != '(') return false;
            break;
        case ']':
            if (n == 0 || stack[--n] != '[') return false;
            break;
        case '}':
            if (n == 0 || stack[--n] != '{') return false;
            break;
        default:
            return false;
        }
        s++;
    }

    return n == 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test xxxx\n\r");
        exit(-1);
        //异常退出，返回-1
        //return是语言级别的，它表示了调用堆栈的返回；
        //而exit是系统调用级别的，它表示了一个进程的结束
        // 在main中：
        // return v;  与   exit(v);  的效果相同。
        // 但是在其它功能函数中就会有所区别：
        // return会跳出函数，而exit会结束程序
    }
    printf("%s\n", isValid(argv[1]) ? "true" : "false");
    return 0;
}
