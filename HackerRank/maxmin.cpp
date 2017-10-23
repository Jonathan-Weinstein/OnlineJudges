#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

int answer(const int* lo, const int* e, int k)//2<=k<=n
{
    int mindist=INT_MAX;

    for (const int* hi=lo+k-1; hi!=e; ++lo, ++hi)
    {
        const int d=*hi-*lo;
        if (d<mindist)
            mindist=d;
    }

    return mindist;
}

int main()
{
    static int buf[100000];
    int n, k;
    cin>>n>>k;

    int* const e=buf+n;
    for (int* b=buf; b!=e; ++b) cin>>*b;
    sort(buf, e);

    cout<<answer(buf, e, k)<<'\n';
    return 0;
}
