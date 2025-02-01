#include <cctype>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "stack.h"
#define N_OPTR 9 // 运算符总数
typedef enum
{
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    FAC,
    L_P,
    R_P,
    EOE
} Operator; // 运算符集合
// 加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const char pri[N_OPTR][N_OPTR] = {
    /*     |--------------------弼前运算符--------------------| */
    /*        +   -      *    /    ^    !    (    )   \0 */
    /* --+ */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* |   -*/ '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* 栈* */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* 顶/ */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* 运^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
    /* 算! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
    /* 符( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
    /* |   ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    /* --\0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '='};

void readNumber(char *&S, Stack<float> &opnd)
{
    opnd.push(std::strtod(S, &S));
}
void append(char *&RPN, float val)
{
    // 这里假设你使用C风格的字符串，可以使用std::sprintf进行字符串拼接
    char buffer[20];                  // 假设最大的float值需要20个字符来表示
    std::sprintf(buffer, "%f ", val); // 将浮点数格式化为字符串
    strcat(RPN, buffer);              // 将格式化后的字符串追加到RPN末尾
}

void append(char *&RPN, char op)
{
    // 这里假设你使用C风格的字符串
    char buffer[2] = {op, ' '}; // 将操作符和空格组合成一个字符串
    strcat(RPN, buffer);        // 将操作符追加到RPN末尾
}

int orderBetween(char op1, char op2)
{
    if (op1 == '(' || op2 == '(')
        return '<'; // 左括号优先级最高
    if (op2 == ')' || op1 == '\0')
        return '>'; // 右括号优先级最低
    if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/'))
        return '<'; // + - 优先级低于 * /
    return '=';
}

float calcu(char op, float operand1, float operand2 = 0)
{
    switch (op)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        // 检查是否是一元运算符
        if (operand2 == 0)
        {
            return -operand1; // 一元负号运算
        }
        else
        {
            return operand1 - operand2; // 二元减法运算
        }
    case '*':
        return operand1 * operand2;
    case '/':
        if (operand2 != 0)
        {
            return operand1 / operand2;
        }
        else
        {
            // 处理除零错误
            // 可以根据具体情况抛出异常或者返回特定值
            return 0.0; // 这里返回一个默认值
        }
    default:
        // 处理未知运算符错误
        // 可以根据具体情况抛出异常或者返回特定值
        return 0.0; // 这里返回一个默认值
    }
}

float evaluate(char *S, char *&RPN) // 对（已剔除白空格的）表达式S求值，幵转换为逆波兰式RPN
{
    Stack<float> opnd;
    Stack<char> optr; // 运算数栈、运算符栈
    optr.push('\0');  // 尾哨兵'\0'也作为头哨兵首先入栈
    while (!optr.empty())
    { // 在运算符栈非空之前，逐个处理表达式中各字符
        if (isdigit(*S))
        { // 若当前字符为操作数，则
            readNumber(S, opnd);
            append(RPN, opnd.top()); // 读入操作数，并将其接至RPN末尾
        }
        else                                      // 若当前字符为运算符，则
            switch (orderBetween(optr.top(), *S)) // 视其与栈顶运算符之间优先级高低分别处理
            {
            case '<': // 栈顶运算符优先级更低时
                optr.push(*S);
                S++; // 计算推迟，当前运算符进栈
                break;
            case '=': // 优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
                optr.pop();
                S++; // 脱括号幵接收下一个字符
                break;
            case '>':
            { // 栈顶运算符优先级更高时，可实斲相应的计算，并将结果重新入栈
                char op = optr.pop();
                append(RPN, op); // 栈顶运算符出栈并续接至RPN末尾
                if ('!' == op)   // 若属于一元运算符
                {
                    float pOpnd = opnd.pop();    // 叧需取出一个操作数，并
                    opnd.push(calcu(op, pOpnd)); // 实施一元计算，结果入栈
                }
                else // 对于其它（二元）运算符
                {
                    float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); // 取出后、前操作数
                    opnd.push(calcu(pOpnd1, op, pOpnd2));           // 实施二元计算，结果入栈
                }
                break;
            }
            default:
                exit(-1); // 逢语法错误，不做处理直接退出
            } // switch
    } // while
    return opnd.pop(); // 弹出并返回最后的计算结果
}

int main()
{
    char expr[] = "3 + 4 * 2 / (1 - 5) ^ 2 ^ 3";
    char *RPN;
    float result = evaluate(expr, RPN);

    std::cout << "Original expression: " << expr << std::endl;
    std::cout << "Result: " << result << std::endl;
    std::cout << "Reverse Polish Notation: " << RPN << std::endl;

    // 释放 RPN 指向的内存
    delete[] RPN;

    return 0;
}
