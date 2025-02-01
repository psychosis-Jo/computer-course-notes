#include <iostream>
#include "List.h" // 假设 List 类定义在 List.h 头文件中

void printList(const List<int> &list)
{
    std::cout << "List content: ";
    for (auto p = list.first(); p != list.last()->succ; p = p->succ)
    {
        std::cout << p->data << " ";
    }
    std::cout << std::endl;
}

int main()
{
    List<int> list;

    // 测试插入操作
    list.insertAsFirst(1);
    list.insertAsLast(2);
    list.insertA(list.first(), 3);
    list.insertB(list.last(), 4);

    // 输出列表内容
    printList(list);

    // 测试排序
    list.sort();

    // 输出排序后的列表内容
    std::cout << "Sorted list content: ";
    printList(list);

    // 测试查找
    int target = 3;
    ListNodePosi(int) result = list.find(target);
    if (result)
    {
        std::cout << "Found " << target << " in the list." << std::endl;
    }
    else
    {
        std::cout << "Did not find " << target << " in the list." << std::endl;
    }

    // 测试去重
    list.insertAsLast(3); // 添加重复元素
    list.insertAsLast(4); // 添加重复元素
    std::cout << "List content before deduplicate: ";
    printList(list);
    list.deduplicate();
    std::cout << "List content after deduplicate: ";
    printList(list);

    // 测试倒置
    list.reverse();
    std::cout << "List content after reverse: ";
    printList(list);

    return 0;
}
