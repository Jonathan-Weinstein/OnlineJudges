#include <stdio.h>
#include <algorithm>
using namespace std;

enum{N=2000};
typedef int *iter;

bool adjust(iter b, iter e, int quot, int rem)//quotient and remainder of target value
{
    iter const part = e-rem;

    if (rem==0 || *part>quot)
    {
        fill(b, part, quot);//don't have to fill these, can return quot and how many times to print it
        fill(part, e, quot+1);
        return true;
    }

    return false;
}

bool possible(iter b, iter const e, int target)//input comes in sorted
{
    while (b!=e)
    {
        const int quot = target/unsigned(e-b);

        if (*b>=quot)
            return adjust(b, e, quot, target%unsigned(e-b));

        do     target -= *b++;
        while (b!=e && *b<quot);
    }

    return false;
}

int main()
{
    static int Buf[N];
    int n, target;
    scanf("%d%d", &n, &target);
    int *const End=Buf+n;

    for (int *p=Buf; p!=End; ++p) scanf("%d", p);
    sort(Buf, End);//full sort may not be needed

    if (possible(Buf, End, target))
        for (const int *p=Buf; p!=End; ++p) printf("%d\n", *p);
    else
        puts("IMPOSSIBLE");

    return 0;
}
