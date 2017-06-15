/*
    2's Complement
    https://www.hackerrank.com/challenges/2s-complement

    Jonathan Weinstein
    last updated December 16, 2016
*/
#include <stdio.h>
#include <stdint.h>

static inline
int bsr(uint32_t u)
{
    return __builtin_clz(u)^31;
}

uint64_t alpha(unsigned n)//popcnt sum of xrange [0, n)
{
    uint64_t a=0;

    while (n>1)
    {
        const unsigned x=bsr(n);
        a += (uint64_t)x<<(x-1);
        n ^= 1<<x;//could just sub
        a += n;
    }

    return a;
}

uint64_t answer(int64_t b, int64_t e)
{
    if (b>=0)
        return alpha(e) - alpha(b);
    else if (e>=0)//if z<0, sum of 0 bits in xrange [z, 0) == sum of 1 bits in xrange [0, -z)
        return (0-b)*32 - alpha(-b) + alpha(e);
    else
        return (e-b)*32 - alpha(-b) + alpha(-e);
}

void println(uint64_t u);

int main()
{
    unsigned t;
    scanf("%u", &t);

    while (t--)
    {
        int beg, inc;
        scanf("%d%d", &beg, &inc);
        println(answer(beg, (int64_t)inc+1));
    }

    return 0;
}

void println(uint64_t u)
{
    char buf[32], *p;
    buf[31]='\n';
    p=buf+30;

    while (u>=10)
        *p-- = (u%10)|48, u/=10;

    *p=u|48;
    fwrite(p, 1, (buf+32)-p, stdout);
}
