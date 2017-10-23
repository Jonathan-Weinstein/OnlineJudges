/*
    Even Tree
    https://www.hackerrank.com/challenges/even-tree

    Solution by Jonathan Weinstein.

    Explanation:
    If a subtree has an odd number of total descendants,
    than it can be removed, since it then has an even node count.
*/

#include <stdio.h>

typedef unsigned char byte;//only the parity of a node's descendants is needed, instead of the full count
enum{N=100};

unsigned sum(const byte *b, const byte *const e)
{
    unsigned ret=0u;
    while (b!=e) ret+=*b++;
    return ret;
}

int main()
{
    byte odd[N+1]={0};//holds 1 if has an odd number of total descendants, else 0
    int parentOf[N+1];//node ids start at 1
    int nodes, edges;

    parentOf[1]=0;//sentinel, node id 1 is root
    scanf("%d%*d", &nodes);//number nodes of nodes always even and >=2
    edges=nodes-1;

    while (edges--)
    {
        int child, parent;
        scanf("%d%d", &child, &parent);

        parentOf[child]=parent;

        do odd[parent]^=1u;
        while ((parent=parentOf[parent])!=0);
    }

    printf("%u\n", sum(odd+2, odd+nodes+1));//skipping root(no link above to cut), and 1-based indexing
    return 0;
}
