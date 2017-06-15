#include <stdio.h>

enum{ sentinel=10001, capacity=10002 };

int main()
{
    bool v[capacity]={};
    unsigned n;

    v[sentinel]=true;
    scanf("%u", &n);

    while (n--)
    {
        unsigned a;
        scanf("%u", &a);
        v[a]=true;
    }

    int i=0, groups=0;
    while (i<sentinel)
    {
        while (!v[i]) ++i;//maybe a bitset could be used if sparsely populated
        if (i==sentinel) break;
        ++groups;
        i+=5;
    }

    printf("%d\n", groups);
    return 0;
}
