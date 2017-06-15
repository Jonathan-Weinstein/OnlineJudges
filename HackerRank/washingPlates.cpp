/*
    Washing Plates
    https://www.hackerrank.com/contests/101hack41/challenges/washing-dishs
    solution by Jonathan Weinstein 9/21/16

    Problem:
    There are N dirty dishes, but Bob only has time to wash K of them.
    Each dish has 2 values associated with them, P and D.
    P is how much money Bob will earn for washing the dish.
    D is how much money Bob will be deducted for not washing the dish.

    Question:
    >>> If Bob can only wash at most K dishes, whats the most he can earn?
        If this value is negative, print 0

    Input format:
    First line has N followed by K.
    The following N lines hold P and D for a dish.
*/
#include <stdio.h>
#include <stdint.h>//dealing with big int values here
#include <algorithm>//nth_element

enum{N=200000};//200k

struct dish
{
    unsigned pay, deduct;
};

const auto Cmp=[](dish a, dish b)
{
    return (a.pay+a.deduct) > (b.pay+b.deduct);//both values are equally important
};//lambda

void println(uint64_t u);

int main(int argc, char **argv)
{
    if (argc==2 && freopen(argv[1], "r", stdin)==nullptr)
    {
        perror("freopen()");
        return 1;
    }

    unsigned n, k;
    scanf("%u%u", &n, &k);

    if (k>=n)
    {
        uint64_t sum=0ul;
        unsigned pay;
        while (n--) scanf("%u%*u", &pay), sum+=pay;//ignore deduct value
        println(sum);
    }
    else
    {
        static dish Buf[N];
        dish *const End=Buf+n, *const Kth=Buf+k;//should call this KthEnd

        for (dish *p=Buf; p!=End; ++p)
            scanf("%u%u", &p->pay, &p->deduct);

        std::nth_element(Buf, Kth, End, Cmp);//only need to semi-sort, since addition order doesn't matter

        uint64_t gain=0ul, lose=0ul;//left, right side sums

        for (const dish *p1=Buf; p1!=Kth; ++p1) gain += p1->pay;//accumulate pay values in [Begin, Kth)
        for (const dish *p2=Kth; p2!=End; ++p2) lose += p2->deduct;//accumulate deduct values in [Kth, End)

        if (gain>lose)  println(gain-lose);
        else            puts("0");
    }

    return 0;
}

void println(uint64_t u)//hard to do this with printf portably
{
    char buf[21];
    unsigned pos=20u;
    buf[20u]='\n';
    do buf[--pos]=(u%10u)+'0'; while (u/=10u);
    fwrite(buf+pos, 1u, 21-pos, stdout);
}
