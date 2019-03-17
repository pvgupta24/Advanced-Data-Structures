#include <bits/stdc++.h>
#include "includes/BinaryHeap.h"

using namespace std;

#define BINARY_HEAP 0
#define FIBONNACI_HEAP 1

// Heap to be used for the priority queue
#define HEAP_TYPE BINARY_HEAP

const string heap_name[] = {"Binary Heap ", "Fibonnaci Heap "};

vector<int> shortestReach(int n, vector<vector<int>> edges, int s)
{
    vector<set<pair<int, int>>> g(n + 1);
    int test1 = edges.size();
    int u, v, w;
    for (int i = 0; i < test1; i++)
    {
        u = edges[i][0];
        v = edges[i][1];
        w = edges[i][2];
        g[u].insert({v, w});
        g[v].insert({u, w});
    }

    Heap<pair<int, int>> *priority_queue;

    switch (HEAP_TYPE)
    {
        case BINARY_HEAP:
            priority_queue = new BinaryHeap<pair<int, int>>();
            break;
    }

    for (int i = 1; i <= n; i++)
    {
        priority_queue->insert({INF, i});
    }

    vector<int> darr(n + 1, INF);
    darr[s] = 0; // source vertex dist is zero
    priority_queue->decrease_key({INF, s}, {0, s});

    while (priority_queue->getNodeCount())
    {
        int u = priority_queue->get_min().second;
        priority_queue->extract_min();

        for (auto x : g[u])
        {
            int v = x.first;
            int weight = x.second;

            if (darr[v] > darr[u] + weight)
            {
                // Updating distance of v
                int tmp = darr[v];
                darr[v] = darr[u] + weight;
                priority_queue->decrease_key({tmp, v}, {darr[v], v});
            }
        }
    }
    vector<int> ans;
    for (int i = 1; i <= n; ++i)
    {
        if (i != s && darr[i] != INF)
            ans.push_back(darr[i]);
        else if (i != s)
            ans.push_back(-1);
    }
    return ans;
}

int main()
{
    int vertex_count, edge_count;
    cin >> vertex_count >> edge_count;

    vector<vector<int>> edges(edge_count);

    for (int i = 0; i < edge_count; i++)
    {
        edges[i] = vector<int>(3);
        for (int j = 0; j < 3; j++)
        {
            cin >> edges[i][j];
        }
    }

    int s;
    cin >> s;

    clock_t begin = clock();
    vector<int> result = shortestReach(vertex_count, edges, s);
    clock_t end = clock();

    cout << "Time Taken with " << heap_name[HEAP_TYPE] << 1.0 * (end - begin) / CLOCKS_PER_SEC << "seconds" << endl;

    for (uint i = 0; i < result.size(); i++)
    {
        cout << result[i];

        if (i != result.size() - 1)
        {
            cout << " ";
        }
    }

    cout << "\n";

    return 0;
}
