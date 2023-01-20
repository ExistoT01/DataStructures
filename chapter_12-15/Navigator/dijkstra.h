#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <iostream>
#include <vector>
#include <queue>
#include <QPair>
#include <stack>
using namespace std;


class Dijkstra
{
private:
    vector<vector<pair<int, int>>> graph;
    vector<vector<int>> adjMatrix;

    const int inf = INT_MAX/2;
//    enum location {南区宿舍, 图书馆, 信南, 信北, 行远楼, 五子顶, 二五广场, 北操, 体育馆, 北区宿舍, 东操, 东区宿舍};

public:
    Dijkstra();

    int n; // num of nodes

    int dij(int start, int end, vector<int>& pre);
};

#endif // DIJKSTRA_H
