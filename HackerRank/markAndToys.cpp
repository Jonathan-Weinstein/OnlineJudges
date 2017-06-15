#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

int answer(const int* b, int k)
{
    const int* const base=b;

    while (k>=*b)//array size is 1 more than needed with intmax planted
         k -= *b++;

    return b-base;
}

int main()
{
    int n, k;
    cin>>n>>k;

    int *const v=new int[n+1], *const sent=v+n;
    for (int *b=v; b!=sent; ++b) cin >> *b;
    *sent=INT_MAX;
    sort(v, sent);

    cout<<answer(v, k)<<'\n';
    delete[]v;
    return 0;
}
