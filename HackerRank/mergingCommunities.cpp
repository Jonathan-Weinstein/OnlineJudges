#include <vector>

class union_find
{
protected:
    std::vector<unsigned> parent, cnt;

    unsigned RootCompress(unsigned cur)
    {
        unsigned next;
        while (cur!=(next=parent[cur])) cur=parent[cur]=parent[next];
        return cur;
    }
public:
    union_find(unsigned n)
    : parent(n), cnt(n, 1u)
    {
        unsigned i=0u;//this simplifies the path compression instead of having a sentinel value
        for (unsigned& r : parent)
            r=i++;
    }

    unsigned root(unsigned i) const//no compression here, only needed in join(), not connected()
    {
        unsigned next;
        while (i!=(next=parent[i])) i=next;
        return i;
    }

    bool connected(unsigned p, unsigned q) const
    {
        return root(p) == root(q);
    }

    unsigned count(unsigned i) const
    {
        return cnt[root(i)];
    }

    void join(unsigned p, unsigned q)//make root of smaller tree point to larger tree
    {
        const unsigned rP=RootCompress(p), rQ=RootCompress(q);
        if (rP!=rQ)//if not already connected
        {
            const unsigned cntP=cnt[rP], cntQ=cnt[rQ];
            if (cntP<cntQ)  { parent[rP]=rQ; cnt[rQ]+=cntP; }
            else            { parent[rQ]=rP; cnt[rP]+=cntQ; }
        }
    }
};

#include <stdio.h>

int main()
{
    unsigned i, j, n=0u, queries=0u;
    scanf("%u%u ", &n, &queries);
    union_find uf(n+1u);

    while (queries--)
    {
        if (getchar()=='M')
        {
            scanf("%u%u ", &i, &j);
            uf.join(i, j);
        }
        else
        {
            scanf("%u ", &i);
            printf("%u\n", uf.count(i));
        }
    }

    return 0;
}
