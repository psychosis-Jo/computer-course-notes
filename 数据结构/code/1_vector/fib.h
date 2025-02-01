#ifndef FIB_H
#define FIB_H

typedef int Rank; // 定义 Rank 类型，假设它是一个整数类型

class Fib
{
public:
    Fib(int n); // 构造一个能容纳至少n个元素的Fib数列
    ~Fib();

    int get();  // 获取当前Fib数列的最大元素
    int prev(); // 获取前一个Fib数
    int next(); // 获取后一个Fib数
};

#endif // FIB_H
