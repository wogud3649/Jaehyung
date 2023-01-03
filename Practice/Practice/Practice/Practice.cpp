#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    Edge(int u, int v, int cost) :u(u), v(v), cost(cost) {}
    int cost;
    int u;
    int v;
};

int main()
{
    int n = 4;
    vector<vector<int>> costs = { {0,1,1},
                                  {0,2,2},
                                  {1,2,5},
                                  {1,3,1},
                                  {2,3,8} };
    vector<bool> discovered(n, false);

    vector<Edge> edges;

    for (int i = 0; i < costs.size(); i++)
    {
        edges.push_back(Edge(costs[i][0], costs[i][1], costs[i][2]));
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b)->bool
        {
            return a.cost < b.cost;
        });

    return 0;
}