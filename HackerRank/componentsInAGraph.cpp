#include <stdio.h>
#include <vector>

struct union_find
{
    std::vector<unsigned> parent, cnt;

    union_find(unsigned n)
    : parent(n), cnt(n, 1u)
    {
        unsigned i=0u;//this simplifies the path compression instead of having a sentinel value
        for (unsigned& r : parent)
            r=i++;
    }

    unsigned root(unsigned cur)
    {
        while (cur!=parent[cur]) cur=parent[cur]=parent[parent[cur]];
        return cur;
    }

    bool connected(unsigned p, unsigned q)
    {
        return root(p) == root(q);
    }

    void join(unsigned p, unsigned q)//make root of smaller tree point to larger tree
    {
        const unsigned rP=root(p), rQ=root(q);
        if (rP!=rQ)//if not already connected
        {
            const unsigned cntP=cnt[rP], cntQ=cnt[rQ];
            if (cntP<cntQ)  { parent[rP]=rQ; cnt[rQ]+=cntP; }
            else            { parent[rQ]=rP; cnt[rP]+=cntQ; }
        }
    }
};

int main()
{
    unsigned lines;
    scanf("%u", &lines);
    union_find uf(lines*2 + 1);

    while (lines--)
    {
        unsigned p, q;
        scanf("%u%u", &p, &q);
        uf.join(p, q);
    }

    unsigned i=0u, min=0u, max=0u;//note:
    const unsigned n=uf.cnt.size();

    for ( ; i!=n; ++i)//note:
    {
        if (i==uf.parent[i] && uf.cnt[i]>1u)//if is a root, and not considering lone nodes in this problem
        {
            min=max=uf.cnt[i++];
            break;
        }
    }

    for ( ; i!=n; ++i)
    {
        const unsigned count=uf.cnt[i];
        if (i==uf.parent[i] && count>1u)
        {
            if (count>max) max=count;
            else if (count<min) min=count;
        }
    }

    printf("%u %u\n", min, max);
    return 0;
}
