/* Sherlock and MiniMax https://www.hackerrank.com/challenges/sherlock-and-minimax


*/
#include <algorithm>//sort
using namespace std;
#include <stdio.h>

typedef const int *iter;

int most_remote(iter const base, iter const past, int pos, const int hi)
{
    if (base==past) return pos;
    iter it=lower_bound(base, past, pos);
    int maxdist;

    if (it==past)
        return hi;
    else if (it==base)
        maxdist = ((*it++ - pos)*2)|1;
    else
    {
        const int d = *it-it[-1], m = (it[-1] + d/2);
        maxdist = (m>=pos ? (pos=m, d) : (*it++ - pos)*2)|1;
    }

    for (int left=it[-1]; it!=past; left=*it++)
    {
        const int dist = *it-left;

        if (dist>maxdist)
        {
            const int mid = left+dist/2;

            if (mid<=hi)
            {
                maxdist=dist|1;
                pos=mid;
            }
            else
                return (hi-left)*2 > maxdist ? hi : pos;
        }
    }

    return past[-1]<hi && (hi-past[-1])*2>maxdist ? hi : pos;
}

enum{MaxN=100};//this is small while data values can be large, so will use conventional sort instead of count array

int main()
{
    static int data[MaxN];
    int n;
    scanf("%d", &n);

    int *const e=data+n;
    for (int *b=data; b!=e; ++b) scanf("%d", b);
    sort(data, e);

    int lo, hi;//both inclusive
    scanf("%d%d", &lo, &hi);

    printf("%d\n", most_remote(data, e, lo, hi));
    return 0;
}
