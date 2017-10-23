/*
    description is misleading,
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum{N=100000};//100k

int gSum;
int gAbs;

struct node
{
    node* next;//could use index
    int childId;
};

struct islist
{
    node* head;

    void prepend(node* newHead)
    {
        newHead->next=head;
        head=newHead;
    }
};

int dfs(const islist* adj, short* data, int id)
{
    int sum=data[id];
    data[id]=0;//mark as visited
    for (const node* p=adj[id].head; p!=nullptr; p=p->next)
    {
        id=p->childId;
        if (data[id])
        {
            const int childSum = dfs(adj, data, id);
            const int absDiff  = abs(gSum-childSum-childSum);
            if (absDiff<gAbs) gAbs=absDiff;
            sum+=childSum;
        }
    }
    return sum;
}

int answer(const islist* adj, short* data)
{
    gAbs=INT_MAX;
    dfs(adj, data, 1);//can start anywhere
    return gAbs;
}

int main()
{
    static node pool[N*2];
    static islist alist[N+1];//all set to nullptr
    static short data[N+1];

    int n, sum=0;
    scanf("%d", &n);

    for (int i=1; i!=n+1; ++i)
    {
        int val;
        scanf("%d", &val);
        sum+=val;
        data[i]=val;
    }
    gSum=sum;

    node* p=pool;
    for (int edges=n-1; edges--; )
    {
        int x, y;//not in any sort of order... so I need both ways
        scanf("%d%d", &x, &y);

        p->childId=x;
        alist[y].prepend(p++);

        p->childId=y;
        alist[x].prepend(p++);
    }

    printf("%d\n", answer(alist, data));
    return 0;
}

