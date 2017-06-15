///https://www.hackerrank.com/challenges/find-the-running-median
/*
    Starting from zero to N elements print the median after every insert.

    -State used in solution-
    left: a max heap of all <= median
    right: a min heap of all >= median

    -Algorithm-
    Adding a new element makes total count odd:
        if new <= previous median (avg of both tops)
            insert new to left
            output left top
            goto A
        else
            insert new to right
            output right top
            goto B
    Then adding another will make even:
    A:
        if new < left top (previous median)
            insert left top to right
            demote left top to new
        else
            insert new to right

        goto OutPutEvenCount
    B:
        if new > right top (previous median)
            insert right top to left
            demote right top to new
        else
            insert new to left
    OutPutEvenCount:
        output average of left top and right top
        repeat
*/
#include <stdio.h>
#include <limits.h>
//could use count array instead, but how to skip over empty cells to next element on left or right?
enum
{
    MaxN=100000
};

struct Less
{
    static bool xthan(int a, int b){return a<b;}
    enum:int{lhs_false_sentinel=INT_MAX};
};

struct Greater
{
    static bool xthan(int a, int b){return a>b;}
    enum:int{lhs_false_sentinel=INT_MIN};
};

template<class C>
struct sheap
{
    static
    void promote(int *const a, size_t j, int const val)
    {
        for (size_t parent=j>>1; C::xthan(a[parent], val); parent>>=1)
        {
            a[j]=a[parent];
            j=parent;
        }

        a[j]=val;
    }

    static
    void demote(int *const a, size_t i, int const val, size_t const sz)
    {
        size_t child=i<<1;//left

        while (child<sz)//if has both children
        {
            if (C::xthan(a[child], a[child+1]))//get pos of higher priority
                ++child;

            a[i]=a[child];
            i=child;
            child<<=1;//left
        }
        //if has a single left child
        if (child==sz && C::xthan(val, a[sz]))
        {
            a[i]=a[sz];
            i=sz;
        }

        promote(a, i, val);
    }
};

template<typename C>
class SentinelHeap
{
    size_t sz;
    int *sntnl;
public:
    typedef C compare_t;
    SentinelHeap(int *s) : sz(0), sntnl(s)
    {
        *s=C::lhs_false_sentinel;
    }
    int top()const{return sntnl[1];}
    size_t size()const{return sz;}
    void insert(int val){ sheap<C>::promote(sntnl, ++sz, val);     }
    void demote(int val){ sheap<C>::demote( sntnl,    1, val, sz); }
};

using MaxSentinelHeap = SentinelHeap<Less>;//consistent with std, because sorting the heap would result in ascending
using MinSentinelHeap = SentinelHeap<Greater>;

template<class A, class B>
void do_case(SentinelHeap<A>& a, SentinelHeap<B>& b, int val)
{
    int prev;
    a.insert(val);
    printf("%d.0\n", prev=a.top());

    scanf("%d", &val);
    if (A::xthan(val, prev))
    {
        b.insert(prev);
        a.demote(val);
    }
    else
    {
        b.insert(val);
    }
}

int main()
{
    enum{PerCap = (MaxN/2)+2 };
    static int lbuf[PerCap];
    static int rbuf[PerCap];

    MaxSentinelHeap lefthp(lbuf);
    MinSentinelHeap righthp(rbuf);

    int n=0, prev=INT_MAX, val;
    if (scanf("%d", &n), n<=0)
        return 1;
    //process an odd then even median for each trip
    for (int trips=n>>1; trips!=0; --trips)
    {
        if (scanf("%d", &val), val<prev)
            do_case(lefthp, righthp, val);
        else
            do_case(righthp, lefthp, val);

        const int twice=lefthp.top()+righthp.top();
        printf("%d.", prev=(twice>>1));
        puts(twice&1 ? "5" : "0");
    }

    if (n&1)
    {
        if (scanf("%d", &val), val<=prev)//<= b/c of possible rounding down
        {
            if (val<lefthp.top())
                val=lefthp.top();
        }
        else
        {
            if (val>lefthp.top())
                val=righthp.top();
        }

        printf("%d.0\n", val);
    }

    return 0;
}
