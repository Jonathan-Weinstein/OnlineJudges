#include <iostream>
using namespace std;

typedef unsigned cookie;

namespace heap1///1-indexed min heap routines
{
    void promote(cookie *const a, size_t j, const cookie val);
    void demote(cookie *const a, size_t i, size_t n, const cookie val);
    void create(cookie *const a, size_t n);
}

int answer(cookie *const jar, size_t n, const cookie k)
{
    using namespace heap1;
    int ops=0;
    create(jar, n);

    for ( ; *jar<k && n>=3; ++ops)//perhaps can be done with less work on heap
    {
        const size_t small = jar[1]<jar[2] ? 1 : 2;//get 2nd smallest item index
        //remove 2nd smallest item
        const cookie back=jar[--n], mix=*jar+(jar[small]<<1u);
        demote(jar, small, n, back);
        //exchange top with mixed and fix heap
        demote(jar, 0, n, mix);
    }

    if (*jar>=k)
        return ops;
    else if (n==2 && *jar+(jar[1]<<1u)>=k)
        return ops+1;
    else
        return -1;
}

int main()
{
    size_t n;//n>=1
    cookie k;
    cin>>n>>k;

    cookie *const jar=new cookie[n+1];
    *jar=0u;//sentinel for promote
    for (cookie *b=jar+1, *const e=jar+n+1; b!=e; ++b)
        cin>>*b;

    cout<<answer(jar, n, k)<<'\n';

    delete[]jar;
    return 0;
}

/** 1-indexed min heap routines
 *
 * by higher priority I mean values that should be closer to the root of the heap
 *
 * the 1 based indexing allows for a bit simpler parent and child index calcs, and allows for a sentinel
 * at a[0], which is expected to be there before calling promote
 */
namespace heap1
{
    /* promote

        val: new value to be exchanged with value at index i

        brings slot up while bringing other items down, then assigns val
    */
    void promote(cookie *const a, size_t j, const cookie val)
    {
        for (size_t parent=j>>1; a[parent]>val; parent>>=1)
        {
            a[j]=a[parent];
            j=parent;
        }

        a[j]=val;
    }

    /* demote

        val: new value to be exchanged with value at index i.

        Instead of trying to place the new value near the top and bringing it down
        while bringing other values up until the heap property would be satisfied, which
        does 2 comparisons per level, instead the other values are just brought up first, doing just 1 comparison per level.
        Then the new value is placed by promoting it from the bottom.

        This is favorable when the new value should belong close to the bottom of the heap,
        where it won't have to rise much. When an element from the heap is 'removed,' the topmost element is
        replaced with the last leaf, which will likely end up near the bottom again, so it wont have to rise much.
    */
    void demote(cookie *const a, size_t i, const size_t size, const cookie val)
    {
        size_t child=i<<1;//left

        while (child<size)//if has both children
        {
            if (a[child] > a[child+1])
                ++child;

            a[i]=a[child];
            i=child;
            child<<=1;//left
        }
        //if has a single left child
        if (child==size && val>a[size])
        {
            a[i]=a[size];
            i=size;
        }

        promote(a, i, val);
    }

    /* create

        turns the array into a min heap using the bottom-up approach,
        instead of promoting each element from 2 to n inclusive
    */
    void create(cookie *const a, const size_t n)
    {
        for (size_t j=n>>1; j>1; --j)
            demote(a, j, n, a[j]);//bottom up heap method doesn't make sense here
    }
}//namespace heap1

#if 0//old func, zero indexed
/* demote

    val: new value to be exchanged with value at index i.

    sifts new value down to a proper place to restore heap property,
    while bringing the higher-priority children up
*/
void heap_demote(cookie *const a, size_t i, const size_t size, const cookie val)
{
    size_t child=i*2 + 2;//right

    while (child<size)//if has both children
    {
        if (a[child] > a[child+1])
            --child;

        if (val > a[child])//second comparison
        {
            a[i]=a[child];
            i=child;
            child=i*2 + 2;//right
        }
        else
        {
            a[i]=val;
            return;
        }
    }
    //if has a single left child
    if (child==size && val>a[child-1])
    {
        a[i]=a[child-1];
        a[child-1]=val;
    }
    else
        a[i]=val;
}
#endif
