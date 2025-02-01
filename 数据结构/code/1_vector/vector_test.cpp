#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6);
    for (int i : vec)
    {
        std::cout << i << " "; // 1，输出：1 2 3 4 5 6
    }
    std::cout << std::endl;
    vec.pop_back();
    for (int i : vec)
    {
        std::cout << i << " "; // 2，输出：1 2 3 4 5
    }
    std::cout << std::endl;
    auto it = vec.begin() + 2;
    vec.insert(it, 3);
    for (int i : vec)
    {
        std::cout << i << " "; // 3，输出：1 2 3 3 4 5
    }
    std::cout << std::endl;
    vec.erase(it);
    for (int i : vec)
    {
        std::cout << i << " "; // 4，输出：1 2 3 4 5
    }
    std::cout << std::endl;
    vec.clear();
    std::cout << "Vector size after clearing: " << vec.size() << std::endl; // 5，输出：Vector size after clearing: 0
    vec.resize(8, 0);                                                       // 增加到8个元素，新增元素用0填充
    for (int i : vec)
    {
        std::cout << i << " "; // 6，输出：0 0 0 0 0 0 0 0
    }
    std::cout << std::endl;
    return 0;
}