#include <iostream>
#include <limits.h>
using namespace std;

int main()
{
    static int idx[100001]={};//for any array element a, 1<=a<=1e5.

    int n, minimum=INT_MAX;
    cin>>n;

    for (int i=1; i<=n; ++i)//using one-based indexing so can compare against zero if not seen.
    {
        int a;
        cin>>a;

        const int prevIdx = idx[a];
        const int dist = i-prevIdx;

        if (prevIdx!=0 && dist<minimum)
            minimum=dist;

        idx[a]=i;
    }

    if (minimum==INT_MAX)
        cout<<"-1\n";
    else
        cout<<minimum<<'\n';

    return 0;
}
