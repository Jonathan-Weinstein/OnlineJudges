#include <stdio.h>

int main()
{
    int cnt[1001]={}, n;
    scanf("%d", &n);

    for (int x=n; x--; )
    {
        int a;
        scanf("%d", &a);
        ++cnt[a];
    }

    for (int i=0; n!=0; )
    {
        printf("%d\n", n);
        while (cnt[i]==0) ++i;
        n-=cnt[i++];
    }

    return 0;
}
