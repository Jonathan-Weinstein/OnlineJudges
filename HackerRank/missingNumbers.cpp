#include <stdio.h>
#include <stddef.h>

#include <iostream>
using namespace std;

int main()
{
    int baseA[201]={}, baseB[201]={}, *const offA=baseA+100, *const offB=baseB+100;
    size_t n;
    ptrdiff_t f;//first read

    cin>>n;
    cin>>f;//a number could be at most 100 more than f, or at least 100 less than
    --n;
    ++offA[0];

    while (n--)
    {
        ptrdiff_t val;
        cin>>val;
        ++offA[val-f];
    }

    cin>>n;
    while (n--)
    {
        ptrdiff_t val;
        cin>>val;
        ++offB[val-f];
    }

    for (int i=0; i!=201; ++i)
    {
        if (baseA[i]!=baseB[i])
            cout<<(f+i-100)<<'\n';
    }

    return 0;
}
