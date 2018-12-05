//LINE MUST BE HORIZ OR VERT

#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    if (n>1)
    {
        int a, b, x, y;
        scanf("%d%d%d%d", &a, &b, &x, &y);
        n -= 2;

        if (a==x)
        {
            while (n--)
            {
                scanf("%d%d", &x, &y);
                if (x != a)
                    goto Lno;
            }
        }
        else if (b==y)
        {
            while (n--)
            {
                scanf("%d%d", &x, &y);
                if (y != b)
                    goto Lno;
            }while (--n);
        }
        else
            goto Lno;

        puts("YES");
    }

    return 0;
Lno:
    puts("NO");
    return 0;
}
