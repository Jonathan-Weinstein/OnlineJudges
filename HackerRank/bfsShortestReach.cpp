/* Breadth First Search: Shortest Reach https://www.hackerrank.com/challenges/bfsshortreach

Given an undirected graph consisting of N nodes (labeled 1 to N) where a specific given node S represents the start position
and an edge between any two nodes is of length 6 units in the graph.

>>>It is required to calculate the shortest distance from start position (Node S) to all of the other nodes in the graph.

Note 1: If a node is unreachable, the distance is assumed as -1.
Note 2: The length of each edge in the graph is 6 units.

Input Format:
The first line contains T,denoting the number of test cases.
First line of each test case has two integers, N denoting the number of nodes in the graph, and M denoting the number of edges in the graph.
The next M lines each consist of two space separated integers X Y, where X and Y denote the two nodes between which the edge exists.
The last line of a test case has an integer S, denoting the starting position.

Constraints:
1<=T<=10
2<=N<=1000
1<=M<=N*(N-1)/2
1<=x,y,s<=N

Output Format:
For each of  test cases, print a single line consisting of N-1 space-separated integers,
denoting the shortest distances of the N-1 nodes from starting position S.
This will be done for all nodes same as in the order of input 1 to N.
For unreachable nodes, print -1.

Sample Input:
2
4 2
1 2
1 3
1
3 1
2 3
2

Sample Output:
6 6 -1
-1 6

*/
#include <stdio.h>
#include <algorithm>//fill_n
#include <memory>
using namespace std;

struct node
{
    int id;
    node* next;
};

struct ilist
{
    node* head=nullptr;

    void prepend(node* nptr)
    {
        node* const old=head;
        head=nptr;
        head->next=old;
    }
};

void bfs(const ilist *const adj, int *const dist, int pred, int *last)//pred starts as source id, last points to an array of size MaxNodes-1
{
    const int *first=last;
    dist[pred]=0;

    for (;; pred=*first++)//dequeue
    {
        for (const node* j=adj[pred].head; j!=nullptr; j=j->next)
        {
            const int child=j->id;

            if (dist[child] == -1)//no need to track parents and construct a tree for this problem
            {
                dist[child] = dist[pred]+6;
                *last++ = child;//enqueue
            }
        }

        if (first==last)//queue empty
            break;
    }
}

void print(int* dist, int s, int verts)
{
    for (int i=1; i<s; ++i)
        printf("%d ", dist[i]);

    for (int i=s+1; i<=verts; ++i)
        printf("%d ", dist[i]);

    putchar('\n');
}

enum { MaxNodes=1000 };

int main()
{
    static ilist adj[MaxNodes+1];//node id's are one based, I'll waste some space at the beginning instead of doing conversions
    static int dist[MaxNodes+1];
    static int qbuf[MaxNodes-1];//a node will only be enqueued if it hasnt been seen. maybe should just use deque<int>, but this is not much space

    size_t capacity=4096;
    unique_ptr<node[]> pool(new node[4096]);

    int t;
    scanf("%d", &t);

    while (t--)
    {
        int verts, edges;
        scanf("%d%d", &verts, &edges);

        fill_n(adj+1, verts, ilist{});
        fill_n(dist+1, verts, -1);

        const size_t needed=edges*2;
        if (capacity<needed)
            pool.reset(new node[capacity=needed]);

        for (node* p=pool.get(); edges--; )//populate the adjacency lists
        {
            int x, y;
            scanf("%d%d", &x, &y);

            p->id=y;
            adj[x].prepend(p++);

            p->id=x;
            adj[y].prepend(p++);
        }

        int srcId;
        scanf("%d", &srcId);

        bfs(adj, dist, srcId, qbuf);
        print(dist, srcId, verts);
    }

    return 0;
}
