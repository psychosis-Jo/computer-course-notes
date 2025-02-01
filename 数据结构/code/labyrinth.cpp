#include <iostream>
#include <stack>

const int LABY_MAX = 5;

enum Status
{
    AVAILABLE, // 可通行
    ROUTE,     // 路径
    WALL       // 墙
};

struct Cell
{
    int x, y;
    Status status;
};
// 判断格点是否可通行
bool passable(Cell laby[LABY_MAX][LABY_MAX], int x, int y)
{
    if (x < 0 || x >= LABY_MAX || y < 0 || y >= LABY_MAX || laby[x][y].status != AVAILABLE)
    {
        return false;
    }
    return true;
}
// 迷宫寻径算法
bool labyrinth(Cell laby[LABY_MAX][LABY_MAX], int startX, int startY, int endX, int endY)
{
    std::stack<Cell *> pathStack;
    pathStack.push(&laby[startX][startY]); // 将起点入栈

    while (!pathStack.empty())
    {
        Cell *current = pathStack.top(); // 获取栈顶格点

        if (current->x == endX && current->y == endY) // 如果当前格点为终点
        {
            std::cout << "Path found:" << std::endl; // 输出找到的路径
            while (!pathStack.empty())
            {
                Cell *cell = pathStack.top();
                std::cout << "(" << cell->x << ", " << cell->y << ") ";
                cell->status = ROUTE; // 标记路径上的格点
                pathStack.pop();      // 弹出格点
            }
            std::cout << std::endl;
            return true;
        }

        current->status = ROUTE; // 标记当前格点为已访问
        // 尝试向四个方向探索
        if (passable(laby, current->x + 1, current->y))
        {
            pathStack.push(&laby[current->x + 1][current->y]);
        }
        else if (passable(laby, current->x, current->y + 1))
        {
            pathStack.push(&laby[current->x][current->y + 1]);
        }
        else if (passable(laby, current->x - 1, current->y))
        {
            pathStack.push(&laby[current->x - 1][current->y]);
        }
        else if (passable(laby, current->x, current->y - 1))
        {
            pathStack.push(&laby[current->x][current->y - 1]);
        }
        else
        {
            current->status = WALL; // 如果周围没有可探索的相邻格点，则标记为墙
            pathStack.pop();        // 回溯，弹出当前格点
        }
    }

    std::cout << "No path found." << std::endl;
    return false;
}

int main()
{
    Cell laby[LABY_MAX][LABY_MAX];

    // 初始化迷宫，设置起点和绂点位置，标记墙等
    for (int i = 0; i < LABY_MAX; ++i)
    {
        for (int j = 0; j < LABY_MAX; ++j)
        {
            laby[i][j].x = i;
            laby[i][j].y = j;
            laby[i][j].status = AVAILABLE;
        }
    }

    laby[1][1].status = WALL;
    laby[2][0].status = WALL;
    laby[3][1].status = WALL;

    bool pathExists = labyrinth(laby, 0, 0, 4, 4); // 调用迷宫寻径算法
    // 输出结果
    if (pathExists)
    {
        std::cout << "Path found!" << std::endl;
    }
    else
    {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}
