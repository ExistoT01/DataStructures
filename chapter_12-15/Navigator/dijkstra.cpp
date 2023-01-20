#include "dijkstra.h"

Dijkstra::Dijkstra()
{
    this->n = 12;
    this->adjMatrix = {
        {0, 1, 3},
        {0, 4, 3},
        {4, 2, 4},
        {4, 3, 2},
        {4, 6, 2},
        {1, 2, 1},
        {2, 3, 1},
        {3, 6, 4},
        {2, 5, 7},
        {3, 5, 3},
        {6, 8 ,2},
        {8, 7, 3},
        {7, 9 ,2},
        {9, 10, 2},
        {8, 10, 6},
        {5, 10 ,7},
        {5, 11, 8},
        {10, 11, 3}
    };
}

int Dijkstra::dij(int start, int end, vector<int> &pre) {
    graph.resize(n);
    for(auto mat: adjMatrix){
        int from = mat[0], to = mat[1], dist = mat[2];
        graph[from].push_back(pair<int, int>(dist, to));
        graph[to].emplace_back(pair<int, int>(dist, from));
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> q;

    vector<int> dis(n, inf);
    dis[start] = 0;

    q.emplace(0, start);
    pre[start] = start;

    while(!q.empty()){
        auto cur = q.top();
        q.pop();

        int x = cur.second, dist = cur.first;

//        if(dist > dis[x])break;

        for(auto to: graph[x]){
            int y = to.second, d = to.first + dist;
            if(d < dis[y]){
                dis[y] = d;
                q.emplace(d, y);
                pre[y] = x;
            }
        }

    }
    return dis[end];
}
