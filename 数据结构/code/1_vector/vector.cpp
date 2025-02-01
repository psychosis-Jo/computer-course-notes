// vector.cpp
#include <iostream>
#include <algorithm>
#include "vector.h"

int main()
{
    // 创建一个整型向量
    Vector<int> vec(10, 5, 1); // 容量为10，规模为5，所有元素初始为1

    // 输出向量规模和内容
    std::cout << "Vector size: " << vec.size() << std::endl;
    std::cout << "Vector elements: ";

    // 使用函数指针遍历输出
    void (*printFunc)(int &);
    printFunc = [](int &e)
    { std::cout << e << " "; };
    vec.traverse(printFunc);

    std::cout << std::endl;

    // 在指定位置插入元素
    vec.insert(2, 3);
    std::cout << "Insert 3 at position 2: ";
    vec.traverse(printFunc);
    std::cout << std::endl;

    // 删除指定位置的元素
    vec.remove(4);
    std::cout << "Remove element at position 4: ";
    vec.traverse(printFunc);
    std::cout << std::endl;

    // 对向量进行排序
    vec.sort();
    std::cout << "Sorted vector: ";
    vec.traverse(printFunc);
    std::cout << std::endl;

    return 0;
}
