/*
    https://www.hackerrank.com/challenges/hackerland-radio-transmitters
*/

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

const int* find_greater(const int* it, int val)
{
    while (*it<=val) ++it;
    return it;
}

int houses(const int* left, int r)
{
    int cnt=0;

    for (;;)
    {
        const int *right=find_greater(left, *left+r);
        ++cnt;
        if (*right==INT_MAX) break;
        left=find_greater(right, right[-1]+r);
        if (*left==INT_MAX) break;
    }

    return cnt;
}

int main()
{
    int n, r;
    cin>>n>>r;

    int *const v=new int[n+1], *const sent=v+n;
    for (int *it=v; it!=sent; ++it) cin>>*it;//may contain duplicates
    *sent=INT_MAX;
    sort(v, sent);

    cout<<houses(v, r)<<'\n';

    delete[]v;
    return 0;
}
