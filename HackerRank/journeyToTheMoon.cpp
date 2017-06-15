/*
    Journey To The Moon
    https://www.hackerrank.com/challenges/journey-to-the-moon

    Jonathan Weinstein
    last updated December 20, 2016
*/
#include <vector>

struct union_find
{
    std::vector<unsigned> par, cnt;

    union_find(unsigned n)
    : par(n), cnt(n)
    {
        for (unsigned i=0; i!=n; ++i)
        {
            par[i]=i;
            cnt[i]=1;
        }
    }

    unsigned root(unsigned i)
    {
        unsigned next;
        while (i!=(next=par[i])) i=par[i]=par[next];
        return i;
    }

    void join(unsigned p, unsigned q)//make root of smaller tree point to larger tree
    {
        const unsigned rP=root(p), rQ=root(q);
        if (rP!=rQ)//if not already connected
        {
            const unsigned cntP=cnt[rP], cntQ=cnt[rQ];
            if (cntP<cntQ)  { par[rP]=rQ; cnt[rQ]+=cntP; }
            else            { par[rQ]=rP; cnt[rP]+=cntQ; }
        }
    }
//    //following not used in this problem
//    bool is_root(unsigned i)
//    {
//        return root(i)==i;
//    }
//
//    bool connected(unsigned p, unsigned q)
//    {
//        return root(p) == root(q);//need to always do compression?
//    }
//
//    unsigned count(unsigned i)
//    {
//        return cnt[root(i)];
//    }
};

template<class Int>
Int nc2(Int n)//n choose 2
{
    return (n*(n-1))>>1;
}

#include <iostream>
#include <stdint.h>
typedef uint64_t u64;

int main()
{
    using namespace std;
    unsigned n, lines;

    cin>>n>>lines;
    union_find uf(n);

    while (lines--)
    {
        unsigned p, q;
        cin>>p>>q;
        uf.join(p, q);
    }

    u64 total=nc2<u64>(n), same=0;

    for (unsigned i=0; n!=0; ++i)//sub from n the size of each group until all people accounted for
    {
        if (uf.par[i]==i)//if is a root
        {
            const unsigned sz=uf.cnt[i];
            same+=nc2(sz);
            n-=sz;
        }
    }

    cout<<(total-same)<<'\n';
    return 0;
}

#if 0
//Alternative solution that gets the number of groups and their sizes the same method,
//but then figures out the answer a little differently.
//
//Both loops use a similar number of operations, but I think the above way may be better,
//since an iteration does not depend on the previous one.
//Though for this problem, that may not apply since I skip over the non-roots in the sizes array,
//instead of processing all contiguous elements.
int main()
{
    using namespace std;
    unsigned n, lines;

    cin>>n>>lines;
    union_find uf(n);

    while (lines--)
    {
        unsigned p, q;
        cin>>p>>q;
        uf.join(p, q);
    }

    u64 answer=0, sum=0;

    for (unsigned i=0; n!=0; ++i)//sub from n the size of each group until all people accounted for
    {
        if (uf.par[i]==i)//if is a root
        {
            const unsigned sz=uf.cnt[i];
            answer+=sum*sz, sum+=sz //vs: same += (sz*(sz-1))>>1;//then (answer=total-same) after the loop
            n-=sz;
        }
    }

    cout<<answer<<'\n';
    return 0;
}
#endif
