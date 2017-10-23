/**
 * Heres an optimized loop using XOR that doesn't branch on the data being odd
 */
#include <stdio.h>

int main()
{
    int n, a, prev, total;/* prev will be 1 for odd, 0 for even */
    scanf("%d", &n);

    scanf("%d", &a);
    total=prev=a&1;

    scanf("%d", &a);
    prev^=a&1;
    n-=2;

    while(n--)
    {
        scanf("%d", &a);
        total+=prev;
        prev^=a&1;/* next iteration */
    }

    if (prev)
        puts("NO");
    else
        printf("%d\n", total<<1);

    return 0;
}
