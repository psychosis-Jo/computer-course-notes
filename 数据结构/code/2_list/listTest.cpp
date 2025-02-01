#include <iostream>

struct Node
{
    int data;   // 数据
    Node *next; // 指向下一个节点的指针
};

class LinkedList
{
private:
    Node *head; // 链表头节点指针
public:
    // 创建空链表
    LinkedList() : head(nullptr) {}

    // 在链表末尾插入新节点
    void append(int value)
    {
        Node *newNode = new Node{value, nullptr};
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // 删除指定值的节点
    void remove(int value)
    {
        Node *current = head;
        Node *prev = nullptr;
        while (current != nullptr && current->data != value)
        {
            prev = current;
            current = current->next;
        }
        if (current != nullptr)
        {
            if (prev == nullptr)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current;
        }
    }

    // 遍历链表并打印节点的值
    void printList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};
int main()
{
    LinkedList list;

    // 在链表末尾插入节点
    list.append(1);
    list.append(2);
    list.append(3);

    // 打印链表
    list.printList(); // 输出: 1 2 3

    // 删除节点
    list.remove(2);

    // 再次打印链表
    list.printList(); // 输出: 1 3

    return 0;
}
