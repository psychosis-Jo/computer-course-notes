#include <cstdlib>

#include "../2_list/list.h" //以List为基类
template <typename T>
class Queue : public List<T> // 队列模板类（继承List原有接口）
{
public:                                           // size()、empty()以及其它开放接口均可直接沿用
    void enqueue(T const &e) { insertAsLast(e); } // 入队：尾部插入
    T dequeue() { return remove(first()); }       // 出队：首部删除
    T &front() { return first()->data; }          // 队首
};

template <typename T>
class RoundRobin // 循环分配器
{
    Queue<clients> Q;        // 参与资源分配的所有客户组成队列Q
    while (!ServiceClosed()) // 在服务关闭之前，反复地
    {
        e = Q.dequeue(); // 队首的客户出队，并
        serve(e);        // 接受服务，然后
        Q.enqueue(e);    // 重新入队
    }
};

struct Customer
{
    int window;
    unsigned int time;
}; // 顾客类：所属窗口（队列）、服务时长

/*
int bestWindow(Queue<Customer> *windows, int nWin)
{
    int minSize = windows[0].size(); // 初始化最小队列长度为第一个窗口的队列长度
    int bestWindowIndex = 0;         // 最佳窗口的索引，默认为第一个窗口
    // 寻找最小队列长度及其对应的窗口索引
    for (int i = 1; i < nWin; i++)
    {
        if (windows[i].size() < minSize)
        {
            minSize = windows[i].size();
            bestWindowIndex = i;
        }
    }
    return bestWindowIndex;
}*/

void simulate(int nWin, int servTime)
{
    Queue<Customer> *windows = new Queue<Customer>[nWin];
    for (int now = 0; now < servTime; now++)
    {
        if (rand() % (1 + nWin))
        {
            Customer c;
            c.time = 1 + rand() % 98;
            c.window = bestWindow(windows, nWin);
            windows[c.window].enqueue(c);
        }
        for (int i = 0; i < nWin; i++)
            if (!windows[i].empty())
                if (--windows[i].front().time <= 0)
                    windows[i].dequeue();
    }
    delete[] windows;
}

int bestWindow(Queue<Customer> windows[], int nWin)
{
    int minSize = windows[0].size(), optiWin = 0;
    for (int i = 1; i < nWin; i++)
    {
        if (minSize > windows[i].size())
        {
            minSize = windows[i].size();
            optiWin = i;
        }
        return optiWin;
    }
}