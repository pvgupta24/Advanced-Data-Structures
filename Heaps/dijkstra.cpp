#include <bits/stdc++.h>
#include "includes/BinaryHeap.h"
#include "includes/FibonacciHeap.h"
#include "includes/BinomialHeap.h"

using namespace std;

enum {
    BINARY_HEAP,
    FIBONACCI_HEAP,
    BINOMIAL_HEAP
};

// Heap to be used for the priority queue
// #define HEAP_TYPE BINARY_HEAP
#define HEAP_TYPE FIBONACCI_HEAP
// #define HEAP_TYPE BINOMIAL_HEAP

const string heap_name[] = {"Binary Heap ", "Fibonnaci Heap ", "Binomial Heap"};

int insert_ops = 0, extract_min_ops = 0;

vector<int> shortestReach(int n, int e, vector<vector<int> > &edges, int s)
{
    vector<set<pair<int, int> > > g(n + 1);
    int u, v, w;

    // Makes adjacency matrix with 1 based indexing
    for (int i = 0; i < e; i++)
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
        case FIBONACCI_HEAP:
            priority_queue = new FibonacciHeap<pair<int, int>>();
            break;
        case BINOMIAL_HEAP:
            priority_queue = new BinomialHeap<pair<int, int>>();
            break;
    }

    for (int i = 1; i <= n; i++)
    {
        priority_queue->insert({INF, i});
        ++insert_ops;
    }

    vector<int> darr(n + 1, INF);
    darr[s] = 0; // source vertex dist is zero
    vector<bool> visited(n + 1, false);
    priority_queue->insert({0, s});
    ++insert_ops;
    int count = 0;
    while (count<n)
    {
        int u = priority_queue->get_min().second;
        priority_queue->extract_min();
        ++extract_min_ops;
        if(visited[u]) continue;
        visited[u] = true;
        ++count;
        for (auto x : g[u])
        {
            if(visited[x.first]) continue;
            int v = x.first;
            int weight = x.second;

            if (darr[v] > darr[u] + weight)
            {
                // Updating distance of v
                // int tmp = darr[v];
                darr[v] = darr[u] + weight;
                ++insert_ops;
                priority_queue->insert({darr[v], v});
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
        else
            ans.push_back(0);
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
        
        if(edges[i][2] < 0) 
        {
            cout << "\nERROR: Negative edge\n";
            return 0;
        }
    }

    int s;
    cin >> s;

    clock_t begin = clock();
    vector<int> result = shortestReach(vertex_count, edge_count, edges, s);
    clock_t end = clock();

    cout << "Time Taken with " << heap_name[HEAP_TYPE] << " " << 1.0 * (end - begin) / CLOCKS_PER_SEC << " seconds" << endl;

    cout << "Insert operations: " << insert_ops << endl << "Extract minimum operations: " << extract_min_ops << endl;

    for (uint i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }

    cout << "\n";

    return 0;
}

/*
9 14
1 2 4 
1 8 8
2 3 8 
2 8 11 
3 4 7 
3 9 2 
3 6 4 
4 5 9 
4 6 14 
5 6 10 
6 7 2 
7 8 1 
7 9 6 
8 9 7 
1
*/
