#include <stdio.h>

int maxint(int a, int b)
{
    return a>b ? a : b;
}

int main()
{
    int rcnt[100]={};//remainder count
    int n;
    unsigned k;

    scanf("%d%u", &n, &k);

    if (k!=1u)
    {
        while (n--)
        {
            unsigned a;
            scanf("%u", &a);
            ++rcnt[a%k];
        }

        int result = rcnt[0]==0 ? 0 : 1;//can take one of these if there is one

        for (size_t i=1u, j=k-1u; i<j; ++i, --j)
            result+=maxint(rcnt[i], rcnt[j]);

        if (!(k&1u) && rcnt[k>>1u]!=0)//if k even and were some numbers in original set that had a remainder of k/2
            ++result;//can only take 1 of them

        printf("%d\n", result);
    }
    else
        puts("1");//not zero?

    return 0;
}
