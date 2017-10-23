#include <stdio.h>

#include <algorithm>
using namespace std;

int main()
{
    static int a[1001], b[1001];//1 extra for sentinels
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        int *const x=a+n, *const y=b+n;

        for (int *iter=a; iter!=x; ++iter) scanf("%d", iter);
        *x=-1;
        sort(a, x);

        for (int *iter=b; iter!=y; ++iter) scanf("%d", iter);
        *y=-1;
        sort(b, y, [](int a, int b){return a>b;});

        size_t i=0u;
        while (a[i]+b[i] >= k) ++i;

        puts(a[i]==-1 ? "YES" : "NO");
    }

    return 0;
}
