/* Luck Balance https://www.hackerrank.com/challenges/luck-balance
    This challenge is not very hard, and can be done a variety of ways, but I think this is a good use case of
    nth_element and one of the best ways to do it, since the count of important data is not known until we read it all.

    Since addition is associative, the sum of the smallest k values can be done in any order, and a full sort isn't needed
    (maybe I shouldn't use k here since the problem description gives that a different meaning).
*/
#include <stdio.h>

#include <algorithm>//nth_element
#include <numeric>//accumulate
using namespace std;

int main()
{
    int buf[100], *e=buf, total=0, n, noMore;
    scanf("%d%d", &n, &noMore);

    while (n--)
    {
        int luck;
        scanf("%d ", &luck);//skip ws

        if (getchar()=='1')
            *e++ = luck;
        else
            total+=luck;
    }

    const int wins=e-buf-noMore;

    if (wins>0)
    {
        int *const wEnd=buf+wins;
        nth_element(buf, wEnd, e);

        printf("%d\n", total - accumulate(buf, wEnd, 0) + accumulate(wEnd, e, 0));
    }
    else
        printf("%d\n", accumulate(buf, e, total));

    return 0;
}
