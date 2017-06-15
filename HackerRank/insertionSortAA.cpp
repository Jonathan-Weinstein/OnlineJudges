#include <iostream>
#include <algorithm>//copy
using namespace std;

enum{N=100000};
#define restrict __restrict__

size_t Merge(const int* left, size_t n, const int* right, const int* const R, int* restrict dest)
{
    for (size_t k=0u;;)//empty ranges aren't passed
    {
        if (*left <= *right)
        {
            *dest++ = *left++;
            if (!--n)
            {
                copy(right, R, dest);
                return k;
            }
        }
        else
        {
            *dest++ = *right++;
            k+=n;//reason second arg isnt an end iterator
            if (right==R)
            {
                copy_n(left, n, dest);
                return k;
            }
        }
    }
}
//identical to normal, but if left range exhausted first, there is nothing to be copied
size_t FinalMerge(const int* left, size_t n, const int* right, const int* const R, int* restrict dest)
{
    for (size_t k=0u;;)//empty ranges aren't passed
    {
        if (*left <= *right)
        {
            *dest++ = *left++;
            if (!--n)
                return k;
        }
        else
        {
            *dest++ = *right++;
            k+=n;//reason second arg isnt an end iterator
            if (right==R)
            {
                copy_n(left, n, dest);
                return k;
            }
        }
    }
}

size_t isort(int* const base, int* const past)
{
    if (past-base <= 1)
        return 0u;

    size_t k=0u;
    for (int *left=base, *sortedEnd=base+1; sortedEnd!=past; left=sortedEnd++)
    {
        if (*left>*sortedEnd)
        {
            const int val=*sortedEnd;
            int* right=sortedEnd;

            do *right=*left;
            while ((right=left)!=base && *--left>val);

            *right=val;
            k+=size_t(sortedEnd-right);
        }
    }
    return k;
}

/* Improved version of classic Merge Sort Algorithm
    -buffer only needs to be of length n/2 instead of entire n
    -merging done with minimal copying
    -starts by sorting small arrays with Insertion Sort, instead of merging single element arrays.
*/
size_t msort(int* data, size_t n, int* buf)
{
    if (n>=24u)
    {
        const size_t half=n>>1u, fourth=n>>2u;
        size_t k=0u;

        k+=msort(data,        fourth,      buf);
        k+=msort(data+fourth, half-fourth, buf);
        k+=msort(data+half,   n-half,      buf);

        k+=Merge(data, fourth, data+fourth, data+half, buf);

        return k+FinalMerge(buf, half, data+half, data+n, data);
    }
    else
        return isort(data, data+n);
}

int main()
{
    static int a[N], buf[N/2];
    unsigned t=0u;
    cin>>t;

    while (t--)
    {
        unsigned n, i=0u;
        cin>>n;

        while (i!=n)
            cin>>a[i++];

        cout<<msort(a, n, buf)<<'\n';
    }

    return 0;
}
