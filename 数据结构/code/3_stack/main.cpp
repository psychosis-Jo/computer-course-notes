#include <iostream>
#include "stack.h"

int main()
{
    Stack<char> S;

    // 测试数字转换为不同进制
    __int64 n = 123;
    int base = 2;
    convert_i(S, n, base);
    std::cout << "The number " << n << " in base " << base << " is: ";
    while (!S.empty())
    {
        std::cout << S.pop();
    }
    std::cout << std::endl;

    n = 255;
    base = 16;
    convert_r(S, n, base);
    std::cout << "The number " << n << " in base " << base << " is: ";
    while (!S.empty())
    {
        std::cout << S.pop();
    }
    std::cout << std::endl;

    // 测试括号匹配检查
    const char exp1[] = "((a+b)*c)-{d+e}";
    const char exp2[] = "((a+b)*c-{d+e}";
    if (paren_r(exp1, 0, 10))
    {
        std::cout << "Expression 1 has matched parentheses." << std::endl;
    }
    else
    {
        std::cout << "Expression 1 does not have matched parentheses." << std::endl;
    }

    if (paren3(exp2, 0, 11))
    {
        std::cout << "Expression 2 has matched parentheses." << std::endl;
    }
    else
    {
        std::cout << "Expression 2 does not have matched parentheses." << std::endl;
    }

    return 0;
}
