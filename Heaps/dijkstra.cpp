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
#define HEAP_TYPE BINOMIAL_HEAP

const string heap_name[] = {"Binary Heap ", "Fibonnaci Heap ", "Binomial Heap"};

vector<int> shortestReach(int n, vector<vector<int> > edges, int s)
{
    vector<set<pair<int, int> > > g(n + 1);
    int test1 = edges.size();
    int u, v, w;
    for (int i = 0; i < test1; i++)
    {
        u = edges[i][0];
        v = edges[i][1];
        w = edges[i][2];
        // cout<< u << v << w << "<-\n";
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
    }

    vector<int> darr(n + 1, INF);
    darr[s] = 0; // source vertex dist is zero
    // priority_queue->decrease_key({INF, s}, {0, s});
    vector<bool> visited(n + 1, false);
    // visited[s] = true;
    priority_queue->insert({0, s});
    cout<<s<<"----\n";
    int count = 0;
    while (count<n)
    {
        int u = priority_queue->get_min().second;
        
        cout<< u << "<-\n";
        priority_queue->extract_min();

        if(visited[u]) continue;
        visited[u] = true;
        ++count;
        
        for (auto x : g[u])
        {
            if(visited[x.first]) continue;
            cout<< " " << x.first << "<--\n";    
            int v = x.first;
            int weight = x.second;

            if (darr[v] > darr[u] + weight)
            {
                // Updating distance of v
                int tmp = darr[v];
                darr[v] = darr[u] + weight;
                // priority_queue->decrease_key({tmp, v}, {darr[v], v});
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
            if(j!=2) ++edges[i][j];
        }
    }

    int s;
    cin >> s;
    ++s;

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
/*
9 14
0 1 4 
0 7 8
1 2 8 
1 7 11 
2 3 7 
2 8 2 
2 5 4 
3 4 9 
3 5 14 
4 5 10 
5 6 2 
6 7 1 
6 8 6 
7 8 7 
0
*/
