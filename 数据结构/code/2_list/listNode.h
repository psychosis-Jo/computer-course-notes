#ifndef LISTNODE_H
#define LISTNODE_H

typedef int Rank;                     // 秩
#define ListNodePosi(T) ListNode<T> * // 列表节点位置

template <typename T>
struct ListNode // 列表节点模板类（以双向链表形式实现）
{
    // 成员
    T data;               // 数据
    ListNodePosi(T) pred; // 前驱
    ListNodePosi(T) succ; // 后继

    // 构造函数
    ListNode() {}                                                                                    // 针对header和trailer的构造
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) : data(e), pred(p), succ(s) {} // 默认构造器

    // 操作接口
    // 紧靠当前节点之前插入新节点
    ListNodePosi(T) insertAsPred(T const &e);
    // 紧靠当前节点之后插入新节点
    ListNodePosi(T) insertAsSucc(T const &e);
};

// 在当前节点之前插入新节点
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const &e)
{
    ListNodePosi(T) newNode = new ListNode(e, pred, this); // 创建新节点
    pred->succ = newNode;                                  // 更新前驱的后继为新节点
    pred = newNode;                                        // 更新前驱为新节点
    return newNode;                                        // 返回新节点位置
}

// 在当前节点之后插入新节点
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e)
{
    ListNodePosi(T) newNode = new ListNode(e, this, succ); // 创建新节点
    succ->pred = newNode;                                  // 更新后继的前驱为新节点
    succ = newNode;                                        // 更新后继为新节点
    return newNode;                                        // 返回新节点位置
}

#endif
